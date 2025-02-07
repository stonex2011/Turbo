#pragma once
#ifndef TURBO_CORE_TFORMAT_H
#define TURBO_CORE_TFORMAT_H
#include "TObject.h"

namespace Turbo
{
namespace Core
{
class TDevice;

typedef enum class TFormatType
{
    UNDEFINED = VkFormat::VK_FORMAT_UNDEFINED,
    R4G4_UNORM_PACK8 = VkFormat::VK_FORMAT_R4G4_UNORM_PACK8,
    R4G4B4A4_UNORM_PACK16 = VkFormat::VK_FORMAT_R4G4B4A4_UNORM_PACK16,
    B4G4R4A4_UNORM_PACK16 = VkFormat::VK_FORMAT_B4G4R4A4_UNORM_PACK16,
    R5G6B5_UNORM_PACK16 = VkFormat::VK_FORMAT_R5G6B5_UNORM_PACK16,
    B5G6R5_UNORM_PACK16 = VkFormat::VK_FORMAT_B5G6R5_UNORM_PACK16,
    R5G5B5A1_UNORM_PACK16 = VkFormat::VK_FORMAT_R5G5B5A1_UNORM_PACK16,
    B5G5R5A1_UNORM_PACK16 = VkFormat::VK_FORMAT_B5G5R5A1_UNORM_PACK16,
    A1R5G5B5_UNORM_PACK16 = VkFormat::VK_FORMAT_A1R5G5B5_UNORM_PACK16,
    R8_UNORM = VkFormat::VK_FORMAT_R8_UNORM,
    R8_SNORM = VkFormat::VK_FORMAT_R8_SNORM,
    R8_USCALED = VkFormat::VK_FORMAT_R8_USCALED,
    R8_SSCALED = VkFormat::VK_FORMAT_R8_SSCALED,
    R8_UINT = VkFormat::VK_FORMAT_R8_UINT,
    R8_SINT = VkFormat::VK_FORMAT_R8_SINT,
    R8_SRGB = VkFormat::VK_FORMAT_R8_SRGB,
    R8G8_UNORM = VkFormat::VK_FORMAT_R8G8_UNORM,
    R8G8_SNORM = VkFormat::VK_FORMAT_R8G8_SNORM,
    R8G8_USCALED = VkFormat::VK_FORMAT_R8G8_USCALED,
    R8G8_SSCALED = VkFormat::VK_FORMAT_R8G8_SSCALED,
    R8G8_UINT = VkFormat::VK_FORMAT_R8G8_UINT,
    R8G8_SINT = VkFormat::VK_FORMAT_R8G8_SINT,
    R8G8_SRGB = VkFormat::VK_FORMAT_R8G8_SRGB,
    R8G8B8_UNORM = VkFormat::VK_FORMAT_R8G8B8_UNORM,
    R8G8B8_SNORM = VkFormat::VK_FORMAT_R8G8B8_SNORM,
    R8G8B8_USCALED = VkFormat::VK_FORMAT_R8G8B8_USCALED,
    R8G8B8_SSCALED = VkFormat::VK_FORMAT_R8G8B8_SSCALED,
    R8G8B8_UINT = VkFormat::VK_FORMAT_R8G8B8_UINT,
    R8G8B8_SINT = VkFormat::VK_FORMAT_R8G8B8_SINT,
    R8G8B8_SRGB = VkFormat::VK_FORMAT_R8G8B8_SRGB,
    B8G8R8_UNORM = VkFormat::VK_FORMAT_B8G8R8_UNORM,
    B8G8R8_SNORM = VkFormat::VK_FORMAT_B8G8R8_SNORM,
    B8G8R8_USCALED = VkFormat::VK_FORMAT_B8G8R8_USCALED,
    B8G8R8_SSCALED = VkFormat::VK_FORMAT_B8G8R8_SSCALED,
    B8G8R8_UINT = VkFormat::VK_FORMAT_B8G8R8_UINT,
    B8G8R8_SINT = VkFormat::VK_FORMAT_B8G8R8_SINT,
    B8G8R8_SRGB = VkFormat::VK_FORMAT_B8G8R8_SRGB,
    R8G8B8A8_UNORM = VkFormat::VK_FORMAT_R8G8B8A8_UNORM,
    R8G8B8A8_SNORM = VkFormat::VK_FORMAT_R8G8B8A8_SNORM,
    R8G8B8A8_USCALED = VkFormat::VK_FORMAT_R8G8B8A8_USCALED,
    R8G8B8A8_SSCALED = VkFormat::VK_FORMAT_R8G8B8A8_SSCALED,
    R8G8B8A8_UINT = VkFormat::VK_FORMAT_R8G8B8A8_UINT,
    R8G8B8A8_SINT = VkFormat::VK_FORMAT_R8G8B8A8_SINT,
    R8G8B8A8_SRGB = VkFormat::VK_FORMAT_R8G8B8A8_SRGB,
    B8G8R8A8_UNORM = VkFormat::VK_FORMAT_B8G8R8A8_UNORM,
    B8G8R8A8_SNORM = VkFormat::VK_FORMAT_B8G8R8A8_SNORM,
    B8G8R8A8_USCALED = VkFormat::VK_FORMAT_B8G8R8A8_USCALED,
    B8G8R8A8_SSCALED = VkFormat::VK_FORMAT_B8G8R8A8_SSCALED,
    B8G8R8A8_UINT = VkFormat::VK_FORMAT_B8G8R8A8_UINT,
    B8G8R8A8_SINT = VkFormat::VK_FORMAT_B8G8R8A8_SINT,
    B8G8R8A8_SRGB = VkFormat::VK_FORMAT_B8G8R8A8_SRGB,
    A8B8G8R8_UNORM_PACK32 = VkFormat::VK_FORMAT_A8B8G8R8_UNORM_PACK32,
    A8B8G8R8_SNORM_PACK32 = VkFormat::VK_FORMAT_A8B8G8R8_SNORM_PACK32,
    A8B8G8R8_USCALED_PACK32 = VkFormat::VK_FORMAT_A8B8G8R8_USCALED_PACK32,
    A8B8G8R8_SSCALED_PACK32 = VkFormat::VK_FORMAT_A8B8G8R8_SSCALED_PACK32,
    A8B8G8R8_UINT_PACK32 = VkFormat::VK_FORMAT_A8B8G8R8_UINT_PACK32,
    A8B8G8R8_SINT_PACK32 = VkFormat::VK_FORMAT_A8B8G8R8_SINT_PACK32,
    A8B8G8R8_SRGB_PACK32 = VkFormat::VK_FORMAT_A8B8G8R8_SRGB_PACK32,
    A2R10G10B10_UNORM_PACK32 = VkFormat::VK_FORMAT_A2R10G10B10_UNORM_PACK32,
    A2R10G10B10_SNORM_PACK32 = VkFormat::VK_FORMAT_A2R10G10B10_SNORM_PACK32,
    A2R10G10B10_USCALED_PACK32 = VkFormat::VK_FORMAT_A2R10G10B10_USCALED_PACK32,
    A2R10G10B10_SSCALED_PACK32 = VkFormat::VK_FORMAT_A2R10G10B10_SSCALED_PACK32,
    A2R10G10B10_UINT_PACK32 = VkFormat::VK_FORMAT_A2R10G10B10_UINT_PACK32,
    A2R10G10B10_SINT_PACK32 = VkFormat::VK_FORMAT_A2R10G10B10_SINT_PACK32,
    A2B10G10R10_UNORM_PACK32 = VkFormat::VK_FORMAT_A2B10G10R10_UNORM_PACK32,
    A2B10G10R10_SNORM_PACK32 = VkFormat::VK_FORMAT_A2B10G10R10_SNORM_PACK32,
    A2B10G10R10_USCALED_PACK32 = VkFormat::VK_FORMAT_A2B10G10R10_USCALED_PACK32,
    A2B10G10R10_SSCALED_PACK32 = VkFormat::VK_FORMAT_A2B10G10R10_SSCALED_PACK32,
    A2B10G10R10_UINT_PACK32 = VkFormat::VK_FORMAT_A2B10G10R10_UINT_PACK32,
    A2B10G10R10_SINT_PACK32 = VkFormat::VK_FORMAT_A2B10G10R10_SINT_PACK32,
    R16_UNORM = VkFormat::VK_FORMAT_R16_UNORM,
    R16_SNORM = VkFormat::VK_FORMAT_R16_SNORM,
    R16_USCALED = VkFormat::VK_FORMAT_R16_USCALED,
    R16_SSCALED = VkFormat::VK_FORMAT_R16_SSCALED,
    R16_UINT = VkFormat::VK_FORMAT_R16_UINT,
    R16_SINT = VkFormat::VK_FORMAT_R16_SINT,
    R16_SFLOAT = VkFormat::VK_FORMAT_R16_SFLOAT,
    R16G16_UNORM = VkFormat::VK_FORMAT_R16G16_UNORM,
    R16G16_SNORM = VkFormat::VK_FORMAT_R16G16_SNORM,
    R16G16_USCALED = VkFormat::VK_FORMAT_R16G16_USCALED,
    R16G16_SSCALED = VkFormat::VK_FORMAT_R16G16_SSCALED,
    R16G16_UINT = VkFormat::VK_FORMAT_R16G16_UINT,
    R16G16_SINT = VkFormat::VK_FORMAT_R16G16_SINT,
    R16G16_SFLOAT = VkFormat::VK_FORMAT_R16G16_SFLOAT,
    R16G16B16_UNORM = VkFormat::VK_FORMAT_R16G16B16_UNORM,
    R16G16B16_SNORM = VkFormat::VK_FORMAT_R16G16B16_SNORM,
    R16G16B16_USCALED = VkFormat::VK_FORMAT_R16G16B16_USCALED,
    R16G16B16_SSCALED = VkFormat::VK_FORMAT_R16G16B16_SSCALED,
    R16G16B16_UINT = VkFormat::VK_FORMAT_R16G16B16_UINT,
    R16G16B16_SINT = VkFormat::VK_FORMAT_R16G16B16_SINT,
    R16G16B16_SFLOAT = VkFormat::VK_FORMAT_R16G16B16_SFLOAT,
    R16G16B16A16_UNORM = VkFormat::VK_FORMAT_R16G16B16A16_UNORM,
    R16G16B16A16_SNORM = VkFormat::VK_FORMAT_R16G16B16A16_SNORM,
    R16G16B16A16_USCALED = VkFormat::VK_FORMAT_R16G16B16A16_USCALED,
    R16G16B16A16_SSCALED = VkFormat::VK_FORMAT_R16G16B16A16_SSCALED,
    R16G16B16A16_UINT = VkFormat::VK_FORMAT_R16G16B16A16_UINT,
    R16G16B16A16_SINT = VkFormat::VK_FORMAT_R16G16B16A16_SINT,
    R16G16B16A16_SFLOAT = VkFormat::VK_FORMAT_R16G16B16A16_SFLOAT,
    R32_UINT = VkFormat::VK_FORMAT_R32_UINT,
    R32_SINT = VkFormat::VK_FORMAT_R32_SINT,
    R32_SFLOAT = VkFormat::VK_FORMAT_R32_SFLOAT,
    R32G32_UINT = VkFormat::VK_FORMAT_R32G32_UINT,
    R32G32_SINT = VkFormat::VK_FORMAT_R32G32_SINT,
    R32G32_SFLOAT = VkFormat::VK_FORMAT_R32G32_SFLOAT,
    R32G32B32_UINT = VkFormat::VK_FORMAT_R32G32B32_UINT,
    R32G32B32_SINT = VkFormat::VK_FORMAT_R32G32B32_SINT,
    R32G32B32_SFLOAT = VkFormat::VK_FORMAT_R32G32B32_SFLOAT,
    R32G32B32A32_UINT = VkFormat::VK_FORMAT_R32G32B32A32_UINT,
    R32G32B32A32_SINT = VkFormat::VK_FORMAT_R32G32B32A32_SINT,
    R32G32B32A32_SFLOAT = VkFormat::VK_FORMAT_R32G32B32A32_SFLOAT,
    R64_UINT = VkFormat::VK_FORMAT_R64_UINT,
    R64_SINT = VkFormat::VK_FORMAT_R64_SINT,
    R64_SFLOAT = VkFormat::VK_FORMAT_R64_SFLOAT,
    R64G64_UINT = VkFormat::VK_FORMAT_R64G64_UINT,
    R64G64_SINT = VkFormat::VK_FORMAT_R64G64_SINT,
    R64G64_SFLOAT = VkFormat::VK_FORMAT_R64G64_SFLOAT,
    R64G64B64_UINT = VkFormat::VK_FORMAT_R64G64B64_UINT,
    R64G64B64_SINT = VkFormat::VK_FORMAT_R64G64B64_SINT,
    R64G64B64_SFLOAT = VkFormat::VK_FORMAT_R64G64B64_SFLOAT,
    R64G64B64A64_UINT = VkFormat::VK_FORMAT_R64G64B64A64_UINT,
    R64G64B64A64_SINT = VkFormat::VK_FORMAT_R64G64B64A64_SINT,
    R64G64B64A64_SFLOAT = VkFormat::VK_FORMAT_R64G64B64A64_SFLOAT,
    B10G11R11_UFLOAT_PACK32 = VkFormat::VK_FORMAT_B10G11R11_UFLOAT_PACK32,
    E5B9G9R9_UFLOAT_PACK32 = VkFormat::VK_FORMAT_E5B9G9R9_UFLOAT_PACK32,
    D16_UNORM = VkFormat::VK_FORMAT_D16_UNORM,
    X8_D24_UNORM_PACK32 = VkFormat::VK_FORMAT_X8_D24_UNORM_PACK32,
    D32_SFLOAT = VkFormat::VK_FORMAT_D32_SFLOAT,
    S8_UINT = VkFormat::VK_FORMAT_S8_UINT,
    D16_UNORM_S8_UINT = VkFormat::VK_FORMAT_D16_UNORM_S8_UINT,
    D24_UNORM_S8_UINT = VkFormat::VK_FORMAT_D24_UNORM_S8_UINT,
    D32_SFLOAT_S8_UINT = VkFormat::VK_FORMAT_D32_SFLOAT_S8_UINT,
    BC1_RGB_UNORM_BLOCK = VkFormat::VK_FORMAT_BC1_RGB_UNORM_BLOCK,
    BC1_RGB_SRGB_BLOCK = VkFormat::VK_FORMAT_BC1_RGB_SRGB_BLOCK,
    BC1_RGBA_UNORM_BLOCK = VkFormat::VK_FORMAT_BC1_RGBA_UNORM_BLOCK,
    BC1_RGBA_SRGB_BLOCK = VkFormat::VK_FORMAT_BC1_RGBA_SRGB_BLOCK,
    BC2_UNORM_BLOCK = VkFormat::VK_FORMAT_BC2_UNORM_BLOCK,
    BC2_SRGB_BLOCK = VkFormat::VK_FORMAT_BC2_SRGB_BLOCK,
    BC3_UNORM_BLOCK = VkFormat::VK_FORMAT_BC3_UNORM_BLOCK,
    BC3_SRGB_BLOCK = VkFormat::VK_FORMAT_BC3_SRGB_BLOCK,
    BC4_UNORM_BLOCK = VkFormat::VK_FORMAT_BC4_UNORM_BLOCK,
    BC4_SNORM_BLOCK = VkFormat::VK_FORMAT_BC4_SNORM_BLOCK,
    BC5_UNORM_BLOCK = VkFormat::VK_FORMAT_BC5_UNORM_BLOCK,
    BC5_SNORM_BLOCK = VkFormat::VK_FORMAT_BC5_SNORM_BLOCK,
    BC6H_UFLOAT_BLOCK = VkFormat::VK_FORMAT_BC6H_UFLOAT_BLOCK,
    BC6H_SFLOAT_BLOCK = VkFormat::VK_FORMAT_BC6H_SFLOAT_BLOCK,
    BC7_UNORM_BLOCK = VkFormat::VK_FORMAT_BC7_UNORM_BLOCK,
    BC7_SRGB_BLOCK = VkFormat::VK_FORMAT_BC7_SRGB_BLOCK,
    ETC2_R8G8B8_UNORM_BLOCK = VkFormat::VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK,
    ETC2_R8G8B8_SRGB_BLOCK = VkFormat::VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK,
    ETC2_R8G8B8A1_UNORM_BLOCK = VkFormat::VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK,
    ETC2_R8G8B8A1_SRGB_BLOCK = VkFormat::VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK,
    ETC2_R8G8B8A8_UNORM_BLOCK = VkFormat::VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK,
    ETC2_R8G8B8A8_SRGB_BLOCK = VkFormat::VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK,
    EAC_R11_UNORM_BLOCK = VkFormat::VK_FORMAT_EAC_R11_UNORM_BLOCK,
    EAC_R11_SNORM_BLOCK = VkFormat::VK_FORMAT_EAC_R11_SNORM_BLOCK,
    EAC_R11G11_UNORM_BLOCK = VkFormat::VK_FORMAT_EAC_R11G11_UNORM_BLOCK,
    EAC_R11G11_SNORM_BLOCK = VkFormat::VK_FORMAT_EAC_R11G11_SNORM_BLOCK,
    ASTC_4x4_UNORM_BLOCK = VkFormat::VK_FORMAT_ASTC_4x4_UNORM_BLOCK,
    ASTC_4x4_SRGB_BLOCK = VkFormat::VK_FORMAT_ASTC_4x4_SRGB_BLOCK,
    ASTC_5x4_UNORM_BLOCK = VkFormat::VK_FORMAT_ASTC_5x4_UNORM_BLOCK,
    ASTC_5x4_SRGB_BLOCK = VkFormat::VK_FORMAT_ASTC_5x4_SRGB_BLOCK,
    ASTC_5x5_UNORM_BLOCK = VkFormat::VK_FORMAT_ASTC_5x5_UNORM_BLOCK,
    ASTC_5x5_SRGB_BLOCK = VkFormat::VK_FORMAT_ASTC_5x5_SRGB_BLOCK,
    ASTC_6x5_UNORM_BLOCK = VkFormat::VK_FORMAT_ASTC_6x5_UNORM_BLOCK,
    ASTC_6x5_SRGB_BLOCK = VkFormat::VK_FORMAT_ASTC_6x5_SRGB_BLOCK,
    ASTC_6x6_UNORM_BLOCK = VkFormat::VK_FORMAT_ASTC_6x6_UNORM_BLOCK,
    ASTC_6x6_SRGB_BLOCK = VkFormat::VK_FORMAT_ASTC_6x6_SRGB_BLOCK,
    ASTC_8x5_UNORM_BLOCK = VkFormat::VK_FORMAT_ASTC_8x5_UNORM_BLOCK,
    ASTC_8x5_SRGB_BLOCK = VkFormat::VK_FORMAT_ASTC_8x5_SRGB_BLOCK,
    ASTC_8x6_UNORM_BLOCK = VkFormat::VK_FORMAT_ASTC_8x6_UNORM_BLOCK,
    ASTC_8x6_SRGB_BLOCK = VkFormat::VK_FORMAT_ASTC_8x6_SRGB_BLOCK,
    ASTC_8x8_UNORM_BLOCK = VkFormat::VK_FORMAT_ASTC_8x8_UNORM_BLOCK,
    ASTC_8x8_SRGB_BLOCK = VkFormat::VK_FORMAT_ASTC_8x8_SRGB_BLOCK,
    ASTC_10x5_UNORM_BLOCK = VkFormat::VK_FORMAT_ASTC_10x5_UNORM_BLOCK,
    ASTC_10x5_SRGB_BLOCK = VkFormat::VK_FORMAT_ASTC_10x5_SRGB_BLOCK,
    ASTC_10x6_UNORM_BLOCK = VkFormat::VK_FORMAT_ASTC_10x6_UNORM_BLOCK,
    ASTC_10x6_SRGB_BLOCK = VkFormat::VK_FORMAT_ASTC_10x6_SRGB_BLOCK,
    ASTC_10x8_UNORM_BLOCK = VkFormat::VK_FORMAT_ASTC_10x8_UNORM_BLOCK,
    ASTC_10x8_SRGB_BLOCK = VkFormat::VK_FORMAT_ASTC_10x8_SRGB_BLOCK,
    ASTC_10x10_UNORM_BLOCK = VkFormat::VK_FORMAT_ASTC_10x10_UNORM_BLOCK,
    ASTC_10x10_SRGB_BLOCK = VkFormat::VK_FORMAT_ASTC_10x10_SRGB_BLOCK,
    ASTC_12x10_UNORM_BLOCK = VkFormat::VK_FORMAT_ASTC_12x10_UNORM_BLOCK,
    ASTC_12x10_SRGB_BLOCK = VkFormat::VK_FORMAT_ASTC_12x10_SRGB_BLOCK,
    ASTC_12x12_UNORM_BLOCK = VkFormat::VK_FORMAT_ASTC_12x12_UNORM_BLOCK,
    ASTC_12x12_SRGB_BLOCK = VkFormat::VK_FORMAT_ASTC_12x12_SRGB_BLOCK,
    // Provided by VK_VERSION_1_1
    G8B8G8R8_422_UNORM = VkFormat::VK_FORMAT_G8B8G8R8_422_UNORM,
    // Provided by VK_VERSION_1_1
    B8G8R8G8_422_UNORM = VkFormat::VK_FORMAT_B8G8R8G8_422_UNORM,
    // Provided by VK_VERSION_1_1
    G8_B8_R8_3PLANE_420_UNORM = VkFormat::VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM,
    // Provided by VK_VERSION_1_1
    G8_B8R8_2PLANE_420_UNORM = VkFormat::VK_FORMAT_G8_B8R8_2PLANE_420_UNORM,
    // Provided by VK_VERSION_1_1
    G8_B8_R8_3PLANE_422_UNORM = VkFormat::VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM,
    // Provided by VK_VERSION_1_1
    G8_B8R8_2PLANE_422_UNORM = VkFormat::VK_FORMAT_G8_B8R8_2PLANE_422_UNORM,
    // Provided by VK_VERSION_1_1
    G8_B8_R8_3PLANE_444_UNORM = VkFormat::VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM,
    // Provided by VK_VERSION_1_1
    R10X6_UNORM_PACK16 = VkFormat::VK_FORMAT_R10X6_UNORM_PACK16,
    // Provided by VK_VERSION_1_1
    R10X6G10X6_UNORM_2PACK16 = VkFormat::VK_FORMAT_R10X6G10X6_UNORM_2PACK16,
    // Provided by VK_VERSION_1_1
    R10X6G10X6B10X6A10X6_UNORM_4PACK16 = VkFormat::VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16,
    // Provided by VK_VERSION_1_1
    G10X6B10X6G10X6R10X6_422_UNORM_4PACK16 = VkFormat::VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16,
    // Provided by VK_VERSION_1_1
    B10X6G10X6R10X6G10X6_422_UNORM_4PACK16 = VkFormat::VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16,
    // Provided by VK_VERSION_1_1
    G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16 = VkFormat::VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16,
    // Provided by VK_VERSION_1_1
    G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16 = VkFormat::VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16,
    // Provided by VK_VERSION_1_1
    G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16 = VkFormat::VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16,
    // Provided by VK_VERSION_1_1
    G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16 = VkFormat::VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16,
    // Provided by VK_VERSION_1_1
    G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16 = VkFormat::VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16,
    // Provided by VK_VERSION_1_1
    R12X4_UNORM_PACK16 = VkFormat::VK_FORMAT_R12X4_UNORM_PACK16,
    // Provided by VK_VERSION_1_1
    R12X4G12X4_UNORM_2PACK16 = VkFormat::VK_FORMAT_R12X4G12X4_UNORM_2PACK16,
    // Provided by VK_VERSION_1_1
    R12X4G12X4B12X4A12X4_UNORM_4PACK16 = VkFormat::VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16,
    // Provided by VK_VERSION_1_1
    G12X4B12X4G12X4R12X4_422_UNORM_4PACK16 = VkFormat::VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16,
    // Provided by VK_VERSION_1_1
    B12X4G12X4R12X4G12X4_422_UNORM_4PACK16 = VkFormat::VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16,
    // Provided by VK_VERSION_1_1
    G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16 = VkFormat::VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16,
    // Provided by VK_VERSION_1_1
    G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16 = VkFormat::VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16,
    // Provided by VK_VERSION_1_1
    G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16 = VkFormat::VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16,
    // Provided by VK_VERSION_1_1
    G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16 = VkFormat::VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16,
    // Provided by VK_VERSION_1_1
    G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16 = VkFormat::VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16,
    // Provided by VK_VERSION_1_1
    G16B16G16R16_422_UNORM = VkFormat::VK_FORMAT_G16B16G16R16_422_UNORM,
    // Provided by VK_VERSION_1_1
    B16G16R16G16_422_UNORM = VkFormat::VK_FORMAT_B16G16R16G16_422_UNORM,
    // Provided by VK_VERSION_1_1
    G16_B16_R16_3PLANE_420_UNORM = VkFormat::VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM,
    // Provided by VK_VERSION_1_1
    G16_B16R16_2PLANE_420_UNORM = VkFormat::VK_FORMAT_G16_B16R16_2PLANE_420_UNORM,
    // Provided by VK_VERSION_1_1
    G16_B16_R16_3PLANE_422_UNORM = VkFormat::VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM,
    // Provided by VK_VERSION_1_1
    G16_B16R16_2PLANE_422_UNORM = VkFormat::VK_FORMAT_G16_B16R16_2PLANE_422_UNORM,
    // Provided by VK_VERSION_1_1
    G16_B16_R16_3PLANE_444_UNORM = VkFormat::VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM
} TFormatTypeEnum;

typedef enum TFormatContentType
{
    UNDEFINED = 0x000,
    RED = 0x001,
    GREEN = 0x002,
    BLUE = 0x004,
    ALPHA = 0x008,
    DEPTH = 0x010,
    STENCIL = 0x020,
    EXPONENT = 0x040, //???
    UNUSED = 0x080,   ///???
} TFormatContentTypeEnum;

typedef enum TFormatDataTypeBits
{
    UNSIGNED_NORMALIZED = 0x00000001, // UNORM 	: float : unsigned normalized values in the range [0,1]
    SIGNED_NORMALIZED = 0x00000002,   // SNORM 	: float : signed normalized values in the range [-1,1]
    UNSIGNED_SCALED = 0x00000004,     // USCALED : float : unsigned integer values that get converted to floating-point in the range [0,(2^n)-1]
    SIGNED_SCALED = 0x00000008,       // SSCALED ：float : signed integer values that get converted to floating-point in the range [(-2^(n-1)),(2^(n-1))-1]
    UNSIGNED_INTEGER = 0x00000010,    // UINT 	  : uint 	: unsigned integer values in the range [0,(2^n)-1]
    SIGNED_INTEGER = 0x00000020,      // SINT 	  : int 	: signed integer values in the range [-2^(n-1),(2^(n-1))-1]
    SRGB = 0x00000040,                // SRGB	  : float : The R, G, and B components are unsigned normalized values that represent values using sRGB nonlinear encoding, while the A component (if one exists) is a regular unsigned normalized value
    SIGNED_FLOAT = 0x00000080,        // SFLOAT	: float : signed floating-point numbers
    UNSIGNED_FLOAT = 0x00000100       // UFLOAT	: float : unsigned floating-point numbers (used by packed, shared exponent, and some compressed formats)
} TFormatDataTypeBitsEnum;
typedef VkFlags TFormatDataTypes;

typedef enum class TFormatCompression
{
    NONE = 0,
    BC,   // Block Compression
    ETC2, // Ericsson Texture Compression
    EAC,  // ETC2 Alpha Compression
    ASTC  // Adaptive Scalable Texture Compression (LDR Profile).
} TFormatCompression;

typedef enum class TFormatReduceFactor
{
    NONE = 0,
    FACTOR_422, // planes other than the first are reduced in size by a factor of two horizontally or that the R and B values appear at half the horizontal frequency of the G values
    FACTOR_420, // planes other than the first are reduced in size by a factor of two both horizontally and vertically
    FACTOR_444, // all three planes of a three-planar image are the same size.
} TFormatReduceFactor;

typedef enum TFormatFeatureBits
{
    FEATURE_SAMPLED_IMAGE_BIT = 0x00000001,
    FEATURE_STORAGE_IMAGE_BIT = 0x00000002,
    FEATURE_STORAGE_IMAGE_ATOMIC_BIT = 0x00000004,
    FEATURE_UNIFORM_TEXEL_BUFFER_BIT = 0x00000008,
    FEATURE_STORAGE_TEXEL_BUFFER_BIT = 0x00000010,
    FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT = 0x00000020,
    FEATURE_VERTEX_BUFFER_BIT = 0x00000040,
    FEATURE_COLOR_ATTACHMENT_BIT = 0x00000080,
    FEATURE_COLOR_ATTACHMENT_BLEND_BIT = 0x00000100,
    FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT = 0x00000200,
    FEATURE_BLIT_SRC_BIT = 0x00000400,
    FEATURE_BLIT_DST_BIT = 0x00000800,
    FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT = 0x00001000,
} TFormatFeatureBits;
typedef VkFlags TFormatFeatures;

class TPhysicalDevice;

class TFormatInfo : public TObject
{
  private:
    TFormatType formatType = TFormatType::UNDEFINED;
    TFormatProperties formatProperties = {};

  public:
    static std::vector<TFormatInfo> GetSupportFormats(TPhysicalDevice *physicalDevice);
    static bool IsSupportFormat(TPhysicalDevice *physicalDevice, TFormatType formatType);

  public:
    TFormatInfo();
    //[[deprecated]] TFormatInfo(TFormatType formatType = TFormatType::UNDEFINED);
    explicit TFormatInfo(TFormatType formatType, TFormatProperties formatProperties);
    ~TFormatInfo();

  public:
    TFormatType GetFormatType();
    VkFormat GetVkFormat();

    TFormatDataTypes GetFormatDataType();

    // bool IsPacked();
    // uint32_t GetPackGroup();
    // uint32_t GetPackBits();

    // bool IsCompressed();
    // TFormatCompression GetFormatCompression

    // bool IsMultiPlanar();
    // uint32_t GetPlaneNumber();
    // TFormatReduceFactor GetReduceFactor();

    uint32_t GetTexelBlockSize(); // unit byte

    // uint8_t GetRedBitSize();//unit bit
    // uint8_t GetGreenBitSize();//unit bit
    // uint8_t GetBlueBitSize();//unit bit
    // uint8_t GetAlphaBitSize();//unit bit
    // uint8_t GetDepthBitSize();//unit bit
    // uint8_t GetStencilBitSize();//unit bit

    bool IsSupportBuffer();
    bool IsSupportVertexBuffer();

    bool IsSupportLinearTiling();
    bool IsLinearTilingSupportSampledImage();
    bool IsLinearTilingSupportStorageImage();
    bool IsLinearTilingSupportStorageImageAtomic();
    bool IsLinearTilingSupportColorAttachment();
    bool IsLinearTilingSupportColorAttachmentBlend();
    bool IsLinearTilingSupportDepthStencilAttachment();
    bool IsLinearTilingSupportBlitSrc();
    bool IsLinearTilingSupportBlitDst();
    bool IsLinearTilingSupportSampledImageFilterLinear();
    bool IsLinearTilingSupportTransferSrc();
    bool IsLinearTilingSupportTransferDst();

    bool IsSupportOptimalTiling();
    bool IsOptimalTilingSupportSampledImage();
    bool IsOptimalTilingSupportStorageImage();
    bool IsOptimalTilingSupportStorageImageAtomic();
    bool IsOptimalTilingSupportColorAttachment();
    bool IsOptimalTilingSupportColorAttachmentBlend();
    bool IsOptimalTilingSupportDepthStencilAttachment();
    bool IsOptimalTilingSupportBlitSrc();
    bool IsOptimalTilingSupportBlitDst();
    bool IsOptimalTilingSupportSampledImageFilterLinear();
    bool IsOptimalTilingSupportTransferSrc();
    bool IsOptimalTilingSupportTransferDst();

    bool operator==(const TFormatInfo &format) const; // TODO: Format Compatibility Classes
    bool operator!=(const TFormatInfo &format) const;
    virtual std::string ToString() override;
};
} // namespace Core
} // namespace Turbo
#endif // !TURBO_CORE_TFORMAT_H