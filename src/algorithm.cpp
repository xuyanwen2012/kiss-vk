#include "algorithm.hpp"

#include "shaders/all_shaders.hpp"

namespace vulkan {

Algorithm::Algorithm(VulkanMemoryResource* mr_ptr, const std::string_view shader_name)
    : mr_ptr_(mr_ptr), shader_name_(shader_name) {
  load_compiled_shader(shader_name_);
  create_shader_module();
}

Algorithm::~Algorithm() {}

std::shared_ptr<Algorithm> Algorithm::num_buffers(const size_t n) {
  internal_.num_buffers_ = n;
  create_descriptor_set_layout();
  create_descriptor_pool();
  allocate_descriptor_sets();
  return shared_from_this();
}

std::shared_ptr<Algorithm> Algorithm::build() { return shared_from_this(); }

// -------------------------------------------------------------------------------------------------
//
// -------------------------------------------------------------------------------------------------

void Algorithm::load_compiled_shader(const std::string& shader_name) {
  std::pair<const unsigned char*, size_t> shader_pair = shaders::all_shaders.at(shader_name);

  internal_.spirv_binary_.resize(shader_pair.second / sizeof(uint32_t));
  std::memcpy(internal_.spirv_binary_.data(), shader_pair.first, shader_pair.second);
}

// -------------------------------------------------------------------------------------------------
// Create shader module
// -------------------------------------------------------------------------------------------------

void Algorithm::create_shader_module() {
  if (shader_name_.empty()) {
    throw std::runtime_error("Shader name is empty");
  }

  if (internal_.spirv_binary_.empty()) {
    throw std::runtime_error("SPIRV binary is empty");
  }

  const vk::ShaderModuleCreateInfo create_info{
      .codeSize = internal_.spirv_binary_.size() * sizeof(uint32_t),
      .pCode = internal_.spirv_binary_.data(),
  };

  shader_module_ = device_ref_.createShaderModule(create_info);

  spdlog::debug("Shader module [{}] created successfully", shader_name_);
}

// ----------------------------------------------------------------------------
// Descriptor Related
//   create_descriptor_set_layout();
//   create_descriptor_pool();
//   allocate_descriptor_sets();
// ----------------------------------------------------------------------------

void Algorithm::create_descriptor_set_layout() {
  spdlog::trace("Algorithm::create_descriptor_set_layout() num_buffers: {}", internal_.num_buffers_);

  if (internal_.num_buffers_ == 0) {
    throw std::runtime_error("Number of buffers is 0");
  }

  std::vector<vk::DescriptorSetLayoutBinding> bindings;
  bindings.reserve(internal_.num_buffers_);

  for (uint32_t i = 0; i < internal_.num_buffers_; ++i) {
    bindings.emplace_back(vk::DescriptorSetLayoutBinding{
        .binding = i,
        .descriptorType = vk::DescriptorType::eStorageBuffer,
        .descriptorCount = 1,
        .stageFlags = vk::ShaderStageFlagBits::eCompute,
    });
  }

  const vk::DescriptorSetLayoutCreateInfo create_info{
      .bindingCount = static_cast<uint32_t>(bindings.size()),
      .pBindings = bindings.data(),
  };

  descriptor_set_layout_ = device_ref_.createDescriptorSetLayout(create_info);
}

void Algorithm::create_descriptor_pool() {
  spdlog::trace("Algorithm create_descriptor_pool");

  const std::vector pool_sizes{
      vk::DescriptorPoolSize{
          .type = vk::DescriptorType::eStorageBuffer,
          .descriptorCount = static_cast<uint32_t>(internal_.num_buffers_),
      },
  };

  const vk::DescriptorPoolCreateInfo create_info{
      .maxSets = 1,
      .poolSizeCount = static_cast<uint32_t>(pool_sizes.size()),
      .pPoolSizes = pool_sizes.data(),
  };

  descriptor_pool_ = device_ref_.createDescriptorPool(create_info);
}

void Algorithm::allocate_descriptor_sets() {
  spdlog::trace("Algorithm allocate_descriptor_sets");

  if (descriptor_pool_ == nullptr || descriptor_set_layout_ == nullptr) {
    throw std::runtime_error("Descriptor pool or set layout is not initialized");
  }

  const vk::DescriptorSetAllocateInfo allocate_info{
      .descriptorPool = descriptor_pool_,
      .descriptorSetCount = 1,
      .pSetLayouts = &descriptor_set_layout_,
  };

  descriptor_set_ = device_ref_.allocateDescriptorSets(allocate_info).front();
}

}  // namespace vulkan