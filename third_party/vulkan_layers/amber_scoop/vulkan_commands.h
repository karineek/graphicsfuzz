/*
 * Copyright 2020 The GraphicsFuzz Project Authors
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
 */

#ifndef GRAPHICSFUZZ_VULKAN_LAYERS_VULKAN_COMMANDS_H
#define GRAPHICSFUZZ_VULKAN_LAYERS_VULKAN_COMMANDS_H

#include "vk_deep_copy.h"
#include <vulkan/vulkan_core.h>

namespace graphicsfuzz_amber_scoop {

struct CmdBeginRenderPass;
struct CmdBindDescriptorSets;
struct CmdBindIndexBuffer;
struct CmdBindPipeline;
struct CmdBindVertexBuffers;
struct CmdCopyBuffer;
struct CmdCopyBufferToImage;
struct CmdDraw;
struct CmdDrawIndexed;
struct CmdPipelineBarrier;

struct Cmd {

  enum Kind {
    kBeginRenderPass,
    kBindDescriptorSets,
    kBindIndexBuffer,
    kBindPipeline,
    kBindVertexBuffers,
    kCopyBuffer,
    kCopyBufferToImage,
    kDraw,
    kDrawIndexed,
    kPipelineBarrier
  };

  explicit Cmd(Kind kind) : kind_(kind) {}

// A bunch of methods for casting this type to a given type. Returns this if the
// cast can be done, nullptr otherwise.
// clang-format off
#define DeclareCastMethod(target)                                              \
  virtual Cmd##target *As##target() { return nullptr; }                        \
  virtual const Cmd##target *As##target() const { return nullptr; }
  DeclareCastMethod(BeginRenderPass)
  DeclareCastMethod(BindDescriptorSets)
  DeclareCastMethod(BindIndexBuffer)
  DeclareCastMethod(BindPipeline)
  DeclareCastMethod(BindVertexBuffers)
  DeclareCastMethod(CopyBuffer)
  DeclareCastMethod(CopyBufferToImage)
  DeclareCastMethod(Draw)
  DeclareCastMethod(DrawIndexed)
  DeclareCastMethod(PipelineBarrier)
#undef DeclareCastMethod

  Kind kind_;
  // clang-format on
};

struct CmdBeginRenderPass : public Cmd {
  CmdBeginRenderPass(VkRenderPassBeginInfo const *pRenderPassBegin,
                     VkSubpassContents contents)
      : Cmd(kBeginRenderPass), pRenderPassBegin_(DeepCopy(pRenderPassBegin)),
        contents_(contents) {}

  CmdBeginRenderPass *AsBeginRenderPass() override { return this; }
  const CmdBeginRenderPass *AsBeginRenderPass() const override { return this; }

  VkRenderPassBeginInfo *pRenderPassBegin_;
  VkSubpassContents contents_;
};

struct CmdBindDescriptorSets : public Cmd {

  CmdBindDescriptorSets(VkPipelineBindPoint pipelineBindPoint,
                        VkPipelineLayout layout, uint32_t firstSet,
                        uint32_t descriptorSetCount,
                        VkDescriptorSet const *pDescriptorSets,
                        uint32_t dynamicOffsetCount,
                        uint32_t const *pDynamicOffsets)
      : Cmd(kBindDescriptorSets), pipelineBindPoint_(pipelineBindPoint),
        layout_(layout), firstSet_(firstSet),
        descriptorSetCount_(descriptorSetCount),
        pDescriptorSets_(CopyArray(pDescriptorSets, descriptorSetCount)),
        dynamicOffsetCount_(dynamicOffsetCount),
        pDynamicOffsets_(CopyArray(pDynamicOffsets, dynamicOffsetCount)) {}

  CmdBindDescriptorSets *AsBindDescriptorSets() override { return this; }
  const CmdBindDescriptorSets *AsBindDescriptorSets() const override {
    return this;
  }

  VkPipelineBindPoint pipelineBindPoint_;
  VkPipelineLayout layout_;
  uint32_t firstSet_;
  uint32_t descriptorSetCount_;
  VkDescriptorSet *pDescriptorSets_;
  uint32_t dynamicOffsetCount_;
  uint32_t *pDynamicOffsets_;
};

struct CmdBindIndexBuffer : public Cmd {

  CmdBindIndexBuffer(VkBuffer buffer, VkDeviceSize offset,
                     VkIndexType indexType)
      : Cmd(kBindIndexBuffer), buffer_(buffer), offset_(offset),
        indexType_(indexType) {}

  CmdBindIndexBuffer *AsBindIndexBuffer() override { return this; }
  const CmdBindIndexBuffer *AsBindIndexBuffer() const override { return this; }

  VkBuffer buffer_;
  VkDeviceSize offset_;
  VkIndexType indexType_;
};

struct CmdBindPipeline : public Cmd {
  CmdBindPipeline(VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline)
      : Cmd(kBindPipeline), pipelineBindPoint_(pipelineBindPoint),
        pipeline_(pipeline) {}

  CmdBindPipeline *AsBindPipeline() override { return this; }
  const CmdBindPipeline *AsBindPipeline() const override { return this; }

  VkPipelineBindPoint pipelineBindPoint_;
  VkPipeline pipeline_;
};

struct CmdBindVertexBuffers : public Cmd {

  CmdBindVertexBuffers(uint32_t firstBinding, uint32_t bindingCount,
                       VkBuffer const *pBuffers, VkDeviceSize const *pOffsets)
      : Cmd(kBindVertexBuffers), firstBinding_(firstBinding),
        bindingCount_(bindingCount),
        pBuffers_(CopyArray(pBuffers, bindingCount)),
        pOffsets_(CopyArray(pOffsets, bindingCount)) {}

  CmdBindVertexBuffers *AsBindVertexBuffers() override { return this; }
  const CmdBindVertexBuffers *AsBindVertexBuffers() const override {
    return this;
  }

  uint32_t firstBinding_;
  uint32_t bindingCount_;
  VkBuffer const *pBuffers_;
  VkDeviceSize const *pOffsets_;
};

struct CmdCopyBuffer : public Cmd {
  CmdCopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount,
                VkBufferCopy const *pRegions)
      : Cmd(kCopyBuffer), srcBuffer_(srcBuffer), dstBuffer_(dstBuffer),
        regionCount_(regionCount), pRegions_(pRegions) {}

  CmdCopyBuffer *AsCopyBuffer() override { return this; }
  const CmdCopyBuffer *AsCopyBuffer() const override { return this; }

  VkBuffer srcBuffer_;
  VkBuffer dstBuffer_;
  uint32_t regionCount_;
  VkBufferCopy const *pRegions_;
};

struct CmdCopyBufferToImage : public Cmd {
  CmdCopyBufferToImage(VkBuffer srcBuffer, VkImage dstImage,
                       VkImageLayout dstImageLayout, uint32_t regionCount,
                       VkBufferImageCopy const *pRegions)
      : Cmd(kCopyBufferToImage), srcBuffer_(srcBuffer), dstImage_(dstImage),
        dstImageLayout_(dstImageLayout), regionCount_(regionCount),
        pRegions_(CopyArray(pRegions, regionCount)) {}

  CmdCopyBufferToImage *AsCopyBufferToImage() override { return this; }
  const CmdCopyBufferToImage *AsCopyBufferToImage() const override {
    return this;
  }

  VkBuffer srcBuffer_;
  VkImage dstImage_;
  VkImageLayout dstImageLayout_;
  uint32_t regionCount_;
  VkBufferImageCopy const *pRegions_;
};

struct CmdDraw : public Cmd {
  CmdDraw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex,
          uint32_t firstInstance)
      : Cmd(kDraw), vertexCount_(vertexCount), instanceCount_(instanceCount),
        firstVertex_(firstVertex), firstInstance_(firstInstance) {}

  CmdDraw *AsDraw() override { return this; }
  const CmdDraw *AsDraw() const override { return this; }

  uint32_t vertexCount_;
  uint32_t instanceCount_;
  uint32_t firstVertex_;
  uint32_t firstInstance_;
};

struct CmdDrawIndexed : public Cmd {
  CmdDrawIndexed(uint32_t indexCount, uint32_t instanceCount,
                 uint32_t firstIndex, int32_t vertexOffset,
                 uint32_t firstInstance)
      : Cmd(kDrawIndexed), indexCount_(indexCount),
        instanceCount_(instanceCount), firstIndex_(firstIndex),
        vertexOffset_(vertexOffset), firstInstance_(firstInstance) {}

  CmdDrawIndexed *AsDrawIndexed() override { return this; }
  const CmdDrawIndexed *AsDrawIndexed() const override { return this; }

  uint32_t indexCount_;
  uint32_t instanceCount_;
  uint32_t firstIndex_;
  int32_t vertexOffset_;
  uint32_t firstInstance_;
};

struct CmdPipelineBarrier : public Cmd {
  CmdPipelineBarrier(VkPipelineStageFlags srcStageMask,
                     VkPipelineStageFlags dstStageMask,
                     VkDependencyFlags dependencyFlags,
                     uint32_t memoryBarrierCount,
                     VkMemoryBarrier const *pMemoryBarriers,
                     uint32_t bufferMemoryBarrierCount,
                     VkBufferMemoryBarrier const *pBufferMemoryBarriers,
                     uint32_t imageMemoryBarrierCount,
                     VkImageMemoryBarrier const *pImageMemoryBarriers)
      : Cmd(kPipelineBarrier), srcStageMask_(srcStageMask),
        dstStageMask_(dstStageMask), dependencyFlags_(dependencyFlags),
        memoryBarrierCount_(memoryBarrierCount),
        pMemoryBarriers_(CopyArray(pMemoryBarriers, memoryBarrierCount)),
        bufferMemoryBarrierCount_(bufferMemoryBarrierCount),
        pBufferMemoryBarriers_(
            CopyArray(pBufferMemoryBarriers, bufferMemoryBarrierCount)),
        imageMemoryBarrierCount_(imageMemoryBarrierCount),
        pImageMemoryBarriers_(
            CopyArray(pImageMemoryBarriers, imageMemoryBarrierCount)) {}

  CmdPipelineBarrier *AsPipelineBarrier() override { return this; }
  const CmdPipelineBarrier *AsPipelineBarrier() const override { return this; }

  VkPipelineStageFlags srcStageMask_;
  VkPipelineStageFlags dstStageMask_;
  VkDependencyFlags dependencyFlags_;
  uint32_t memoryBarrierCount_;
  VkMemoryBarrier const *pMemoryBarriers_;
  uint32_t bufferMemoryBarrierCount_;
  VkBufferMemoryBarrier const *pBufferMemoryBarriers_;
  uint32_t imageMemoryBarrierCount_;
  VkImageMemoryBarrier const *pImageMemoryBarriers_;
};

} // namespace graphicsfuzz_amber_scoop

#endif // GRAPHICSFUZZ_VULKAN_LAYERS_VULKAN_COMMANDS_H
