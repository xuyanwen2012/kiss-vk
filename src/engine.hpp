#pragma once

#include "algorithm.hpp"
#include "base_engine.hpp"
#include "vma_pmr.hpp"

namespace vulkan {

class Engine final : public BaseEngine {
 public:
  explicit Engine() : BaseEngine(true), mr_ptr(std::make_unique<VulkanMemoryResource>(device_)) {}

  [[nodiscard]] VulkanMemoryResource *get_mr() { return mr_ptr.get(); }

  std::shared_ptr<Algorithm> make_algo(const std::string_view shader_name) {
    return std::make_shared<Algorithm>(mr_ptr.get(), shader_name);
  }

 private:
  std::unique_ptr<VulkanMemoryResource> mr_ptr;
};

}  // namespace vulkan