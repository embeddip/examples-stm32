cmake_minimum_required(VERSION 3.22)

project(dip-vs LANGUAGES C ASM)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

add_compile_definitions(STM32F746xx)

# Define the main executable FIRST
add_executable(${PROJECT_NAME})

# Now add stm32cubemx (which assumes dip-vs already exists)
add_subdirectory(cmake/stm32cubemx)

# Add embedDIP module
add_subdirectory(embedDIP)

# Add sources to the executable
target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/compress.c
)

# Include CMSIS DSP headers
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/DSP/Include
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
