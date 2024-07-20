cmake_minimum_required(VERSION 3.13)
set(PICO_SDK_FETCH_FROM_GIT on)
include(pico_sdk_import.cmake)

set(PROJECT "rpi-pioc")

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

target_link_libraries(${PROJECT} pico_stdlib)

pico_add_extra_outputs(${PROJECT})
