#include <spdlog/spdlog.h>

#include "engine.hpp"

template <typename T>
using UsmVector = std::pmr::vector<T>;

int main() {
  spdlog::set_level(spdlog::level::trace);

  vulkan::Engine engine;
  auto mr = engine.get_mr();

  constexpr auto n = 1024;
  UsmVector<uint32_t> input_a(n, mr);
  UsmVector<uint32_t> input_b(n, mr);
  UsmVector<uint32_t> output(n, mr);

  struct Ps {
    uint32_t n;
  };

  auto algo =
      engine.make_algo("hello_vector_add")->work_group_size(256, 1, 1)->num_buffers(3)->push_constant<Ps>()->build();

  algo->update_push_constant(Ps{
      .n = n,
  });

  algo->update_buffer({
      engine.get_buffer_info(input_a),
      engine.get_buffer_info(input_b),
      engine.get_buffer_info(output),
  });

  auto seq = engine.make_seq();
  seq->record_commands(algo.get(), {vulkan::div_ceil(n, 256), 1, 1});
  seq->launch_kernel_async();
  seq->sync();

  spdlog::info("done!");
  return 0;
}
