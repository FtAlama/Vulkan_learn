cmake_minimum_required(VERSION 4.3.1)
set(APP_NAME test)

project(${APP_NAME} VERSION 1.0.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${APP_NAME}
	src/main.cpp
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

target_compile_options(${APP_NAME} PRIVATE
    -Wall
    -Wextra
    -Werror
)

find_package(Vulkan REQUIRED)

add_subdirectory(dependencies/glfw-3.4)

target_include_directories(${APP_NAME}
	PRIVATE
	dependencies
)

target_link_libraries(${APP_NAME}
	glfw
	Vulkan::Vulkan
)
