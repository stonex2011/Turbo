#pragma once
#ifndef TURBO_CORE_TVIEWPORT_H
#define TURBO_CORE_TVIEWPORT_H
#include "TInfo.h"

namespace Turbo
{
namespace Core
{
class TDevice;
class TPipeline;

class TViewport : public Turbo::Core::TInfo
{
  private:
    float x;
    float y;
    float width;
    float height;
    float minDepth;
    float maxDepth;

  public:
    TViewport(float x, float y, float width, float height, float minDepth, float maxDepth);
    ~TViewport();

    float GetX();
    float GetY();
    float GetWidth();
    float GetHeight();
    float GetMinDepth();
    float GetMaxDepth();

  public:
    virtual std::string ToString() override;
};

} // namespace Core
} // namespace Turbo
#endif // !TURBO_CORE_TVIEWPORT_H