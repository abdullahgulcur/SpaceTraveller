#pragma once

#include <jni.h>
#include <game-activity/GameActivity.h>
#include <game-text-input/gametextinput.h>
#include <game-activity/native_app_glue/android_native_app_glue.h>
#include <android/asset_manager.h>
//#include <EGL/egl.h>

class AndroidApplication {
private:

    static AndroidApplication* instance;
    bool appStarted = false;
    android_app* app;
    static void handle_cmd_proxy(android_app* app, int32_t cmd);
    static bool motion_event_filter_func(const GameActivityMotionEvent *motionEvent);
    void handleCommand(int32_t cmd);

public:

    void init(android_app* app);
    void run();
    static AAssetManager* getAssetManager();
    static android_app* getAndroidApp();
    static ANativeWindow* getAndroidWindow();
    static AndroidApplication* getInstance();

};