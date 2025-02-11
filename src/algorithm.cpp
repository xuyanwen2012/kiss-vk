#include "algorithm.hpp"

#include "shaders/all_shaders.hpp"

namespace vulkan {

Algorithm::Algorithm(VulkanMemoryResource* mr_ptr, const std::string_view shader_name)
    : mr_ptr_(mr_ptr), shader_name_(shader_name) {
  load_compiled_shader(shader_name_);
}

Algorithm::~Algorithm() {}

// -------------------------------------------------------------------------------------------------
//
// -------------------------------------------------------------------------------------------------

void Algorithm::load_compiled_shader(const std::string& shader_name) {
  // auto shader_pair = shaders::all_shaders.at(shader_name);
}

}  // namespace vulkan