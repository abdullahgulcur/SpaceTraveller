#include "pch.h"

#if PLATFORM == ANDROID

#include <jni.h>
#include <game-activity/GameActivity.cpp>
#include <game-text-input/gametextinput.cpp>
#include <game-activity/native_app_glue/android_native_app_glue.c>

#include "AndroidApplication.h"

extern "C" void android_main(struct android_app* app) {

    AndroidApplication* instance = AndroidApplication::getInstance();
    instance->init(app);
    instance->run();
}

#elif PLATFORM == WIN

#include "WindowsApplication.h"

int main() {

    WindowsApplication* instance = WindowsApplication::getInstance();
    instance->run();
    return 0;
}

#endif




//
//#include <glew.h>
//#include <glfw3.h>
//#include <thread>
//#include <iostream>
//#include <vector>
//#include <atomic>
//#include <chrono>
//
//// Shared texture ID
//GLuint sharedTexture = 0;
//
//// Sync object for GPU sync
//GLsync syncObj = nullptr;
//
//// Flags to coordinate threads
////std::atomic<bool> textureReady(false);
//
//GLFWwindow* mainWindow = nullptr;
//GLFWwindow* workerWindow = nullptr;
//
//// Create a simple 2x2 red texture in the worker context
//void workerThreadFunc() {
//    glfwMakeContextCurrent(workerWindow);
//
//    // Init GLEW for this context
//    glewExperimental = true;
//    if (glewInit() != GLEW_OK) {
//        std::cerr << "Failed to init GLEW in worker\n";
//        return;
//    }
//
//    glGenTextures(1, &sharedTexture);
//    glBindTexture(GL_TEXTURE_2D, sharedTexture);
//
//    // Simple 2x2 red pixels (RGBA)
//    unsigned char pixels[] = {
//        255, 127, 65, 255,  255, 0, 0, 255,
//        255, 0, 0, 255,  255, 0, 0, 255
//    };
//
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
//
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//    glFlush(); // Ensure commands are pushed
//
//    // Insert fence sync to signal render thread
//    syncObj = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
//
//    //textureReady.store(true);
//
//    //// Keep context current to avoid destruction during test
//    //while (textureReady.load()) {
//    //    std::this_thread::sleep_for(std::chrono::milliseconds(10));
//    //}
//}
//
//// Simple rendering in main thread: draws a fullscreen quad textured with sharedTexture
//void renderLoop() {
//    glfwMakeContextCurrent(mainWindow);
//
//    glewExperimental = true;
//    if (glewInit() != GLEW_OK) {
//        std::cerr << "Failed to init GLEW in main thread\n";
//        return;
//    }
//
//    // Simple shader-less rendering (using fixed pipeline, requires compatibility context)
//    // Alternatively, user can create shaders. Here, just clear screen and bind texture to show it's valid.
//
//
//    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
//
//    while (!glfwWindowShouldClose(mainWindow)) {
//        //if (!textureReady.load()) {
//        //    std::this_thread::sleep_for(std::chrono::milliseconds(10));
//        //    continue;
//        //}
//
//        // Wait for worker to finish texture upload
//        if (syncObj) {
//            GLenum waitResult = glClientWaitSync(syncObj, GL_SYNC_FLUSH_COMMANDS_BIT, 1000000000);
//            if (waitResult == GL_ALREADY_SIGNALED || waitResult == GL_CONDITION_SATISFIED) {
//                glDeleteSync(syncObj);
//                syncObj = nullptr;
//            }
//            else {
//                // Timeout or error
//                std::cerr << "Waiting for sync failed\n";
//                continue;
//            }
//        }
//
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        // Bind texture and draw textured quad here
//        // For simplicity, let's just clear screen green if texture ready
//
//        glBindTexture(GL_TEXTURE_2D, sharedTexture);
//
//        std::vector<unsigned char> pixels(2 * 2 * 4);
//        glBindTexture(GL_TEXTURE_2D, sharedTexture);
//        glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
//
//        // Here you'd bind VAO/VBO and shaders to draw textured quad.
//        // For minimal demo, just clear green:
//        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        glfwSwapBuffers(mainWindow);
//        glfwPollEvents();
//    }
//
//    //textureReady.store(false);
//}
//
//int main() {
//    if (!glfwInit()) {
//        std::cerr << "Failed to init GLFW\n";
//        return -1;
//    }
//
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    mainWindow = glfwCreateWindow(640, 480, "Main Window", nullptr, nullptr);
//    if (!mainWindow) {
//        std::cerr << "Failed to create main window\n";
//        glfwTerminate();
//        return -1;
//    }
//
//    //glfwMakeContextCurrent(mainWindow);
//
//    //glewExperimental = true;
//    //if (glewInit() != GLEW_OK) {
//    //    std::cerr << "Failed to init GLEW in main thread\n";
//    //    return -1;
//    //}
//
//    // Now create worker window with sharing enabled
//    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
//    workerWindow = glfwCreateWindow(1, 1, "", nullptr, mainWindow);
//    if (!workerWindow) {
//        std::cerr << "Failed to create worker window\n";
//        glfwTerminate();
//        return -1;
//    }
//
//    // Start worker thread
//    std::thread worker(workerThreadFunc);
//
//    // Run render loop in main thread
//    renderLoop();
//
//    worker.join();
//
//    glfwDestroyWindow(workerWindow);
//    glfwDestroyWindow(mainWindow);
//    glfwTerminate();
//
//    return 0;
//}
