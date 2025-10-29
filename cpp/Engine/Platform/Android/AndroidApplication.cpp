#include "pch.h"
#include "AndroidApplication.h"
#include "Game.h"

AndroidApplication* AndroidApplication::instance;

void AndroidApplication::init(android_app* app){
    this->app = app;
    app->userData = this;
    app->onAppCmd = handle_cmd_proxy;
    android_app_set_motion_event_filter(app, motion_event_filter_func);
}

void AndroidApplication::handle_cmd_proxy(android_app* app, int32_t cmd) {

    AndroidApplication::getInstance()->handleCommand(cmd);
}

void AndroidApplication::handleCommand(int32_t cmd) {
    switch (cmd) {
        case APP_CMD_INIT_WINDOW: {
            Game::Game::getInstance()->init();
            appStarted = true;
            break;
        }
        case APP_CMD_TERM_WINDOW: {
            if (app->userData) {
                Game::Game* gameInstance = Game::Game::getInstance();
                gameInstance->shouldOpen = false;
                gameInstance->shutDown();
            }
            break;
        }
        default:
            break;
    }
}

bool AndroidApplication::motion_event_filter_func(const GameActivityMotionEvent *motionEvent) {
    auto sourceClass = motionEvent->source & AINPUT_SOURCE_CLASS_MASK;
    return (sourceClass == AINPUT_SOURCE_CLASS_POINTER ||
            sourceClass == AINPUT_SOURCE_CLASS_JOYSTICK);
}

void AndroidApplication::run() {
    while (!app->destroyRequested) {
        bool done = false;
        while (!done) {
            int events;
            android_poll_source* pSource;
            int result = ALooper_pollOnce(0, nullptr, &events, reinterpret_cast<void**>(&pSource));
            switch (result) {
                case ALOOPER_POLL_TIMEOUT:
                case ALOOPER_POLL_WAKE:
                    done = true;
                    break;
                default:
                    if (pSource) pSource->process(app, pSource);
                    break;
            }
        }

        if(appStarted){
            Game::Game* gameInstance = Game::Game::getInstance();
            if (gameInstance->shouldOpen)
                gameInstance->update();
        }
    }
}

AndroidApplication* AndroidApplication::getInstance() {
    if (!instance)
        instance = new AndroidApplication;
    return instance;
}

AAssetManager* AndroidApplication::getAssetManager(){
    return AndroidApplication::getInstance()->app->activity->assetManager;
}

android_app* AndroidApplication::getAndroidApp(){
    return AndroidApplication::getInstance()->app;
}

ANativeWindow* AndroidApplication::getAndroidWindow(){
    return AndroidApplication::getInstance()->app->window;
}