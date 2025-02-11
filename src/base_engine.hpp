#pragma once

#include <limits>

#include "vk.hpp"

namespace vulkan {

class BaseEngine {
 public:
  explicit BaseEngine(bool enable_validation_layer = true);

  ~BaseEngine();

 protected:
  void initialize_dynamic_loader();
  void request_validation_layer();
  void create_instance();
  void create_physical_device(
      vk::PhysicalDeviceType type = vk::PhysicalDeviceType::eIntegratedGpu);
  void create_device(vk::QueueFlags queue_flags = vk::QueueFlagBits::eCompute);
  void initialize_vma_allocator() const;

  vk::Instance instance_;
  vk::PhysicalDevice physical_device_;
  vk::Device device_;
  vk::Queue compute_queue_;

  uint32_t compute_queue_family_index_ = std::numeric_limits<uint32_t>::max();

 private:
  vk::DynamicLoader dl_;
  vk::DispatchLoaderDynamic dldi_;

  PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr_;

  std::vector<const char *> enabledLayers_;
};

}  // namespace vulkan
