cmake_minimum_required(VERSION 4.3.1)
set(APP_NAME test)

project(${APP_NAME} VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${APP_NAME}
	src/main.cpp
	src/HelloTriangle/0_createInstance.cpp
	src/HelloTriangle/1_pickPhysicalDevice.cpp
)



target_compile_definitions(${APP_NAME} PRIVATE
    VULKAN_HPP_NO_CONSTRUCTORS
)

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
	include
)

target_link_libraries(${APP_NAME}
	glfw
	Vulkan::Vulkan
)
