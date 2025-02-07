#include "TDescriptorSetLayout.h"
#include "TDescriptor.h"
#include "TDevice.h"
#include "TException.h"
#include "TShader.h"
#include "TVulkanAllocator.h"
#include "TVulkanLoader.h"

void Turbo::Core::TDescriptorSetLayout::InternalCreate()
{
    std::map</*binding*/ uint32_t, std::vector<TDescriptor *>> binding_map;
    for (TDescriptor *descriptor_item : this->descriptors)
    {
        uint32_t binding = descriptor_item->GetBinding();
        TShader *shader = descriptor_item->GetShader();
        if (shader != nullptr)
        {
            binding_map[binding].push_back(descriptor_item);
        }
    }

    std::vector<VkDescriptorSetLayoutBinding> bindings;
    for (auto &descriptors_item : binding_map)
    {
        std::vector<Turbo::Core::TDescriptor *> &descriptors = descriptors_item.second;
        if (descriptors.size() > 0)
        {
            TDescriptor *descriptor = descriptors[0];
            if (descriptor != nullptr)
            {
                VkDescriptorSetLayoutBinding vk_descriptor_set_layout_binding = {};
                vk_descriptor_set_layout_binding.binding = descriptor->GetBinding();
                vk_descriptor_set_layout_binding.descriptorType = descriptor->GetVkDescriptorType();
                vk_descriptor_set_layout_binding.descriptorCount = descriptor->GetCount();
                vk_descriptor_set_layout_binding.stageFlags = 0;
                for (TDescriptor *descriptor_item : descriptors)
                {
                    TShader *shader = descriptor_item->GetShader();
                    if (shader != nullptr)
                    {
                        vk_descriptor_set_layout_binding.stageFlags |= descriptor_item->GetShader()->GetVkShaderStageFlags();
                    }
                }
                vk_descriptor_set_layout_binding.pImmutableSamplers = nullptr;

                bindings.push_back(vk_descriptor_set_layout_binding);
            }
            else
            {
                throw Turbo::Core::TException(TResult::INVALID_PARAMETER, "Turbo::Core::TDescriptorSetLayout::InternalCreate");
            }
        }
    }

    VkDescriptorSetLayoutCreateInfo vk_descriptor_set_layout_create_info={};
    vk_descriptor_set_layout_create_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    vk_descriptor_set_layout_create_info.pNext = nullptr;
    vk_descriptor_set_layout_create_info.flags = 0;
    vk_descriptor_set_layout_create_info.bindingCount = bindings.size();
    vk_descriptor_set_layout_create_info.pBindings = bindings.data();

    VkDevice vk_device = this->device->GetVkDevice();
    VkAllocationCallbacks *allocator = Turbo::Core::TVulkanAllocator::Instance()->GetVkAllocationCallbacks();
    VkResult result = this->device->GetDeviceDriver()->vkCreateDescriptorSetLayout(vk_device, &vk_descriptor_set_layout_create_info, allocator, &this->vkDescriptorSetLayout);
    if (result != VK_SUCCESS)
    {
        throw Turbo::Core::TException(TResult::INITIALIZATION_FAILED, "Turbo::Core::TDescriptorSetLayout::InternalCreate::vkCreateDescriptorSetLayout");
    }
}

void Turbo::Core::TDescriptorSetLayout::TDescriptorSetLayout::InternalDestroy()
{
    VkDevice vk_device = this->device->GetVkDevice();
    VkAllocationCallbacks *allocator = Turbo::Core::TVulkanAllocator::Instance()->GetVkAllocationCallbacks();
    this->device->GetDeviceDriver()->vkDestroyDescriptorSetLayout(vk_device, this->vkDescriptorSetLayout, allocator);
}

Turbo::Core::TDescriptorSetLayout::TDescriptorSetLayout(TDevice *device, std::vector<TDescriptor *> &descriptors) : Turbo::Core::TVulkanHandle()
{
    if (device != nullptr)
    {
        this->device = device;
        this->descriptors = descriptors;
        this->InternalCreate();
    }
    else
    {
        throw Turbo::Core::TException(TResult::INVALID_PARAMETER, "Turbo::Core::TDescriptorSetLayout::TDescriptorSetLayout");
    }
}

Turbo::Core::TDescriptorSetLayout::~TDescriptorSetLayout()
{
    this->InternalDestroy();

    // TODO: release Turbo::Core::TNaNDescriptor
    for (TDescriptor *depcriptor_item : this->descriptors)
    {
        if (depcriptor_item->GetShader() == nullptr) // this is Turbo::Core::TNaNDescriptor
        {
            delete depcriptor_item;
        }
    }
}

uint32_t Turbo::Core::TDescriptorSetLayout::GetSet()
{
    return this->descriptors[0]->GetSet();
}

VkDescriptorSetLayout Turbo::Core::TDescriptorSetLayout::GetVkDescriptorSetLayout()
{
    return this->vkDescriptorSetLayout;
}

Turbo::Core::TDescriptorType Turbo::Core::TDescriptorSetLayout::GetDescriptorType(uint32_t binding)
{
    for (TDescriptor *dscriptor_item : this->descriptors)
    {
        if (dscriptor_item->GetBinding() == binding)
        {
            return dscriptor_item->GetType();
        }
    }

    throw Turbo::Core::TException(TResult::OUT_OF_RANGE, "Turbo::Core::TDescriptorSetLayout::TDescriptorSetLayout", "not finding the type binding please check the binding index");
}

std::string Turbo::Core::TDescriptorSetLayout::ToString()
{
    return std::string();
}
