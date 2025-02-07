project(TCore)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)

aux_source_directory(./src/ SRCS)

add_subdirectory(./thirdparty)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/VulkanMemoryAllocator/src/VmaUsage.cpp")
set(VMA_SRCS 
./thirdparty/VulkanMemoryAllocator/src/VmaUsage.cpp
./thirdparty/VulkanMemoryAllocator/include/vk_mem_alloc.h
)
else()
message(FATAL_ERROR "Can not find VulkanMemoryAllocator")
endif()

message(STATUS "${VMA_SRCS}")

option(TCORE_SHARED_LIBS "flag to create TCore shared libraries if on" OFF)

if(TCORE_SHARED_LIBS)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    add_library(${PROJECT_NAME} SHARED
        ${VMA_SRCS}
        #$<TARGET_OBJECTS:VulkanMemoryAllocator>
        $<TARGET_OBJECTS:MachineIndependent>
        $<TARGET_OBJECTS:glslang>
        $<TARGET_OBJECTS:glslang-default-resource-limits>
        $<TARGET_OBJECTS:OGLCompiler>
        $<TARGET_OBJECTS:OSDependent>
        $<TARGET_OBJECTS:GenericCodeGen>
        $<TARGET_OBJECTS:SPIRV>
        $<TARGET_OBJECTS:spirv-cross-core>
        $<TARGET_OBJECTS:spirv-cross-glsl>
        $<TARGET_OBJECTS:spirv-cross-hlsl>
        ${SRCS}
    )
    target_compile_definitions(${PROJECT_NAME} PUBLIC TCORE_SHARED_LIBS)
else() 
    add_library(${PROJECT_NAME} STATIC
        ${VMA_SRCS}
        #$<TARGET_OBJECTS:VulkanMemoryAllocator>
        $<TARGET_OBJECTS:MachineIndependent>
        $<TARGET_OBJECTS:glslang>
        $<TARGET_OBJECTS:glslang-default-resource-limits>
        $<TARGET_OBJECTS:OGLCompiler>
        $<TARGET_OBJECTS:OSDependent>
        $<TARGET_OBJECTS:GenericCodeGen>
        $<TARGET_OBJECTS:SPIRV>
        $<TARGET_OBJECTS:spirv-cross-core>
        $<TARGET_OBJECTS:spirv-cross-glsl>
        $<TARGET_OBJECTS:spirv-cross-hlsl>
        ${SRCS}
    )
endif()

target_compile_definitions(${PROJECT_NAME} PUBLIC
    VMA_STATIC_VULKAN_FUNCTIONS=$<BOOL:${VMA_STATIC_VULKAN_FUNCTIONS}>
    VMA_DYNAMIC_VULKAN_FUNCTIONS=$<BOOL:${VMA_DYNAMIC_VULKAN_FUNCTIONS}>
    VMA_DEBUG_ALWAYS_DEDICATED_MEMORY=$<BOOL:${VMA_DEBUG_ALWAYS_DEDICATED_MEMORY}>
    VMA_DEBUG_INITIALIZE_ALLOCATIONS=$<BOOL:${VMA_DEBUG_INITIALIZE_ALLOCATIONS}>
    VMA_DEBUG_GLOBAL_MUTEX=$<BOOL:${VMA_DEBUG_GLOBAL_MUTEX}>
    VMA_DEBUG_DONT_EXCEED_MAX_MEMORY_ALLOCATION_COUNT=$<BOOL:${VMA_DEBUG_DONT_EXCEED_MAX_MEMORY_ALLOCATION_COUNT}>
)

target_include_directories(${PROJECT_NAME}
PUBLIC ./include
PRIVATE ./thirdparty/VulkanMemoryAllocator/include
PRIVATE ./thirdparty/SPIRV-Cross
PRIVATE ./thirdparty/glslang
)