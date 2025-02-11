#include <spdlog/spdlog.h>

#include "algorithm.hpp"
#include "engine.hpp"

template <typename T>
using UsmVector = std::pmr::vector<T>;

int main(int argc, char** argv) {
  spdlog::set_level(spdlog::level::trace);

  const vulkan::Engine engine;
  auto mr = engine.get_mr();

  UsmVector<uint32_t> input_a(1024, mr);
  UsmVector<uint32_t> input_b(1024, mr);
  UsmVector<uint32_t> output(1024, mr);

  // #version 460

  // layout(local_size_x = 256) in;

  // layout(push_constant) uniform Params { uint n; }
  // params;

  // layout(std430, set = 0, binding = 0) readonly buffer InputA {
  //   float u_input_a[];
  // };

  // layout(std430, set = 0, binding = 1) readonly buffer InputB {
  //   float u_input_b[];
  // };

  // layout(std430, set = 0, binding = 2) writeonly buffer Output {
  //   float u_output[];
  // };

  // void main() {
  //   uint global_idx = gl_GlobalInvocationID.x;

  //   if (global_idx < params.n) {
  //     u_output[global_idx] = u_input_a[global_idx] + u_input_b[global_idx];
  //   }
  // }

  struct Ps {
    uint32_t n;
  };

  auto algo =
      engine.make_algo("hello_vector_add")->work_group_size(256, 1, 1)->num_buffers(4)->push_constant<Ps>()->build();

  spdlog::info("done!");
  return 0;
}
