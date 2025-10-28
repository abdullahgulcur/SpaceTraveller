#pragma once

#include <jni.h>
#include <game-activity/GameActivity.h>
#include <game-text-input/gametextinput.h>
#include <game-activity/native_app_glue/android_native_app_glue.h>
//#include <game-activity/native_app_glue/android_native_app_glue.c>

class AndroidApplication {
private:

    static AndroidApplication* instance;
    bool appStarted = false;

public:

    android_app* app;

    //AndroidApplication(android_app* application);
    ~AndroidApplication() {}

    void init(android_app* app);
    void run();
    void handleCommand(int32_t cmd);
    static void handle_cmd_proxy(android_app* app, int32_t cmd);
    static bool motion_event_filter_func(const GameActivityMotionEvent *motionEvent);
    static AndroidApplication* getInstance();

    //static void init(android_app *app_);

};