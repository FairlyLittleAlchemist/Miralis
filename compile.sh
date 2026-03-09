#!/usr/bin/env bash

# ================================
#  GLSL → SPIR-V Shader Compiler
# ================================

SHADER_DIR="Miralis/src/Miralis/Shaders"
COMPILED_DIR="$SHADER_DIR/Compiled"

SHADER_EXTENSIONS=(.vert .frag .geom .tesc .tese .comp .glsl)

echo "========================================"
echo "   GLSL to SPIR-V Shader Compiler"
echo "========================================"
echo

# Check shader directory
if [[ ! -d "$SHADER_DIR" ]]; then
    echo "Error: $SHADER_DIR directory does not exist!"
    echo "Please make sure you're running this script from the correct location."
    exit 1
fi

# Check glslc
if ! command -v glslc &> /dev/null; then
    echo "Error: glslc compiler not found!"
    echo "Please install Vulkan SDK or shaderc."
    echo "https://vulkan.lunarg.com/"
    exit 1
fi

echo "Found glslc:"
glslc --version
echo

# Create compiled dir
mkdir -p "$COMPILED_DIR"

echo "Recreating folder structure and compiling shaders..."
echo "Source: $SHADER_DIR"
echo "Target: $COMPILED_DIR"
echo

total_shaders=0
compiled_shaders=0
failed_shaders=0
created_dirs=0

# Create directory structure
while IFS= read -r -d '' dir; do
    [[ "$dir" == *"/Compiled"* ]] && continue

    rel="${dir#$SHADER_DIR/}"
    [[ "$rel" == "$dir" ]] && continue

    target="$COMPILED_DIR/$rel"

    if [[ ! -d "$target" ]]; then
        echo "Creating directory: $rel"
        mkdir -p "$target"
        created_dirs=$((created_dirs + 1))
    fi
done < <(find "$SHADER_DIR" -type d -print0)

echo
echo "Compiling shader files..."
echo

# Compile shaders
while IFS= read -r -d '' file; do
    [[ "$file" == *"/Compiled/"* ]] && continue

    filename=$(basename "$file")

    is_shader=0
    for ext in "${SHADER_EXTENSIONS[@]}"; do
        [[ "$filename" == *"$ext" ]] && is_shader=1
    done

    [[ "$is_shader" -eq 0 ]] && continue

    total_shaders=$((total_shaders + 1))

    rel_path="${file#$SHADER_DIR/}"
    rel_dir=$(dirname "$rel_path")
    base_name="${filename%.*}"

    output="$COMPILED_DIR/$rel_dir/$base_name.spv"

    mkdir -p "$(dirname "$output")"

    echo "Compiling: $rel_path"

    if glslc "$file" -o "$output"; then
        echo "   ✓ Success: $filename -> $base_name.spv"
        compiled_shaders=$((compiled_shaders + 1))
    else
        echo "   ✗ Failed: $filename"
        failed_shaders=$((failed_shaders + 1))
    fi

    echo
done < <(find "$SHADER_DIR" -type f -print0)

# Summary
echo "========================================"
echo "          COMPILATION SUMMARY"
echo "========================================"
echo "Directories created: $created_dirs"
echo "Total shader files found: $total_shaders"
echo "Successfully compiled: $compiled_shaders"
echo "Failed compilations: $failed_shaders"
echo "========================================"

if [[ $failed_shaders -gt 0 ]]; then
    echo
    echo "Warning: Some shaders failed to compile!"
    echo "Check the error messages above for details."
fi

if [[ $compiled_shaders -gt 0 ]]; then
    echo
    echo "Compiled shaders are located in:"
    echo "  $COMPILED_DIR"
fi

echo
exit 0