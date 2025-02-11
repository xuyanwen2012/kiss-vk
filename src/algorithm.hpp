#pragma once

#include "vk.hpp"
#include "vma_pmr.hpp"

namespace vulkan {

class Algorithm final : public std::enable_shared_from_this<Algorithm> {
 public:
  explicit Algorithm(VulkanMemoryResource* mr_ptr, const std::string_view shader_name);

  ~Algorithm();

  // Usage:

  [[nodiscard]] std::shared_ptr<Algorithm> num_buffers(size_t n);
  [[nodiscard]] std::shared_ptr<Algorithm> build();

 private:
  void load_compiled_shader(const std::string& shader_name);

  void create_shader_module();
  void create_descriptor_set_layout();
  void create_descriptor_pool();
  void create_pipeline();

  void allocate_descriptor_sets();
  void allocate_push_constants();

  // References
  vk::Device device_ref_;
  VulkanMemoryResource* mr_ptr_;

  // Core vulkan handles
  vk::ShaderModule shader_module_ = nullptr;
  vk::Pipeline pipeline_ = nullptr;
  vk::PipelineCache pipeline_cache_ = nullptr;
  vk::PipelineLayout pipeline_layout_ = nullptr;
  vk::DescriptorSetLayout descriptor_set_layout_ = nullptr;
  vk::DescriptorPool descriptor_pool_ = nullptr;
  vk::DescriptorSet descriptor_set_ = nullptr;

  std::string shader_name_;

  struct {
    std::vector<uint32_t> spirv_binary_;
    size_t num_buffers_ = 0;
    

    // uint32_t reflected_workgroup_size_[3] = {0, 0, 0};
    // uint32_t reflected_push_constant_reported_size_ = 0;
    // uint32_t reflected_push_constant_accumulated_size_ = 0;
  } internal_;
};

}  // namespace vulkan
