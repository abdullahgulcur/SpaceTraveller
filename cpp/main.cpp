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