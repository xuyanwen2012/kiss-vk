#include <spdlog/spdlog.h>

#include "algorithm.hpp"
#include "engine.hpp"

template <typename T>
using UsmVector = std::pmr::vector<T>;

int main(int argc, char** argv) {
  spdlog::set_level(spdlog::level::trace);

  const vulkan::Engine engine;
  auto mr = engine.get_mr();

  constexpr auto n = 1024;
  UsmVector<uint32_t> input_a(n, mr);
  UsmVector<uint32_t> input_b(n, mr);
  UsmVector<uint32_t> output(n, mr);

  struct Ps {
    uint32_t n;
  };

  auto algo =
      engine.make_algo("hello_vector_add")->work_group_size(256, 1, 1)->num_buffers(4)->push_constant<Ps>()->build();

  spdlog::info("done!");
  return 0;
}
