#include <spdlog/spdlog.h>

#include "engine.hpp"

int main(int argc, char** argv) {
  spdlog::set_level(spdlog::level::trace);

  vulkan::Engine engine;
  auto mr = engine.get_mr();

  // auto algo = engine.make_algo("cifar_conv2d")->build();

  spdlog::info("done!");
  return 0;
}
