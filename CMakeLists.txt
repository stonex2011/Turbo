cmake_minimum_required(VERSION 3.0)

project(Turbo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wunused-function")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Werror -Wno-switch -Wno-missing-field-initializers -Wno-unused-variable -Wno-unused-parameter -Wno-unused-function")

set(CMAKE_BUILD_TYPE "debug")

add_subdirectory(./engine)
add_subdirectory(./thirdparty)
add_subdirectory(./samples)

set(IMGUI_SOURCE_PATH 
./thirdparty/imgui/imgui_demo.cpp
./thirdparty/imgui/imgui_draw.cpp
./thirdparty/imgui/imgui_tables.cpp
./thirdparty/imgui/imgui_widgets.cpp
./thirdparty/imgui/imgui.cpp
)

add_executable(${PROJECT_NAME} ./main.cpp ${IMGUI_SOURCE_PATH})

add_dependencies(${PROJECT_NAME} glfw)
add_dependencies(${PROJECT_NAME} TCore)

target_include_directories(${PROJECT_NAME}
    PUBLIC ./engine/core/include
    PUBLIC ./engine/include/
    PUBLIC ./thirdparty/glm/
    PUBLIC ./thirdparty/tinygltf/
    PUBLIC ./thirdparty/imgui/
    PUBLIC ./thirdparty/imgui/backends/
    PUBLIC ./thirdparty/KTX-Software/include/
    )

target_link_directories(${PROJECT_NAME} 
PUBLIC /engine/core/
PUBLIC /thirdparty/glfw/src/
PUBLIC /thirdparty/KTX-Software/
)

target_link_libraries(${PROJECT_NAME} PUBLIC 
TCore
glfw
ktx
)
