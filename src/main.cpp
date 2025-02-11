#include <spdlog/spdlog.h>

#include "base_engine.hpp"

int main(int argc, char **argv) {
  spdlog::set_level(spdlog::level::trace);

  vulkan::BaseEngine engine;

  return 0;
}
