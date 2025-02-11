#include <spdlog/spdlog.h>

#include "algorithm.hpp"
#include "engine.hpp"

int main(int argc, char** argv) {
  spdlog::set_level(spdlog::level::trace);

  vulkan::Engine engine;
  auto mr = engine.get_mr();

  struct Ps {
    uint32_t input_height;
    uint32_t input_width;
    uint32_t weight_output_channels;
    uint32_t weight_input_channels;
    uint32_t weight_height;
    uint32_t weight_width;
    uint32_t bias_number_of_elements;
    uint32_t kernel_size;
    uint32_t stride;
    uint32_t padding;
    uint32_t output_height;
    uint32_t output_width;
    bool relu;
  };

  auto algo = engine.make_algo("cifar_conv2d")->num_buffers(4)->push_constant<Ps>()->build();

  spdlog::info("done!");
  return 0;
}
