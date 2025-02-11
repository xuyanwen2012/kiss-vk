#include <spdlog/spdlog.h>

#include "engine.hpp"

template <typename T>
using UsmVector = std::pmr::vector<T>;

void run_hello_vector_add(vulkan::Engine& engine) {
  constexpr auto n = 1024;
  UsmVector<uint32_t> input_a(n, engine.get_mr());
  UsmVector<uint32_t> input_b(n, engine.get_mr());
  UsmVector<uint32_t> output(n, engine.get_mr());

  std::ranges::fill(input_a, 1);
  std::ranges::fill(input_b, 2);
  std::ranges::fill(output, 0);

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

  auto seq = engine.make_seq();
  seq->record_commands(algo.get(), {vulkan::div_ceil(n, 256), 1, 1});
  seq->launch_kernel_async();
  seq->sync();

  // print 10 output elements
  for (auto i = 0; i < 10; i++) {
    spdlog::info("output[{}] = {}", i, output[i]);
  }
}

void run_multiple_steps(vulkan::Engine& engine) {
  constexpr auto n = 1024;
  UsmVector<uint32_t> buf_a(n, engine.get_mr());
  UsmVector<uint32_t> buf_b(n, engine.get_mr());
  UsmVector<uint32_t> buf_c(n, engine.get_mr());
  UsmVector<uint32_t> buf_d(n, engine.get_mr());
  UsmVector<uint32_t> buf_e(n, engine.get_mr());

  std::fill(buf_a.begin(), buf_a.end(), 1);
  std::fill(buf_b.begin(), buf_b.end(), 10);
  std::fill(buf_c.begin(), buf_c.end(), 100);
  std::fill(buf_d.begin(), buf_d.end(), 1000);

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

  auto seq = engine.make_seq();
  seq->cmd_begin();

  algo_a->record_bind_core(seq->get_handle());
  algo_a->record_bind_push(seq->get_handle());
  algo_a->record_dispatch(seq->get_handle(), {vulkan::div_ceil(n, 256), 1, 1});

  algo_a->update_buffer({
      engine.get_buffer_info(buf_b),
      engine.get_buffer_info(buf_c),
      engine.get_buffer_info(buf_d),
  });

  algo_a->record_bind_core(seq->get_handle());
  algo_a->record_bind_push(seq->get_handle());
  algo_a->record_dispatch(seq->get_handle(), {vulkan::div_ceil(n, 256), 1, 1});

  algo_a->update_buffer({
      engine.get_buffer_info(buf_c),
      engine.get_buffer_info(buf_d),
      engine.get_buffer_info(buf_e),
  });

  algo_a->record_bind_core(seq->get_handle());
  algo_a->record_bind_push(seq->get_handle());
  algo_a->record_dispatch(seq->get_handle(), {vulkan::div_ceil(n, 256), 1, 1});

  seq->cmd_end();

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
  run_hello_vector_add(engine);

  spdlog::info("done!");
  return 0;
}
