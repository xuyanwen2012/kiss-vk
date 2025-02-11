#include <spdlog/spdlog.h>

#include "algorithm.hpp"
#include "base_engine.hpp"

int main(int argc, char **argv) {
  spdlog::set_level(spdlog::level::trace);

  vulkan::BaseEngine engine;
  vulkan::VulkanMemoryResource mr(engine.get_device());
  vulkan::Algorithm algorithm(&mr, "cifar_conv2d");

  return 0;
}
