#include "algorithm.hpp"

#include "shaders/all_shaders.hpp"

namespace vulkan {

Algorithm::Algorithm(VulkanMemoryResource* mr_ptr, const std::string_view shader_name)
    : mr_ptr_(mr_ptr), shader_name_(shader_name) {
  load_compiled_shader(shader_name_);

  create_shader_module();
}

Algorithm::~Algorithm() {}

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
}

}  // namespace vulkan