#pragma once
#ifndef TURBO_CORE_TDEVICE_H
#define TURBO_CORE_TDEVICE_H
#include "TPhysicalDevice.h"
#include "TVulkanHandle.h"

namespace Turbo
{
namespace Core
{
class TDeviceCreateInfo;
class TQueueFamilyInfo;
class TDeviceQueue;
class TLayerInfo;
class TExtensionInfo;
class TVmaAllocator;
enum class TExtensionType;

struct TDeviceFunctionTable;
using TDeviceDriver = TDeviceFunctionTable;

class TDevice : public Turbo::Core::TVulkanHandle
{
  private:
    friend class TDeviceQueueCreateInfo;
    friend class TDeviceQueue;
    friend class TPhysicalDevice;

  private:
    T_VULKAN_HANDLE_PARENT TPhysicalDevice *physicalDevice = nullptr;
    T_VULKAN_HANDLE_HANDLE VkDevice vkDevice = VK_NULL_HANDLE;
    T_VULKAN_HANDLE_CHILDREN std::vector<TDeviceQueue *> deviceQueues;
    T_VULKAN_HANDLE_CHILDREN TVmaAllocator *vmaAllocator = nullptr;

    T_VULKAN_HANDLE_DATA std::vector<std::vector<float>> deviceQueuePriorities;

    T_VULKAN_HANDLE_DATA std::vector<TLayerInfo> enabledLayers;
    T_VULKAN_HANDLE_DATA std::vector<TExtensionInfo> enabledExtensions;
    T_VULKAN_HANDLE_DATA TPhysicalDeviceFeatures enabledFeatures;

    TDeviceDriver *deviceDriver = nullptr;

  protected:
    virtual void AddChildHandle(TDeviceQueue *deviceQueue);
    virtual TDeviceQueue *RemoveChildHandle(TDeviceQueue *deviceQueue);
    virtual void InternalCreate() override;
    virtual void InternalDestroy() override;
    virtual void InspectExtensionAndVersionDependencies(TExtensionType extensionType);

    uint32_t GetDeviceQueueCountByQueueFamily(TQueueFamilyInfo queueFamily);
    std::vector<TQueueFamilyInfo> GetDeviceQueueFamilyInfos();

  public:
    explicit TDevice(TPhysicalDevice *physicalDevice, std::vector<TLayerInfo> *enabledLayers = nullptr, std::vector<TExtensionInfo> *enabledExtensions = nullptr, TPhysicalDeviceFeatures *enableFeatures = nullptr);
    ~TDevice();

  public:
    VkDevice GetVkDevice();

    TPhysicalDevice *GetPhysicalDevice();

    size_t GetEnabledLayersCount();
    std::vector<TLayerInfo> GetEnabledLayers();

    size_t GetEnabledExtensionCount();
    std::vector<TExtensionInfo> GetEnabledExtensions();
    bool IsEnabledExtension(std::string extensionName);
    bool IsEnabledExtension(TExtensionType extensionType);

    TPhysicalDeviceFeatures GetEnableDeviceFeatures();

    TVmaAllocator *GetVmaAllocator();

    TDeviceQueue *GetBestGraphicsQueue();
    TDeviceQueue *GetBestComputeQueue();
    TDeviceQueue *GetBestTransferQueue();
    TDeviceQueue *GetBestSparseBindingQueue();
    TDeviceQueue *GetBestProtectedQueue();

    void WaitIdle();

    const TDeviceDriver *GetDeviceDriver();

    virtual std::string ToString() override;
};
} // namespace Core
} // namespace Turbo
#endif // !TURBO_CORE_TDEVICE_H
