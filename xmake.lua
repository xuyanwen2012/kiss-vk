add_rules("mode.debug", "mode.release")

set_languages("c++20")
set_warnings("all", "error")

includes("android.lua")

add_requires("vulkan-hpp", "vulkan-memory-allocator")
add_requires("spdlog")

target("kiss-vk")
    set_kind("binary")
    add_headerfiles("src/*.hpp")
    add_files("src/*.cpp")
    add_packages("vulkan-hpp", "vulkan-memory-allocator")
    add_packages("spdlog")

    if is_plat("android") then
        on_run(run_on_android)
    end




