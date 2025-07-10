cmake_minimum_required(VERSION 3.13)

# 1) Point to the Pico SDK root on your system
set(PICO_SDK_PATH "E:/ENTREPRENEURSHIP/summer2025embedded/Pico/pico-sdk")

# 2) Include the Pico SDK import wrapper
include("${PICO_SDK_PATH}/external/pico_sdk_import.cmake")

# 3) Declare your project *before* initializing the SDK
project(Cppembed C CXX ASM)

# 4) Initialize the Pico SDK (sets up all internal include dirs, toolchain, etc.)
pico_sdk_init()

# 5) Manually add the ADC include directory for hardware/adc.h
include_directories(
  "${PICO_SDK_PATH}/src/rp2_common/hardware_adc/include"
)

# 6) (Optional) export compile_commands.json for editor integrations
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 7) Gather whichever day’s .cpp file you’ve placed here
file(GLOB DAY_SOURCE "${CMAKE_CURRENT_LIST_DIR}/*.cpp")

# 8) Build your firmware executable
add_executable(my_pico_firmware ${DAY_SOURCE})

# 9) Link against the Pico standard library (brings in stdio, gpio, etc.)
target_link_libraries(my_pico_firmware
  pico_stdlib       # core stdio, time, etc.
  hardware_adc      # pulls in the ADC driver implementation
)

# 10) Produce a UF2 you can drag onto the Pico
pico_add_extra_outputs(my_pico_firmware)
