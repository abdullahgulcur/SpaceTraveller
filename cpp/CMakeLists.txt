# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.20)

project("space")

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(win 0)
set(android 1)
set(platform ${win})

set(sourceFiles

        "main.cpp"

        "Game/Game.cpp"
        "Game/Universe.cpp"
        "Game/OrbitCameraController.cpp"
        "Game/TranslateCameraController.cpp"
        "Game/CameraController.cpp"

        "Game/Scene/UniverseScene.cpp"
        "Game/Scene/TerrainSceneTest.cpp"
        "Game/Scene/PlanetSceneTest.cpp"

        "Engine/Core/Core.cpp"
        "Engine/Core/Timer.cpp"
        "Engine/Core/pch.cpp"

        "Engine/Modules/Terrain/TerrainGeometryManager.cpp"

        "Engine/Platform/Input.cpp"
        "Engine/Platform/AppSurface.cpp"

        "Engine/Math/RandomValue.cpp"

        "Engine/Rendering/Camera.cpp"
        "Engine/Rendering/IndexBuffer.cpp"
        "Engine/Rendering/SceneRenderer.cpp"
        "Engine/Rendering/ShaderProgram.cpp"
        "Engine/Rendering/StaticMesh.cpp"
        "Engine/Rendering/Texture2D.cpp"
        "Engine/Rendering/Vao.cpp"
        "Engine/Rendering/VertexBuffer.cpp"
        "Engine/Rendering/ParticleSystem.cpp"
        "Engine/Rendering/Particle.cpp"
        "Engine/Rendering/DrawCommand.cpp"
        "Engine/Rendering/FrameBuffer.cpp"
        "Engine/Rendering/Renderer.cpp"
        "Engine/Rendering/Gizmo.cpp"
        "Engine/Rendering/Entity.cpp"

        "Engine/Resource/MeshData.cpp"

        "ThirdParty/tinyobjloader/tiny_obj_loader.cpp"
        "ThirdParty/stb/stb_image.cpp"
)

if(${platform} STREQUAL ${android})

    list(APPEND sourceFiles
            "Engine/Platform/Android/AndroidApplication.cpp"
            "Engine/Platform/Android/EglContext.cpp"
            "Engine/Platform/Android/AndroidAssetManager.cpp"
            "Engine/Platform/Android/AndroidInput.cpp"
            )
elseif (${platform} STREQUAL ${win})

    list(APPEND sourceFiles
            "Engine/Platform/Glfw/GlfwContext.cpp"
            "Engine/Platform/Glfw/GlfwInput.cpp"
            "Engine/Platform/Windows/WindowsAssetManager.cpp"
            "ThirdParty/imgui/imgui.cpp"
            "ThirdParty/imgui/imgui_draw.cpp"
            "ThirdParty/imgui/imgui_impl_glfw.cpp"
            "ThirdParty/imgui/imgui_impl_opengl3.cpp"
            "ThirdParty/imgui/imgui_tables.cpp"
            "ThirdParty/imgui/imgui_widgets.cpp"
    )
endif()

if(${platform} STREQUAL ${android})
    add_library(${PROJECT_NAME} SHARED ${sourceFiles})
elseif (${platform} STREQUAL ${win})
    add_executable(${PROJECT_NAME} ${sourceFiles})
endif()

## -------------------- INCLUDE DIRS --------------------

set(includeDirectories
        ThirdParty/glm
        ThirdParty/stb
        ThirdParty/tinyobjloader

        Engine/Core
        Engine/Modules/Terrain
        Engine/Modules/ParticleSystem
        Engine/Platform
        Engine/Rendering
        Engine/Resource
        Engine/Math
        Engine/Memory

        Game
        Game/Scene
)

if(${platform} STREQUAL ${android})
    list(APPEND includeDirectories
            Engine/Platform/Android
    )
elseif (${platform} STREQUAL ${win})
    list(APPEND includeDirectories
            ThirdParty/glew/include
            ThirdParty/glfw/include
            ThirdParty/imgui

            Engine/Platform/Windows
            Engine/Platform/Glfw
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${includeDirectories})


## -------------------- PREPROCESSOR MACROS --------------------

target_compile_definitions(${PROJECT_NAME} PUBLIC ANDROID=${android})
target_compile_definitions(${PROJECT_NAME} PUBLIC WIN=${win})
target_compile_definitions(${PROJECT_NAME} PUBLIC PLATFORM=${platform})

if (${platform} STREQUAL ${win})
    target_compile_definitions(${PROJECT_NAME} PRIVATE GLEW_STATIC)
    target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="C:/Users/Abdullah/AndroidStudioProjects/Space/app/src/main/assets/")
endif()

## -------------------- PACKAGE FIND --------------------

if(${platform} STREQUAL ${android})
    find_package(game-activity REQUIRED CONFIG)
elseif (${platform} STREQUAL ${win})
    find_package(OpenGL REQUIRED)
endif()

## -------------------- LINKING --------------------

if(${platform} STREQUAL ${android})
    target_link_libraries(${PROJECT_NAME}
            game-activity::game-activity
            EGL
            GLESv3
            jnigraphics
            android
            log)
elseif (${platform} STREQUAL ${win})

    target_link_directories(${PROJECT_NAME} PRIVATE
        ThirdParty/glew/lib
        ThirdParty/glfw/lib
    )

    target_link_libraries(${PROJECT_NAME} PRIVATE
            OpenGL::GL
            glew32s
            glfw3)
endif()