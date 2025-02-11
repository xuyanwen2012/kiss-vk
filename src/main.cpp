#include <spdlog/spdlog.h>

#include "algorithm.hpp"
#include "base_engine.hpp"
#include "shaders/all_shaders.hpp"

int main(int argc, char **argv) {
  spdlog::set_level(spdlog::level::trace);

  vulkan::BaseEngine engine;
  vulkan::VulkanMemoryResource mr(engine.get_device());
  vulkan::Algorithm algorithm(&mr, "algorithm.comp");

  // peek at the shaders
  spdlog::info("cifar_conv2d_spv_len: {}", vulkan::shaders::src_shaders_spv_cifar_conv2d_spv_len);
  spdlog::info("cifar_linear_spv_len: {}", vulkan::shaders::src_shaders_spv_cifar_linear_spv_len);
  spdlog::info("cifar_maxpool2d_spv_len: {}", vulkan::shaders::src_shaders_spv_cifar_maxpool2d_spv_len);

  return 0;
}
