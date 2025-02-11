add_rules("mode.debug", "mode.release")

set_languages("c++20")

add_requires("vulkan-hpp")
add_requires("vulkan-memory-allocator")
add_requires("spdlog")

target("kiss-vk")
    set_kind("binary")
    add_headerfiles("src/*.hpp")
    add_files("src/*.cpp")
    add_packages("vulkan-hpp")
    add_packages("vulkan-memory-allocator")
    add_packages("spdlog")






