# Directories
SHADER_COMP_DIR := src/shaders/comp
SHADER_SPV_DIR := src/shaders/spv
SHADER_H_DIR := src/shaders/h

# Find all .comp shader files
SHADERS := $(wildcard $(SHADER_COMP_DIR)/*.comp)

# Generate corresponding .spv and .h filenames
SPV_FILES := $(patsubst $(SHADER_COMP_DIR)/%.comp, $(SHADER_SPV_DIR)/%.spv, $(SHADERS))
H_FILES := $(patsubst $(SHADER_SPV_DIR)/%.spv, $(SHADER_H_DIR)/%_spv.h, $(SPV_FILES))

# Compiler settings
GLSLC := glslc
GLSLC_FLAGS := --target-env=vulkan1.3 -O

# Ensure directories exist
$(shell mkdir -p $(SHADER_SPV_DIR) $(SHADER_H_DIR))

# Default target: compile all shaders
all: $(SPV_FILES) $(H_FILES)

# Rule to compile .comp files into .spv
$(SHADER_SPV_DIR)/%.spv: $(SHADER_COMP_DIR)/%.comp
	$(GLSLC) $(GLSLC_FLAGS) -o $@ $<
	@echo "Compiled: $< -> $@"

# Rule to generate .h files from .spv
$(SHADER_H_DIR)/%_spv.h: $(SHADER_SPV_DIR)/%.spv
	xxd -i $< > $@
	@echo "Generated header: $@"

# Clean build artifacts
clean:
	rm -f $(SPV_FILES) $(H_FILES)
	@echo "Cleaned all compiled shaders and headers."

.PHONY: all clean
