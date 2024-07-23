cmake_minimum_required(VERSION 3.13)
set(PICO_SDK_FETCH_FROM_GIT on)
set(FREERTOS_KERNEL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/FreeRTOS-Kernel)
include(pico_sdk_import.cmake)
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

set(PROJECT "open-avian")

project(${PROJECT})

set(CMAKE_CXX_FLAGS "-Wall \
                    -mcpu=cortex-m0plus \
                    -mfpu=fpv4-sp-d16 \
                    -flto \
                    -O4 \
                    -Wshadow \
                    -Wunused-variable \
                    -Wunused-parameter \
                    -Wunused-function")

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

pico_sdk_init()

include_directories(include)
file(GLOB ${PROJECT}_SRC CONFIGURE_DEPENDS "include/*.h" "src/*.cpp")
add_executable(${PROJECT} ${${PROJECT}_SRC})

target_link_libraries(${PROJECT}
                      pico_stdlib
                      hardware_i2c
                      pico_multicore
                      FreeRTOS-Kernel-Heap4)

pico_add_extra_outputs(${PROJECT})
