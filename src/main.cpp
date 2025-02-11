#include <spdlog/spdlog.h>

#include "engine.hpp"

template <typename T>
using UsmVector = std::pmr::vector<T>;

void run_hello_vector_add(vulkan::Engine& engine, vulkan::Sequence* seq) {
  constexpr auto n = 1024;
  UsmVector<float> input_a(n, engine.get_mr());
  UsmVector<float> input_b(n, engine.get_mr());
  UsmVector<float> output(n, engine.get_mr());

  std::ranges::fill(input_a, 1.0f);
  std::ranges::fill(input_b, 2.0f);
  std::ranges::fill(output, 0.0f);

  struct Ps {
    uint32_t n;
  };

  auto algo = engine.make_algo("hello_vector_add")
                  ->work_group_size(256, 1, 1)
                  ->num_buffers(3)
                  ->push_constant<Ps>()
                  ->build();

  algo->update_push_constant(Ps{
      .n = n,
  });

  algo->update_buffer({
      engine.get_buffer_info(input_a),
      engine.get_buffer_info(input_b),
      engine.get_buffer_info(output),
  });

  seq->record_commands(algo.get(), {vulkan::div_ceil(n, 256), 1, 1});
  seq->launch_kernel_async();
  seq->sync();

  // print 10 output elements
  for (auto i = 0; i < 10; i++) {
    spdlog::info("output[{}] = {}", i, output[i]);
  }
}

void run_multiple_steps(vulkan::Engine& engine, vulkan::Sequence* seq) {
  constexpr auto n = 1024;
  UsmVector<float> buf_a(n, engine.get_mr());
  UsmVector<float> buf_b(n, engine.get_mr());
  UsmVector<float> buf_c(n, engine.get_mr());
  UsmVector<float> buf_d(n, engine.get_mr());
  UsmVector<float> buf_e(n, engine.get_mr());

  std::ranges::fill(buf_a, 1.0f);
  std::ranges::fill(buf_b, 10.0f);

  struct Ps {
    uint32_t n;
  };

  auto algo_a = engine.make_algo("hello_vector_add")
                    ->work_group_size(256, 1, 1)
                    ->num_buffers(3)
                    ->push_constant<Ps>()
                    ->build();

  algo_a->update_push_constant(Ps{
      .n = n,
  });

  algo_a->update_buffer({
      engine.get_buffer_info(buf_a),
      engine.get_buffer_info(buf_b),
      engine.get_buffer_info(buf_c),
  });

  seq->record_commands(algo_a.get(), {vulkan::div_ceil(n, 256), 1, 1});
  seq->launch_kernel_async();
  seq->sync();

  algo_a->update_buffer({
      engine.get_buffer_info(buf_b),
      engine.get_buffer_info(buf_c),
      engine.get_buffer_info(buf_d),
  });

  seq->record_commands(algo_a.get(), {vulkan::div_ceil(n, 256), 1, 1});
  seq->launch_kernel_async();
  seq->sync();

  algo_a->update_buffer({
      engine.get_buffer_info(buf_c),
      engine.get_buffer_info(buf_d),
      engine.get_buffer_info(buf_e),
  });

  seq->record_commands(algo_a.get(), {vulkan::div_ceil(n, 256), 1, 1});
  seq->launch_kernel_async();
  seq->sync();

  // print 10 output elements
  for (auto i = 0; i < 10; i++) {
    spdlog::info("buf_e[{}] = {}", i, buf_e[i]);
  }
}

int main() {
  spdlog::set_level(spdlog::level::trace);

  vulkan::Engine engine;
  auto seq = engine.make_seq();

  run_hello_vector_add(engine, seq.get());

  run_multiple_steps(engine, seq.get());

  spdlog::info("done!");
  return 0;
}
