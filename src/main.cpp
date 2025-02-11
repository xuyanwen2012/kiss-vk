#include <spdlog/spdlog.h>

// #include "singleton.hpp"

#include "engine.hpp"

// std::shared_ptr<vulkan::Algorithm> make_algo(vulkan::VulkanMemoryResource& mr, const std::string_view shader_name) {
//   return std::make_shared<vulkan::Algorithm>(&mr, shader_name);
// }

int main(int argc, char** argv) {
  spdlog::set_level(spdlog::level::trace);

  // auto algorithm_ptr = vulkan::Singleton::getInstance().make_algo("cifar_conv2d")->build();

  vulkan::Engine engine;
  auto mr = engine.get_mr();

  auto algo = engine.make_algo("cifar_conv2d")->build();

  return 0;
}
