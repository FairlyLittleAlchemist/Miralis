@echo off
setlocal enabledelayedexpansion

:: Set the base shader directory
set "SHADER_DIR=Miralis\src\Miralis\Shaders"
set "COMPILED_DIR=%SHADER_DIR%\Compiled"

:: Shader file extensions to compile
set "SHADER_EXTENSIONS=.vert .frag .geom .tesc .tese .comp .glsl"

echo ========================================
echo    GLSL to SPIR-V Shader Compiler
echo ========================================
echo.

:: Check if shaders directory exists
if not exist "%SHADER_DIR%" (
    echo Error: %SHADER_DIR% directory does not exist!
    echo Please make sure you're running this script from the correct location.
    pause
    exit /b 1
)

:: Check if glslc is available
glslc --version >nul 2>&1
if errorlevel 1 (
    echo Error: glslc compiler not found!
    echo Please make sure Vulkan SDK is installed and glslc is in your PATH.
    echo You can download it from: https://vulkan.lunarg.com/
    pause
    exit /b 1
)

echo Found glslc compiler:
glslc --version
echo.

:: Create the compiled directory if it doesn't exist
if not exist "%COMPILED_DIR%" (
    echo Creating compiled directory...
    mkdir "%COMPILED_DIR%"
)

echo Recreating folder structure and compiling shaders...
echo Source: %SHADER_DIR%
echo Target: %COMPILED_DIR%
echo.

set /a "total_shaders=0"
set /a "compiled_shaders=0"
set /a "failed_shaders=0"
set /a "created_dirs=0"

:: Loop through all directories in shaders folder
for /r "%SHADER_DIR%" %%d in (.) do (
    set "current_dir=%%d"
    
    :: Skip the compiled directory itself to avoid infinite recursion
    echo !current_dir! | findstr /i /c:"compiled" >nul
    if errorlevel 1 (
        :: Remove the base shader path to get relative path
        set "relative_path=!current_dir:%CD%\%SHADER_DIR%\=!"
        
        :: Skip if it's the root shaders directory
        if not "!relative_path!"=="." (
            set "target_dir=%COMPILED_DIR%\!relative_path!"
            
            :: Create the directory if it doesn't exist
            if not exist "!target_dir!" (
                echo Creating directory: !relative_path!
                mkdir "!target_dir!" 2>nul
                if !errorlevel! equ 0 (
                    set /a "created_dirs+=1"
                ) else (
                    echo   ✗ Failed to create directory: !relative_path!
                )
            )
        )
    )
)

echo.
echo Compiling shader files...
echo.

:: Now compile all shader files
for /r "%SHADER_DIR%" %%f in (*.*) do (
    set "source_file=%%f"
    set "file_name=%%~nxf"
    set "file_dir=%%~dpf"
    
    :: Skip files in compiled directory
    echo !source_file! | findstr /i /c:"compiled" >nul
    if errorlevel 1 (
        :: Check if file has a shader extension
        set "is_shader=0"
        for %%e in (%SHADER_EXTENSIONS%) do (
            echo !file_name! | findstr /i /c:"%%e" >nul
            if !errorlevel! equ 0 set "is_shader=1"
        )
        
        if !is_shader! equ 1 (
            set /a "total_shaders+=1"
            
            :: Get relative path for the file
            set "rel_file_path=!source_file:%CD%\%SHADER_DIR%\=!"
            
            :: Get just the filename without extension and the directory path
            for %%p in ("!source_file!") do (
                set "file_name_no_ext=%%~np"
                set "rel_dir_path=!rel_file_path:%%~nxp=!"
            )
            
            :: Create output path with .spv extension (without original extension)
            set "output_file=%COMPILED_DIR%\!rel_dir_path!!file_name_no_ext!.spv"
            
            :: Ensure output directory exists
            for %%p in ("!output_file!") do (
                set "output_dir=%%~dpp"
                if not exist "!output_dir!" mkdir "!output_dir!" 2>nul
            )
            
            :: Compile the shader
            echo Compiling: !rel_file_path!
            glslc "!source_file!" -o "!output_file!"
            
            if !errorlevel! equ 0 (
                echo   ✓ Success: !file_name! ^-^> !file_name_no_ext!.spv
                set /a "compiled_shaders+=1"
            ) else (
                echo   ✗ Failed: !file_name!
                set /a "failed_shaders+=1"
            )
            echo.
        )
    )
)

:: Display summary
echo ========================================
echo           COMPILATION SUMMARY
echo ========================================
echo Directories created: !created_dirs!
echo Total shader files found: !total_shaders!
echo Successfully compiled: !compiled_shaders!
echo Failed compilations: !failed_shaders!
echo ========================================

if !failed_shaders! gtr 0 (
    echo.
    echo Warning: Some shaders failed to compile!
    echo Check the error messages above for details.
)

if !compiled_shaders! gtr 0 (
    echo.
    echo Compiled shaders are located in: %COMPILED_DIR%
    echo All compiled shaders have the .spv extension.
)

echo.
pause