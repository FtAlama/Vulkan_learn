-----

# learning

## Instance
A Vulkan instance is a global application context that initializes the Vulkan API,
loads available drivers, and provides access to physical devices and extensions.


## Layers
Layers are Vulkan error handling but for this course i will just skip it for now


## PhysicalDevice
Instance need to know connect to one or many physicals GPU and to do it we use the class :
```
vk::raii::PhysicalDevice
```

## Queue Family
There are different types of queues that originate from different queue families,
and each family of queues allows only a subset of commands.

For example, there could be a queue family that only allows processing of compute commands
or one that only allows memory transfer related commands.

## Queue
We need to specify which queues to create knowing that which queue families are available.

## LogicalDevice
The logical device creation process is similar to the instance creation process
and describes the features we want to use.


-----

# source

[vulkan pipeline in french](https://vulkan.developpez.com/articles/premier-pas/)

[vulkan official guide](https://docs.vulkan.org/tutorial/latest/01_Overview.html)

[vulkan sdk tuto](https://vulkan.lunarg.com/doc/sdk/latest/mac/getting_started.html)
