#include "render/include/TBuffer.h"
#include "render/include/TDomain.h"
#include "render/include/TImage.h"
#include "render/include/TShader.h"
#include <chrono>
#include <framegraph/include/TFrameGraph.hpp>
#include <fstream>
#include <iostream>
#include <render/include/TContext.h>
#include <render/include/TPipeline.h>
#include <render/include/TRenderPass.h>
#include <render/include/TResourceAllocator.h>
#include <render/include/TSampler.h>
#include <sstream>
#include <stdint.h>
#include <vector>

#include <core/include/TCommandBuffer.h>
#include <core/include/TDevice.h>
#include <core/include/TDeviceQueue.h>
#include <core/include/TFence.h>
#include <core/include/TImage.h>
#include <core/include/TImageView.h>
#include <core/include/TInstance.h>
#include <core/include/TPipeline.h>
#include <core/include/TSurface.h>
#include <core/include/TSwapchain.h>
#include <core/include/TVulkanLoader.h>
#include <vulkan/vulkan.h>

#include <GLFW/glfw3.h>

std::string ReadTextFile(const std::string &filename)
{
    std::vector<std::string> data;

    std::ifstream file;

    file.open(filename, std::ios::in);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    return std::string{(std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>())};
}

int main()
{
    /*
       [Draw Pass(进行一个简单的三角形绘制)] → Color Texture → [Present Pass]
       1. 在DrawPass创建一个Texture并使用DrawCall进行绘制
       2. 在PresentPass中将之前绘制的Texture结果拷贝至要显示的纹理中
       3. 显示
       4. 重复1-3
    */
    Turbo::Render::TContext context;
    Turbo::Render::TResourceAllocator resource_allocator(&context);

    if (!glfwInit())
        return 0;

    int window_width = 512;
    int window_height = 512;
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow *window = glfwCreateWindow(window_width, window_height, "Turbo", NULL, NULL);
    VkSurfaceKHR vk_surface_khr = VK_NULL_HANDLE;
    VkInstance vk_instance = context.GetInstance()->GetVkInstance();
    VkResult surface_result = glfwCreateWindowSurface(vk_instance, window, NULL, &vk_surface_khr);

    if (vk_surface_khr == VK_NULL_HANDLE)
    {
        std::cout << "vk_surface_khr is VK_NULL_HANDLE::" << surface_result << std::endl;
        return 0;
    }

    Turbo::Extension::TSurface *surface = new Turbo::Extension::TSurface(context.GetDevice(), vk_surface_khr);

    uint32_t max_image_count = surface->GetMaxImageCount();
    uint32_t min_image_count = surface->GetMinImageCount();
    uint32_t swapchain_image_count = max_image_count <= min_image_count ? min_image_count : max_image_count - 1;

    Turbo::Extension::TSwapchain *swapchain = new Turbo::Extension::TSwapchain(surface, swapchain_image_count, Turbo::Core::TFormatType::B8G8R8A8_SRGB, 1, Turbo::Core::TImageUsageBits::IMAGE_COLOR_ATTACHMENT | Turbo::Core::TImageUsageBits::IMAGE_TRANSFER_SRC | Turbo::Core::TImageUsageBits::IMAGE_TRANSFER_DST, true);
    std::vector<Turbo::Core::TImage *> swapchain_images = swapchain->GetImages();

    std::vector<Turbo::Core::TImageView *> swapchain_image_views;
    for (Turbo::Core::TImage *swapchain_image_item : swapchain_images)
    {
        Turbo::Core::TImageView *swapchain_view = new Turbo::Core::TImageView(swapchain_image_item, Turbo::Core::TImageViewType::IMAGE_VIEW_2D, Turbo::Core::TFormatType::B8G8R8A8_SRGB, Turbo::Core::TImageAspectBits::ASPECT_COLOR_BIT, 0, 1, 0, 1);
        swapchain_image_views.push_back(swapchain_view);
    }

    int current_width = window_width;
    int current_height = window_height;

    struct vec3
    {
        float x;
        float y;
        float z;
    };

    struct col3
    {
        float r;
        float g;
        float b;
    };

    struct VertexData
    {
        vec3 position;
        col3 color;
    };

    std::vector<VertexData> vertex_data;
    vertex_data.push_back({{0.0f, -0.5f, 0.0f}, {1, 0, 0}});
    vertex_data.push_back({{0.5f, 0.5f, 0.0f}, {0, 1, 0}});
    vertex_data.push_back({{-0.5f, 0.5f, 0.0f}, {0, 0, 1}});

    Turbo::Render::TVertexBuffer vertex_buffer;
    Turbo::Render::TVertexBuffer::Descriptor vertex_buffer_descriptor = {};
    vertex_buffer_descriptor.size = sizeof(VertexData) * vertex_data.size();
    vertex_buffer_descriptor.domain = Turbo::Render::TDomainBits::GPU;
    vertex_buffer_descriptor.rate = Turbo::Render::TVertexBuffer::TRate::VERTEX;
    vertex_buffer_descriptor.stride = sizeof(VertexData);

    vertex_buffer.Create("VertexBuffer", vertex_buffer_descriptor, &resource_allocator);
    Turbo::Render::TAttributeID position_attribute_id = vertex_buffer.AddAttribute(Turbo::Render::TFormat::R32G32B32_SFLOAT, offsetof(VertexData, position));
    Turbo::Render::TAttributeID color_attribute_id = vertex_buffer.AddAttribute(Turbo::Render::TFormat::R32G32B32_SFLOAT, offsetof(VertexData, color));
    vertex_buffer.Copy(vertex_data.data(), sizeof(VertexData) * vertex_data.size());

    Turbo::Render::TVertexShader *vertex_shader = new Turbo::Render::TVertexShader(&context, Turbo::Render::TShader::TLanguage::GLSL, ReadTextFile("../../asset/shaders/pure_triangle.vert"));
    Turbo::Render::TFragmentShader *fragment_shader = new Turbo::Render::TFragmentShader(&context, Turbo::Render::TShader::TLanguage::GLSL, ReadTextFile("../../asset/shaders/pure_triangle.frag"));

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        Turbo::FrameGraph::TFrameGraph fg;

        struct DrawPassData
        {
            Turbo::FrameGraph::TResource colorTexture;
        };

        fg.AddPass<DrawPassData>(
            "DrawPass",
            [&](Turbo::FrameGraph::TFrameGraph::TBuilder &builder, DrawPassData &data) {
                data.colorTexture = builder.Create<Turbo::Render::TTexture2D>("ColorTexture", {(uint32_t)current_width, (uint32_t)current_height, 1, Turbo::Render::TImageUsageBits::COLOR_ATTACHMENT | Turbo::Render::TImageUsageBits::TRANSFER_SRC | Turbo::Render::TImageUsageBits::TRANSFER_DST, Turbo::Render::TDomainBits::GPU});

                auto subpass0 = builder.CreateSubpass();
                data.colorTexture = subpass0.Write(data.colorTexture);

                fg.GetBlackboard()["ColorTexture"] = data.colorTexture;
            },
            [&](const DrawPassData &data, const Turbo::FrameGraph::TResources &resources, void *_context) {
                // TODO:Clear Color Texture

                Turbo::Render::TTexture2D color_texture = resources.Get<Turbo::Render::TTexture2D>(data.colorTexture);

                resources.GetRenderPass().GetSubpass(0).GetWrite(0).IsValid();

                Turbo::Render::TSubpass subpass;
                subpass.AddColorAttachment(color_texture);

                Turbo::Render::TRenderPass triangle_render_pass;
                triangle_render_pass.AddSubpass(subpass);

                Turbo::Render::TGraphicsPipeline graphics_pipeline;
                graphics_pipeline.SetVertexShader(vertex_shader);
                graphics_pipeline.SetFragmentShader(fragment_shader);

                context.BeginRenderPass(triangle_render_pass);
                context.BindVeretxAttribute(vertex_buffer, position_attribute_id, 0);
                context.BindVeretxAttribute(vertex_buffer, color_attribute_id, 1);
                context.BindPipeline(graphics_pipeline);
                context.Draw(3, 1, 0, 0);
                context.EndRenderPass();

                context.Flush();
                context.Wait(UINT64_MAX);
            });

        struct PresentPassData
        {
            Turbo::FrameGraph::TResource colorTexture;
        };

        fg.AddPass<PresentPassData>(
            "PresentPass",
            [&](Turbo::FrameGraph::TFrameGraph::TBuilder &builder, PresentPassData &data) {
                data.colorTexture = fg.GetBlackboard()["ColorTexture"];

                auto subpass0 = builder.CreateSubpass();
                data.colorTexture = subpass0.Read(data.colorTexture);

                builder.SideEffect();
            },
            [&](const PresentPassData &data, const Turbo::FrameGraph::TResources &resources, void *_context) {
                // TODO:Present Color Texture

                Turbo::Render::TTexture2D color_texture = resources.Get<Turbo::Render::TTexture2D>(data.colorTexture);

                if (_context != nullptr)
                {
                    Turbo::Render::TContext *temp_context = (Turbo::Render::TContext *)_context;

                    temp_context->Flush();
                    temp_context->Wait(UINT64_MAX);
                    // TODO: present
                    uint32_t index = UINT32_MAX;
                    Turbo::Core::TFence *acquire_next_image_fence = new Turbo::Core::TFence(temp_context->GetDevice());
                    Turbo::Core::TResult result = swapchain->AcquireNextImageUntil(nullptr, acquire_next_image_fence, &index);
                    acquire_next_image_fence->WaitUntil();
                    delete acquire_next_image_fence;
                    if (result == Turbo::Core::TResult::SUCCESS)
                    {
                        // TODO:Blit Image

                        auto show_target = swapchain_image_views[index];

                        Turbo::Core::TFence *fence = new Turbo::Core::TFence(temp_context->GetDevice());
                        Turbo::Core::TCommandBuffer *cb = temp_context->AllocateCommandBuffer();
                        cb->Begin();
                        cb->CmdTransformImageLayout(Turbo::Core::TPipelineStageBits::TOP_OF_PIPE_BIT, Turbo::Core::TPipelineStageBits::TOP_OF_PIPE_BIT, Turbo::Core::TAccessBits::ACCESS_NONE, Turbo::Core::TAccessBits::ACCESS_NONE, Turbo::Core::TImageLayout::UNDEFINED, Turbo::Core::TImageLayout::GENERAL, show_target);
                        // cb->CmdClearColorImage(show_target, Turbo::Core::TImageLayout::GENERAL, 1, 0, 0, 1);
                        cb->CmdBlitImage(temp_context->GetTextureImage(color_texture), Turbo::Core::TImageLayout::GENERAL, show_target->GetImage(), Turbo::Core::TImageLayout::GENERAL, 0, 0, 0, current_width, current_height, 1, Turbo::Core::TImageAspectBits::ASPECT_COLOR_BIT, 0, 0, 1, 0, 0, 0, current_width, current_height, 1, Turbo::Core::TImageAspectBits::ASPECT_COLOR_BIT, 0, 0, 1);
                        cb->CmdTransformImageLayout(Turbo::Core::TPipelineStageBits::TOP_OF_PIPE_BIT, Turbo::Core::TPipelineStageBits::TOP_OF_PIPE_BIT, Turbo::Core::TAccessBits::ACCESS_NONE, Turbo::Core::TAccessBits::ACCESS_NONE, Turbo::Core::TImageLayout::GENERAL, Turbo::Core::TImageLayout::PRESENT_SRC_KHR, show_target);
                        cb->End();
                        temp_context->GetDeviceQueue()->Submit(nullptr, nullptr, cb, fence);

                        fence->WaitUntil();

                        delete fence;
                        temp_context->FreeCommandBuffer(cb);
                        Turbo::Core::TResult result = temp_context->GetDeviceQueue()->Present(swapchain, index);
                        switch (result)
                        {
                        case Turbo::Core::TResult::MISMATCH: {
                            Turbo::Core::TDevice *device = temp_context->GetDevice();
                            device->WaitIdle();

                            swapchain_images.clear();

                            for (Turbo::Core::TImageView *swapchain_image_view_item : swapchain_image_views)
                            {
                                delete swapchain_image_view_item;
                            }

                            swapchain_image_views.clear();

                            Turbo::Extension::TSwapchain *old_swapchain = swapchain;
                            Turbo::Extension::TSwapchain *new_swapchain = new Turbo::Extension::TSwapchain(old_swapchain);
                            delete old_swapchain;

                            swapchain = new_swapchain;

                            swapchain_images = swapchain->GetImages();
                            for (Turbo::Core::TImage *swapchain_image_item : swapchain_images)
                            {
                                Turbo::Core::TImageView *swapchain_view = new Turbo::Core::TImageView(swapchain_image_item, Turbo::Core::TImageViewType::IMAGE_VIEW_2D, Turbo::Core::TFormatType::B8G8R8A8_SRGB, Turbo::Core::TImageAspectBits::ASPECT_COLOR_BIT, 0, 1, 0, 1);
                                swapchain_image_views.push_back(swapchain_view);
                            }

                            glfwGetWindowSize(window, &current_width, &current_height);
                        }
                        break;
                        default: {
                        }
                        break;
                        }
                    }
                }
            });

        fg.Compile();
        fg.Execute(&context, &resource_allocator);
        context.GC();
    }

    context.GetDevice()->WaitIdle();

    delete fragment_shader;
    delete vertex_shader;

    vertex_buffer.Destroy(&resource_allocator);

    for (Turbo::Core::TImageView *swapchain_image_view_item : swapchain_image_views)
    {
        delete swapchain_image_view_item;
    }

    delete swapchain;
    delete surface;
    PFN_vkDestroySurfaceKHR pfn_vk_destroy_surface_khr = Turbo::Core::TVulkanLoader::Instance()->LoadInstanceFunction<PFN_vkDestroySurfaceKHR>(context.GetInstance()->GetVkInstance(), "vkDestroySurfaceKHR");
    pfn_vk_destroy_surface_khr(context.GetInstance()->GetVkInstance(), vk_surface_khr, nullptr);
    glfwTerminate();

    return 0;
}