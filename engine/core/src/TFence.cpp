#include "TFence.h"
#include "TDevice.h"
#include "TException.h"
#include "TVulkanAllocator.h"
#include "TVulkanLoader.h"
#include "vulkan/vulkan_core.h"
#include <vector>

void Turbo::Core::TFence::InternalCreate()
{
    VkFenceCreateInfo vk_fence_create_info = {};
    vk_fence_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    vk_fence_create_info.pNext = nullptr;
    vk_fence_create_info.flags = 0;

    VkDevice vk_device = this->device->GetVkDevice();
    VkAllocationCallbacks *allocator = Turbo::Core::TVulkanAllocator::Instance()->GetVkAllocationCallbacks();
    VkResult result = this->device->GetDeviceDriver()->vkCreateFence(vk_device, &vk_fence_create_info, allocator, &this->vkFence);
    if (result != VK_SUCCESS)
    {
        throw Turbo::Core::TException(TResult::INITIALIZATION_FAILED, "Turbo::Core::TFence::InternalCreate::vkCreateFence");
    }
}

void Turbo::Core::TFence::InternalDestroy()
{
    VkDevice vk_device = this->device->GetVkDevice();
    VkAllocationCallbacks *allocator = Turbo::Core::TVulkanAllocator::Instance()->GetVkAllocationCallbacks();
    this->device->GetDeviceDriver()->vkDestroyFence(vk_device, this->vkFence, allocator);
}

Turbo::Core::TFence::TFence(TDevice *device)
{
    if (device != nullptr)
    {
        this->device = device;
        this->InternalCreate();
    }
    else
    {
        throw Turbo::Core::TException(TResult::INVALID_PARAMETER, "Turbo::Core::TFence::TFence");
    }
}

Turbo::Core::TFence::~TFence()
{
    this->InternalDestroy();
}

Turbo::Core::TDevice *Turbo::Core::TFence::GetDevice()
{
    return this->device;
}

VkFence Turbo::Core::TFence::GetVkFence()
{
    return this->vkFence;
}

Turbo::Core::TResult Turbo::Core::TFence::Wait(uint64_t timeout)
{
    VkDevice vk_device = this->device->GetVkDevice();
    VkResult result = this->device->GetDeviceDriver()->vkWaitForFences(vk_device, 1, &this->vkFence, VK_TRUE, timeout);
    if (result != VkResult::VK_SUCCESS)
    {
        return TResult::TIMEOUT;
    }

    return TResult::SUCCESS;
}

void Turbo::Core::TFence::WaitUntil()
{
    VkDevice vk_device = this->device->GetVkDevice();
    VkResult result;
    do
    {
        result = this->device->GetDeviceDriver()->vkWaitForFences(vk_device, 1, &this->vkFence, VK_TRUE, UINT64_MAX);
    } while (result == VK_TIMEOUT);
}

std::string Turbo::Core::TFence::ToString()
{
    return std::string();
}

void Turbo::Core::TFences::Add(TFence *fence)
{
    if (fence != nullptr && fence->GetVkFence() != VK_NULL_HANDLE)
    {
        TDevice *device = fence->GetDevice();
        this->fenceMap[device].push_back(fence);
    }
}

Turbo::Core::TResult Turbo::Core::TFences::Wait(uint64_t timeout)
{
    for (std::pair<Turbo::Core::TDevice *const, std::vector<Turbo::Core::TFence *>> &fence_item : this->fenceMap)
    {
        std::vector<VkFence> vk_fences;
        for (Turbo::Core::TFence *fence_item : fence_item.second)
        {
            vk_fences.push_back(fence_item->GetVkFence());
        }
        TDevice *device = fence_item.first;
        VkResult result = device->GetDeviceDriver()->vkWaitForFences(device->GetVkDevice(), vk_fences.size(), vk_fences.data(), VK_TRUE, timeout);
        if (result != VkResult::VK_SUCCESS)
        {
            return TResult::TIMEOUT;
        }
    }

    return TResult::SUCCESS;
}

std::string Turbo::Core::TFences::ToString()
{
    return std::string();
}
