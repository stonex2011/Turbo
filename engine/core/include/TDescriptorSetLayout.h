#pragma once
#ifndef TURBO_CORE_TDESCRIPTORSETLAYOUT_H
#define TURBO_CORE_DESCRIPTORSETLAYOUT_H
#include "TDescriptor.h"
#include "TVulkanHandle.h"


namespace Turbo
{
namespace Core
{
class TDevice;

class TDescriptorSetLayout : public Turbo::Core::TVulkanHandle
{
  private:
    T_VULKAN_HANDLE_PARENT TDevice *device = nullptr;
    T_VULKAN_HANDLE_HANDLE VkDescriptorSetLayout vkDescriptorSetLayout = VK_NULL_HANDLE;

    T_VULKAN_HANDLE_DATA std::vector<TDescriptor *> descriptors;

  protected:
    virtual void InternalCreate() override;
    virtual void InternalDestroy() override;

  public:
    TDescriptorSetLayout(TDevice *device, std::vector<TDescriptor *> &descriptors);
    ~TDescriptorSetLayout();

    uint32_t GetSet();
    VkDescriptorSetLayout GetVkDescriptorSetLayout();

    TDescriptorType GetDescriptorType(uint32_t binding);

    virtual std::string ToString() override;
};

} // namespace Core
} // namespace Turbo
#endif // !TURBO_CORE_TDESCRIPTORSETLAYOUT_H