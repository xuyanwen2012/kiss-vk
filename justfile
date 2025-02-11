
set-android:
    xmake f -p android -a arm64-v8a --ndk=~/Android/Sdk/ndk/28.0.12674087/ --android_sdk=~/Android/Sdk/ --ndk_sdkver=28 -c -v

set-jetson:
    xmake f -p linux -a arm64 -c -v

set-default:
    xmake f -p linux -a x86_64 -c


set shell := ["bash", "-c"]

# Paths
SHADER_COMP_DIR := "src/shaders/comp"
SHADER_SPV_DIR := "src/shaders/spv"
SHADER_H_DIR := "src/shaders/h"

# Rule to compile all shaders
compile:
    mkdir -p {{SHADER_SPV_DIR}} {{SHADER_H_DIR}}
    for shader in `find {{SHADER_COMP_DIR}} -name "*.comp"`; do \
        shader_name=$$(basename $$shader .comp); \
        glslc --target-env=vulkan1.3 -O -o {{SHADER_SPV_DIR}}/$$shader_name.spv $$shader; \
        xxd -i {{SHADER_SPV_DIR}}/$$shader_name.spv > {{SHADER_H_DIR}}/$$shader_name_spv.h; \
        echo "Compiled: $$shader -> {{SHADER_SPV_DIR}}/$$shader_name.spv"; \
        echo "Generated header: {{SHADER_H_DIR}}/$$shader_name_spv.h"; \
    done
