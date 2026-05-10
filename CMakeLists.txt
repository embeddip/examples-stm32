cmake_minimum_required(VERSION 3.22)

project(dip-vs LANGUAGES C CXX ASM)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

add_compile_definitions(
    STM32F746xx
    ARM_MATH_CM7
    __FPU_PRESENT=1
    TF_LITE_STATIC_MEMORY=1
    ARM_MATH_DSP=1                # Enable DSP extensions
    ARMCM7=1                      # Cortex-M7 core for TFLM timing
)

# Define the main executable FIRST
add_executable(${PROJECT_NAME})

# Now add stm32cubemx (which assumes dip-vs already exists)
add_subdirectory(cmake/stm32cubemx)

# Add embedDIP module
add_subdirectory(embedDIP)

set(TFLM_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/Third_Party/lib/tflm-tree)

# Collect TFLite Micro core sources (exclude platform-specific dirs)
file(GLOB TFLM_MICRO_SOURCES
    ${TFLM_ROOT}/tensorflow/lite/micro/*.cc
    ${TFLM_ROOT}/tensorflow/lite/micro/arena_allocator/*.cc
    ${TFLM_ROOT}/tensorflow/lite/micro/memory_planner/*.cc
    ${TFLM_ROOT}/tensorflow/lite/micro/tflite_bridge/*.cc
)

# Collect kernel sources - Plain TFLite Micro reference kernels
file(GLOB TFLM_KERNEL_SOURCES
    ${TFLM_ROOT}/tensorflow/lite/micro/kernels/*.cc
)

# Add Cortex-M platform-specific sources (includes debug_log.cc)
file(GLOB TFLM_PLATFORM_SOURCES
    ${TFLM_ROOT}/tensorflow/lite/micro/cortex_m_generic/*.cc
)

# Collect core API sources
file(GLOB TFLM_CORE_SOURCES
    ${TFLM_ROOT}/tensorflow/lite/core/api/*.cc
    ${TFLM_ROOT}/tensorflow/lite/core/c/*.cc
)

# Collect kernel utility sources (quantization, tensor utils, etc.)
file(GLOB TFLM_KERNEL_UTIL_SOURCES
    ${TFLM_ROOT}/tensorflow/lite/kernels/internal/quantization_util.cc
    ${TFLM_ROOT}/tensorflow/lite/kernels/internal/tensor_utils.cc
    ${TFLM_ROOT}/tensorflow/lite/kernels/internal/portable_tensor_utils.cc
    ${TFLM_ROOT}/tensorflow/lite/kernels/internal/tensor_ctypes.cc
    ${TFLM_ROOT}/tensorflow/lite/kernels/internal/common.cc
    ${TFLM_ROOT}/tensorflow/lite/kernels/kernel_util.cc
)

# Add schema utilities and error reporter (required for linking)
set(TFLM_SCHEMA_SOURCES
    ${TFLM_ROOT}/tensorflow/compiler/mlir/lite/schema/schema_utils.cc
    ${TFLM_ROOT}/tensorflow/compiler/mlir/lite/core/api/error_reporter.cc
)


# Combine all sources
set(TFLM_CC_SOURCES
    ${TFLM_MICRO_SOURCES}
    ${TFLM_KERNEL_SOURCES}
    ${TFLM_KERNEL_UTIL_SOURCES}
    ${TFLM_CORE_SOURCES}
    ${TFLM_PLATFORM_SOURCES}
    ${TFLM_SCHEMA_SOURCES}
)

# Add sources to the executable
target_sources(${PROJECT_NAME} PRIVATE
    # For segmentation entrypoint, replace main.cpp with:
    # ${CMAKE_CURRENT_SOURCE_DIR}/CoreCPP/Src/main_segmentation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CoreCPP/Src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CoreCPP/Src/tlfm_camvid.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CoreCPP/Src/tlfm_segmentation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CoreCPP/Src/tlfm_classification.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CoreCPP/Src/camvid_model_data.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/CoreCPP/Src/unet_model_data.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/CoreCPP/Src/nn_mnist_model_data.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/CoreCPP/Src/cnn_mnist_model_data.cc
    ${TFLM_CC_SOURCES}
)

# Include CMSIS DSP headers and TFLite Micro
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/DSP/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/CoreCPP/Inc
    ${TFLM_ROOT}
    ${TFLM_ROOT}/third_party/flatbuffers/include
    ${TFLM_ROOT}/third_party/gemmlowp
    ${TFLM_ROOT}/third_party/ruy
    ${TFLM_ROOT}/tensorflow/compiler/mlir/lite
)

# Add Core/Inc to embedDIP (PRIVATE since it's internal to this project)
target_include_directories(embedDIP PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -mcpu=cortex-m7
    -mfpu=fpv5-d16
    -mfloat-abi=hard
    -mthumb
    -Wall              # Enable common warnings
    -Wextra            # Enable even more warnings
    -Wno-unused-parameter  # (optional) disable annoying unused param warnings
    -ffunction-sections
    -fdata-sections
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
    stm32cubemx
    embedDIP
)
