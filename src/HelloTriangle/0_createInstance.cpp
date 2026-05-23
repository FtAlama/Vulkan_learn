#include "HelloTriangleApplication.hpp"
#include <algorithm>
#include <iostream>

void HelloTriangleApplication::createInstance() {
  constexpr vk::ApplicationInfo appInfo{
      .pApplicationName = "Hello Triangle",
      .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
      .pEngineName = "No Engine",
      .engineVersion = VK_MAKE_VERSION(1, 0, 0),
      .apiVersion = vk::ApiVersion14};

  uint32_t glfwExtensionCount = 0;
  const char **glfwExtensions =
      glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
  if (!glfwExtensions) {
    throw std::runtime_error("Failed to get GLFW Vulkan extensions");
  }

  std::vector<const char *> extensionsName(glfwExtensions,
                                           glfwExtensions + glfwExtensionCount);

  extensionsName.push_back(vk::KHRPortabilityEnumerationExtensionName);
  extensionsName.push_back(vk::KHRGetPhysicalDeviceProperties2ExtensionName);

  auto extensionProperties = context.enumerateInstanceExtensionProperties();
  for (uint32_t i = 0; i < glfwExtensionCount; ++i) {
    if (std::ranges::none_of(
            extensionProperties,
            [glfwExtension = glfwExtensions[i]](auto const &extensionProperty) {
              return strcmp(extensionProperty.extensionName, glfwExtension) ==
                     0;
            }))
      throw std::runtime_error("Required GLFW extension not supported: " +
                               std::string(glfwExtensions[i]));
  }
  vk::InstanceCreateInfo createInfo{
      .flags = vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR,
      .pApplicationInfo = &appInfo,
      .enabledExtensionCount = static_cast<uint32_t>(extensionsName.size()),
      .ppEnabledExtensionNames = extensionsName.data()};

  instance = vk::raii::Instance(context, createInfo);
  auto extensions = context.enumerateInstanceExtensionProperties();
  std::cout << "available extensions:\n";

  for (const auto &extension : extensions) {
    std::cout << '\t' << extension.extensionName << '\n';
  }
}
