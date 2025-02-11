#pragma once

#include <span>

#include "algorithm.hpp"
#include "base_engine.hpp"
#include "vma_pmr.hpp"

namespace vulkan {

class Engine final : public BaseEngine {
 public:
  explicit Engine() : BaseEngine(true), mr_ptr_(std::make_unique<VulkanMemoryResource>(device_)) {}

  [[nodiscard]] VulkanMemoryResource* get_mr() const { return mr_ptr_.get(); }

  [[nodiscard]] std::shared_ptr<Algorithm> make_algo(const std::string& shader_name) const {
    return std::make_shared<Algorithm>(mr_ptr_.get(), shader_name);
  }

  // To get a 'vk::Buffer' from raw pointer of the 'UsmVector'
  [[nodiscard]] vk::Buffer get_buffer(void* ptr) const { return mr_ptr_->get_buffer_from_pointer(ptr); }

  template <typename T>
  vk::DescriptorBufferInfo get_buffer_info(std::pmr::vector<T>& vec) const {
    return vk::DescriptorBufferInfo{
        .buffer = get_buffer(vec.data()),
        .offset = 0,
        .range = vec.size() * sizeof(T),
    };
  }

 private:
  std::unique_ptr<VulkanMemoryResource> mr_ptr_;
};

}  // namespace vulkan