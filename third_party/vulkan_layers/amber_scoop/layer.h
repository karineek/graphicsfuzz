/*
 * Copyright (C) 2018 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * THIS FILE WAS GENERATED BY apic. DO NOT EDIT.
 */

#include <unordered_map>
#include <vector>
#include "vulkan/vulkan.h"
#include "core/vulkan/layer_helpers/vulkan_layer_helpers.h"
#include "core/vulkan/layer_helpers/threading.h"
namespace graphicsfuzz_amber_scoop {
    typedef const VkAllocationCallbacks* AllocationCallbacks;
    typedef size_t size_val;

    // Sets the key of the dispatch tables used in lower layers of the parent
    // dispatchable handle to the new child dispatchable handle. This is necessary
    // as lower layers may use that key to find the dispatch table, and a child
    // handle should share the same dispatch table key. E.g. VkCommandBuffer is a
    // child dispatchable handle of VkDevice, all the VkCommandBuffer dispatching
    // functions are actually device functions (resolved by VkGetDeviceProcAddress).
    // Ref:
    // https://github.com/KhronosGroup/Vulkan-LoaderAndValidationLayers/blob/master/loader/LoaderAndLayerInterface.md#creating-new-dispatchable-objects,
    static inline void set_dispatch_from_parent(void *child, void *parent) {
        *((const void **)child) = *((const void **)parent);
    }

    struct InstanceFunctions {
        // Overriden Functions
        PFN_vkGetPhysicalDeviceMemoryProperties vkGetPhysicalDeviceMemoryProperties;
        // Stored pointers to call
    };
    struct DeviceFunctions {
        // Overriden Functions
        PFN_vkCreateBuffer vkCreateBuffer;
        PFN_vkBindBufferMemory vkBindBufferMemory;
        PFN_vkCreateCommandPool vkCreateCommandPool;
        PFN_vkCmdCopyBufferToImage vkCmdCopyBufferToImage;
        PFN_vkCreateDescriptorSetLayout vkCreateDescriptorSetLayout;
        PFN_vkAllocateDescriptorSets vkAllocateDescriptorSets;
        PFN_vkUpdateDescriptorSets vkUpdateDescriptorSets;
        PFN_vkCmdBindDescriptorSets vkCmdBindDescriptorSets;
        PFN_vkCmdBindIndexBuffer vkCmdBindIndexBuffer;
        PFN_vkCmdBindVertexBuffers vkCmdBindVertexBuffers;
        PFN_vkCmdDraw vkCmdDraw;
        PFN_vkCmdDrawIndexed vkCmdDrawIndexed;
        PFN_vkCreateImage vkCreateImage;
        PFN_vkBindImageMemory vkBindImageMemory;
        PFN_vkMapMemory vkMapMemory;
        PFN_vkCreatePipelineLayout vkCreatePipelineLayout;
        PFN_vkCreateGraphicsPipelines vkCreateGraphicsPipelines;
        PFN_vkCreateShaderModule vkCreateShaderModule;
        PFN_vkCmdBindPipeline vkCmdBindPipeline;
        PFN_vkQueueSubmit vkQueueSubmit;
        PFN_vkCreateFramebuffer vkCreateFramebuffer;
        PFN_vkCreateRenderPass vkCreateRenderPass;
        PFN_vkCmdBeginRenderPass vkCmdBeginRenderPass;
        PFN_vkCmdPipelineBarrier vkCmdPipelineBarrier;
        // Stored pointers to call
    };
    // All of the instance data that is needed for book-keeping in a layer.
    struct InstanceData {
        PFN_vkGetInstanceProcAddr get_instance_proc_addr;
        PFN_vkEnumeratePhysicalDevices enumerate_physical_devices;
        PFN_vkCreateDevice create_device;
        PFN_vkDestroyInstance destroy_instance;
        PFN_vkEnumerateDeviceExtensionProperties enumerate_device_extension_properties;
        InstanceFunctions* functions;
    };

    // All of the instance data that is needed for book-keeping in a layer.
    struct PhysicalDeviceData {
        VkInstance instance;
        PFN_vkCreateDevice create_device;
        InstanceFunctions* functions;
    };

    struct DeviceData {
        VkPhysicalDevice physical_device;
        VkInstance instance;
        PFN_vkGetDeviceProcAddr get_device_proc_addr;
        PFN_vkAllocateCommandBuffers allocate_command_buffers;
        PFN_vkGetDeviceQueue get_device_queue;
        PFN_vkDestroyDevice destroy_device;
        PFN_vkFreeCommandBuffers free_command_buffers;
        PFN_vkDestroyCommandPool destroy_command_pool;
        DeviceFunctions* functions;
    };

    struct QueueData {
        VkDevice device;
        DeviceFunctions* functions;
    };

    struct CommandBufferData {
        VkDevice device;
        VkCommandPool command_pool;
        DeviceFunctions* functions;
    };

    using Context = layer_helpers::Context<
    InstanceData,
    CommandBufferData,
    PhysicalDeviceData,
    QueueData,
    DeviceData>;
    Context &GetGlobalContext();
    VkResult vkCreateBuffer(PFN_vkCreateBuffer next, VkDevice device, VkBufferCreateInfo const* pCreateInfo, AllocationCallbacks pAllocator, VkBuffer* pBuffer);
    VkResult vkBindBufferMemory(PFN_vkBindBufferMemory next, VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset);
    VkResult vkCreateCommandPool(PFN_vkCreateCommandPool next, VkDevice device, VkCommandPoolCreateInfo const* pCreateInfo, AllocationCallbacks pAllocator, VkCommandPool* pCommandPool);
    void vkCmdCopyBufferToImage(PFN_vkCmdCopyBufferToImage next, VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, VkBufferImageCopy const* pRegions);
    VkResult vkCreateDescriptorSetLayout(PFN_vkCreateDescriptorSetLayout next, VkDevice device, VkDescriptorSetLayoutCreateInfo const* pCreateInfo, AllocationCallbacks pAllocator, VkDescriptorSetLayout* pSetLayout);
    VkResult vkAllocateDescriptorSets(PFN_vkAllocateDescriptorSets next, VkDevice device, VkDescriptorSetAllocateInfo const* pAllocateInfo, VkDescriptorSet* pDescriptorSets);
    void vkUpdateDescriptorSets(PFN_vkUpdateDescriptorSets next, VkDevice device, uint32_t descriptorWriteCount, VkWriteDescriptorSet const* pDescriptorWrites, uint32_t descriptorCopyCount, VkCopyDescriptorSet const* pDescriptorCopies);
    void vkCmdBindDescriptorSets(PFN_vkCmdBindDescriptorSets next, VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, VkDescriptorSet const* pDescriptorSets, uint32_t dynamicOffsetCount, uint32_t const* pDynamicOffsets);
    void vkCmdBindIndexBuffer(PFN_vkCmdBindIndexBuffer next, VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType);
    void vkCmdBindVertexBuffers(PFN_vkCmdBindVertexBuffers next, VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, VkBuffer const* pBuffers, VkDeviceSize const* pOffsets);
    void vkCmdDraw(PFN_vkCmdDraw next, VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
    void vkCmdDrawIndexed(PFN_vkCmdDrawIndexed next, VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance);
    VkResult vkCreateImage(PFN_vkCreateImage next, VkDevice device, VkImageCreateInfo const* pCreateInfo, AllocationCallbacks pAllocator, VkImage* pImage);
    VkResult vkBindImageMemory(PFN_vkBindImageMemory next, VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset);
    VkResult vkMapMemory(PFN_vkMapMemory next, VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData);
    VkResult vkCreatePipelineLayout(PFN_vkCreatePipelineLayout next, VkDevice device, VkPipelineLayoutCreateInfo const* pCreateInfo, AllocationCallbacks pAllocator, VkPipelineLayout* pPipelineLayout);
    VkResult vkCreateGraphicsPipelines(PFN_vkCreateGraphicsPipelines next, VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, VkGraphicsPipelineCreateInfo const* pCreateInfos, AllocationCallbacks pAllocator, VkPipeline* pPipelines);
    VkResult vkCreateShaderModule(PFN_vkCreateShaderModule next, VkDevice device, VkShaderModuleCreateInfo const* pCreateInfo, AllocationCallbacks pAllocator, VkShaderModule* pShaderModule);
    void vkCmdBindPipeline(PFN_vkCmdBindPipeline next, VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline);
    void vkGetPhysicalDeviceMemoryProperties(PFN_vkGetPhysicalDeviceMemoryProperties next, VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties* pMemoryProperties);
    VkResult vkQueueSubmit(PFN_vkQueueSubmit next, VkQueue queue, uint32_t submitCount, VkSubmitInfo const* pSubmits, VkFence fence);
    VkResult vkCreateFramebuffer(PFN_vkCreateFramebuffer next, VkDevice device, VkFramebufferCreateInfo const* pCreateInfo, AllocationCallbacks pAllocator, VkFramebuffer* pFramebuffer);
    VkResult vkCreateRenderPass(PFN_vkCreateRenderPass next, VkDevice device, VkRenderPassCreateInfo const* pCreateInfo, AllocationCallbacks pAllocator, VkRenderPass* pRenderPass);
    void vkCmdBeginRenderPass(PFN_vkCmdBeginRenderPass next, VkCommandBuffer commandBuffer, VkRenderPassBeginInfo const* pRenderPassBegin, VkSubpassContents contents);
    void vkCmdPipelineBarrier(PFN_vkCmdPipelineBarrier next, VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, VkMemoryBarrier const* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, VkBufferMemoryBarrier const* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, VkImageMemoryBarrier const* pImageMemoryBarriers);
}