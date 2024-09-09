cmake_minimum_required(VERSION 3.13)
set(PICO_SDK_FETCH_FROM_GIT on)
set(PICO_BOARD pico_w)
set(FREERTOS_KERNEL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/FreeRTOS-Kernel)
include(pico_sdk_import.cmake)
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)
set(PROJECT "open-avian")

project(${PROJECT}
        LANGUAGES C CXX ASM
        DESCRIPTION "Open Avian - Firmware")

set(CMAKE_CXX_FLAGS "-Wall \
                    -mcpu=cortex-m0plus \
                    -mfpu=fpv4-sp-d16 \
                    -flto \
                    -O4 \
                    -Wshadow \
                    -Wunused-variable \
                    -Wunused-parameter \
                    -Wunused-function"
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

pico_sdk_init()

include_directories(include)
file(GLOB ${PROJECT}_SRC CONFIGURE_DEPENDS "include/*.h" "src/*.cpp")
add_executable(${PROJECT} ${${PROJECT}_SRC})

target_link_libraries(${PROJECT}
                      pico_stdlib
                      pico_cyw43_arch_none
                      hardware_i2c
                      pico_multicore
                      FreeRTOS
)

# Add FreeRTOS as a library
add_library(FreeRTOS STATIC
    ${FREERTOS_KERNEL_PATH}/event_groups.c
    ${FREERTOS_KERNEL_PATH}/list.c
    ${FREERTOS_KERNEL_PATH}/queue.c
    ${FREERTOS_KERNEL_PATH}/stream_buffer.c
    ${FREERTOS_KERNEL_PATH}/tasks.c
    ${FREERTOS_KERNEL_PATH}/timers.c
    ${FREERTOS_KERNEL_PATH}/portable/MemMang/heap_3.c
    ${FREERTOS_KERNEL_PATH}/portable/GCC/ARM_CM0/port.c
)

# Build FreeRTOS
target_include_directories(FreeRTOS PUBLIC
    ${FREERTOS_KERNEL_PATH}/
    ${FREERTOS_KERNEL_PATH}/include
    ${FREERTOS_KERNEL_PATH}/portable/GCC/ARM_CM0
)

pico_add_extra_outputs(${PROJECT})
