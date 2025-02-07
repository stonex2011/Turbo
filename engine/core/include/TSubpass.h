#pragma once
#ifndef TURBO_CORE_TSUBPASS_H
#define TURBO_CORE_TSUBPASS_H
#include "TImage.h"
#include "TInfo.h"
#include "TPipeline.h"

namespace Turbo
{
namespace Core
{

class TSubpass : public Turbo::Core::TInfo
{
  private:
    std::vector<VkAttachmentReference> *colors;
    std::vector<VkAttachmentReference> *resolves;
    std::vector<VkAttachmentReference> *inputs;
    std::vector<VkAttachmentReference> *preserves;
    VkAttachmentReference *depthStencil;
    TPipelineType type;

  public:
    TSubpass(TPipelineType type);
    TSubpass(const TSubpass &obj);
    ~TSubpass();

    void AddColorAttachmentReference(uint32_t attachment, TImageLayout layout);
    void AddResolveAttachmentReference(uint32_t attachment, TImageLayout layout);
    void AddInputAttachmentReference(uint32_t attachment, TImageLayout layout);
    void AddPreserveAttachmentReference(uint32_t attachment, TImageLayout layout);
    void SetDepthStencilAttachmentReference(uint32_t attachment, TImageLayout layout);
    void Clear();

    std::vector<VkAttachmentReference> *GetColorAttachmentReferences();
    std::vector<VkAttachmentReference> *GetResolveAttachmentReferences();
    std::vector<VkAttachmentReference> *GetInputAttachmentReferences();
    std::vector<VkAttachmentReference> *GetPreserveAttachmentReferences();
    VkAttachmentReference *GetDepthStencilAttachmentReference();

    TPipelineType GetPipelineType();

  public:
    virtual std::string ToString() override;
};

} // namespace Core
} // namespace Turbo
#endif // !TURBO_CORE_TSUBPASS_H