# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.22.1)

project("space")

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB sourceFiles

        "main.cpp"

        "Game/Game.cpp"
        "Game/Scene.cpp"

        "Engine/Core/Core.cpp"
        "Engine/Core/Input.cpp"

        "Engine/Platform/Android/EglContext.cpp"
        "Engine/Platform/Android/AndroidAssetManager.cpp"

        "Engine/Precompiled/pch.cpp"

        "Engine/Rendering/Camera.cpp"
        "Engine/Rendering/IndexBuffer.cpp"
        "Engine/Rendering/SceneRenderer.cpp"
        "Engine/Rendering/ShaderProgram.cpp"
        "Engine/Rendering/StaticMesh.cpp"
        "Engine/Rendering/Texture2D.cpp"
        "Engine/Rendering/Vao.cpp"
        "Engine/Rendering/VertexBuffer.cpp"

        "Engine/Resource/AssetManager.cpp"
        "Engine/Resource/MeshData.cpp"
        "Engine/Resource/TextureData.cpp"

        "ThirdParty/tinyobjloader/tiny_obj_loader.cpp"
        "ThirdParty/stb/stb_image.cpp")

add_library(${PROJECT_NAME} SHARED ${sourceFiles})

target_include_directories(${PROJECT_NAME} PRIVATE ThirdParty/glm
        ThirdParty/stb
        ThirdParty/tinyobjloader
        ThirdParty/assimp

        Game

        Engine/Precompiled

        Engine/Core
        Engine/Platform/Android
        Engine/Platform/Windows
        Engine/Rendering
        Engine/Resource)

# Searches for a package provided by the game activity dependency
find_package(game-activity REQUIRED CONFIG)

# Configure libraries CMake uses to link your target library.
target_link_libraries(${PROJECT_NAME}
        # The game activity
        game-activity::game-activity

        # EGL and other dependent libraries required for drawing
        # and interacting with Android system
        EGL
        GLESv3
        jnigraphics
        android
        log)