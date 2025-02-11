// #pragma once

// #include "engine.hpp"

// namespace vulkan {

// class Singleton {
//  public:
//   // Delete copy constructor and assignment operator to prevent copies
//   Singleton(const Singleton &) = delete;
//   Singleton &operator=(const Singleton &) = delete;

//   static Singleton &getInstance() {
//     static Singleton instance;
//     return instance;
//   }

//  private:
//   Singleton() : engine_() {}
//   ~Singleton() { spdlog::info("Singleton instance destroyed."); }

//   Engine engine_;
// };

// }  // namespace vulkan
