#pragma once

#include "vk.hpp"
#include "vma_pmr.hpp"

namespace vulkan {

class Algorithm final : public std::enable_shared_from_this<Algorithm> {
 public:
  explicit Algorithm(VulkanMemoryResource* mr_ptr, std::string shader_name);

  ~Algorithm() = default;

  // Usage:

  [[nodiscard]] std::shared_ptr<Algorithm> num_buffers(size_t n);
  [[nodiscard]] std::shared_ptr<Algorithm> push_constant_size(size_t size_in_bytes);

  template <typename T>
  [[nodiscard]] std::shared_ptr<Algorithm> push_constant() {
    return push_constant_size(sizeof(T));
  }

  [[nodiscard]] std::shared_ptr<Algorithm> build();

  [[nodiscard]] bool has_push_constants() const { return internal_.push_constant_size > 0; }

 private:
  void load_compiled_shader();

  void create_shader_module();
  void create_descriptor_set_layout();
  void create_descriptor_pool();
  void allocate_descriptor_sets();
  void allocate_push_constants();

  void create_pipeline();

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

  // Payloads (buffers and push constants)
  std::unique_ptr<std::byte[]> push_constants_ptr_ = nullptr;

  struct {
    std::vector<uint32_t> spirv_binary;
    size_t num_buffers = 0;
    size_t push_constant_size = 0;
    uint32_t work_group_size[3] = {0, 0, 0};
  } internal_;
};

}  // namespace vulkan
