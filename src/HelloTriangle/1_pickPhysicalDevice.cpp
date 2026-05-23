#include "HelloTriangleApplication.hpp"
#include "vulkan/vulkan.hpp"
#include <stdexcept>

bool HelloTriangleApplication::isDeviceSuitable(
    vk::raii::PhysicalDevice const &physicalDevice) {

  bool supportVulkan1_3 =
      physicalDevice.getProperties().apiVersion >= vk::ApiVersion13;
  auto queueFamilies = physicalDevice.getQueueFamilyProperties();
  bool supportGraphics =
      std::ranges::any_of(queueFamilies, [](auto const &qfp) {
        return !!(qfp.queueFlags & vk::QueueFlagBits::eGraphics);
      });
  auto availableDeviceExtensions =
      physicalDevice.enumerateDeviceExtensionProperties();
  bool supportAllRequiredExtensions = std::ranges::all_of(
      requiredDeviceExtension,
      [&availableDeviceExtensions](auto const &requiredDeviceExtension) {
        return std::ranges::any_of(
            availableDeviceExtensions,
            [requiredDeviceExtension](auto const &availableDeviceExtension) {
              return strcmp(availableDeviceExtension.extensionName,
                            requiredDeviceExtension) == 0;
            });
      });

  auto features = physicalDevice.template getFeatures2<
      vk::PhysicalDeviceFeatures2, vk::PhysicalDeviceVulkan13Features,
      vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>();

  bool supportsRequiredFeatures =
      features.template get<vk::PhysicalDeviceVulkan13Features>()
          .dynamicRendering &&
      features.template get<vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>()
          .extendedDynamicState;

  return supportVulkan1_3 && supportGraphics && supportsRequiredFeatures &&
         supportAllRequiredExtensions;
}

void HelloTriangleApplication::pickPhysicalDevice() {
  auto physicalDevices = instance.enumeratePhysicalDevices();

  auto const devItr =
      std::ranges::find_if(physicalDevices, [&](auto const physicalDevice) {
        return isDeviceSuitable(physicalDevice);
      });
  if (devItr == physicalDevices.end()) {
    throw std::runtime_error("failed to find a suitable GPU!");
  }
  this->physicalDevice = *devItr;
}
