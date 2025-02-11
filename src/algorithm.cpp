#include "algorithm.hpp"

namespace vulkan {

Algorithm::Algorithm(VulkanMemoryResource* mr_ptr, const std::string_view shader_name)
    : mr_ptr_(mr_ptr), shader_name_(shader_name) {
  // load_compiled_shader();
}

Algorithm::~Algorithm() {
}

}  // namespace vulkan