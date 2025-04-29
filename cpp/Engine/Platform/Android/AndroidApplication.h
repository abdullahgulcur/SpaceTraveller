#pragma once

#include <game-activity/native_app_glue/android_native_app_glue.h>

class AndroidApplication {
private:

public:

    static android_app* application;

    AndroidApplication();
    ~AndroidApplication() {}

    static void init(android_app *app_);

};