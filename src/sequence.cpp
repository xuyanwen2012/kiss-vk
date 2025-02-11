#include "sequence.hpp"

namespace vulkan {

Sequence::Sequence(vk::Device device_ref, vk::Queue compute_queue_ref, const uint32_t compute_queue_index)
    : device_ref_(device_ref), compute_queue_ref_(compute_queue_ref), compute_queue_index_(compute_queue_index) {
  spdlog::trace("Sequence constructor");

  create_sync_objects();
  create_command_pool();
  create_command_buffer();
}

void Sequence::create_command_pool() {
  spdlog::trace("Sequence::create_command_pool()");

  const vk::CommandPoolCreateInfo create_info{
      .flags = vk::CommandPoolCreateFlagBits::eResetCommandBuffer,
      .queueFamilyIndex = compute_queue_index_,
  };

  command_pool_ = device_ref_.createCommandPool(create_info);
}

void Sequence::create_sync_objects() {
  spdlog::trace("Sequence::create_sync_objects()");

  constexpr vk::FenceCreateInfo create_info{};
  fence_ = device_ref_.createFence(create_info);
}

void Sequence::create_command_buffer() {
  spdlog::trace("Sequence::create_command_buffer()");

  const vk::CommandBufferAllocateInfo allocate_info{
      .commandPool = command_pool_,
      .level = vk::CommandBufferLevel::ePrimary,
      .commandBufferCount = 1,
  };

  handle_ = device_ref_.allocateCommandBuffers(allocate_info).front();
}

void Sequence::cmd_begin() const {
  spdlog::trace("Sequence::cmd_begin()");

  constexpr vk::CommandBufferBeginInfo begin_info{
      .flags = vk::CommandBufferUsageFlagBits::eOneTimeSubmit,
  };

  handle_.begin(begin_info);
}

void Sequence::cmd_end() const {
  spdlog::trace("Sequence::cmd_end()");

  handle_.end();
}

void Sequence::launch_kernel_async() {
  spdlog::trace("Sequence::launch_kernel_async()");

  vk::SubmitInfo submit_info{
      .commandBufferCount = 1,
      .pCommandBuffers = &handle_,
  };

  compute_queue_ref_.submit(submit_info, fence_);
}

void Sequence::sync() const {
  spdlog::trace("Sequence::sync()");

  if (device_ref_.waitForFences(1, &fence_, true, UINT64_MAX) != vk::Result::eSuccess) {
    throw std::runtime_error("Failed to sync sequence");
  }

  if (device_ref_.resetFences(1, &fence_) != vk::Result::eSuccess) {
    throw std::runtime_error("Failed to reset sequence");
  }
}

void Sequence::record_commands(const Algorithm* algo, std::array<uint32_t, 3> grid_size) const {
  spdlog::trace("Sequence::record_commands()");

  cmd_begin();

  algo->record_bind_core(handle_);
  if (algo->has_push_constants()) {
    algo->record_bind_push(handle_);
  }

  algo->record_dispatch(handle_, grid_size);

  cmd_end();
}

}  // namespace vulkan
