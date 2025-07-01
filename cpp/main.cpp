#include "pch.h"
#include "Core.h"
#include "Game.h"

#if PLATFORM == ANDROID

#include <jni.h>
#include <game-activity/GameActivity.cpp>
#include <game-text-input/gametextinput.cpp>
#include <game-activity/native_app_glue/android_native_app_glue.c>

#include "AndroidApplication.h"

extern "C" {

bool appStarted = false;

/*!
 * Handles commands sent to this Android application
 * @param pApp the app the commands are coming from
 * @param cmd the command to handle
 */
void handle_cmd(android_app *pApp, int32_t cmd) {
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:{

            AndroidApplication::init(pApp);
            Engine::Core* coreInstance = Engine::Core::getInstance();
            Game::Game* gameInstance = Game::Game::getInstance();
            coreInstance->init();
            gameInstance->init();
            appStarted = true;
            break;
        }
        case APP_CMD_TERM_WINDOW:

            if (pApp->userData) {
                Game::Game* gameInstance = Game::Game::getInstance();
                Engine::Core* coreInstance = Engine::Core::getInstance();
                //delete
            }
            break;
        default:
            break;
    }
}

/*!
 * Enable the motion events you want to handle; not handled events are
 * passed back to OS for further processing. For this example case,
 * only pointer and joystick devices are enabled.
 *
 * @param motionEvent the newly arrived GameActivityMotionEvent.
 * @return true if the event is from a pointer or joystick device,
 *         false for all other input devices.
 */
bool motion_event_filter_func(const GameActivityMotionEvent *motionEvent) {
    auto sourceClass = motionEvent->source & AINPUT_SOURCE_CLASS_MASK;
    return (sourceClass == AINPUT_SOURCE_CLASS_POINTER ||
            sourceClass == AINPUT_SOURCE_CLASS_JOYSTICK);
}

void android_main(struct android_app *pApp) {

    // Register an event handler for Android events
    pApp->onAppCmd = handle_cmd;

    // Set input event filters (set it to NULL if the app wants to process all inputs).
    // Note that for key inputs, this example uses the default default_key_filter()
    // implemented in android_native_app_glue.c.
    android_app_set_motion_event_filter(pApp, motion_event_filter_func);

    do {
        // Process all pending events before running game logic.
        bool done = false;
        while (!done) {
            // 0 is non-blocking.
            int timeout = 0;
            int events;
            android_poll_source *pSource;
            int result = ALooper_pollOnce(timeout, nullptr, &events,
                                          reinterpret_cast<void**>(&pSource));
            switch (result) {
                case ALOOPER_POLL_TIMEOUT:
                    [[clang::fallthrough]];
                case ALOOPER_POLL_WAKE:
                    // No events occurred before the timeout or explicit wake. Stop checking for events.
                    done = true;
                    break;
                case ALOOPER_EVENT_ERROR:
                    //aout << "ALooper_pollOnce returned an error" << std::endl;
                    break;
                case ALOOPER_POLL_CALLBACK:
                    break;
                default:
                    if (pSource) {
                        pSource->process(pApp, pSource);
                    }
            }
        }

        if (appStarted) {

            Engine::Core* instance = Engine::Core::getInstance();
            Game::Game* gameInstance = Game::Game::getInstance();
            instance->update();
            gameInstance->update(instance->systemTimer.getDeltaSeconds());
        }
    } while (!pApp->destroyRequested);
}
}

#elif PLATFORM == WIN

int main() {

    std::cout << "Welcome to Space game !" << std::endl;

    Engine::Core* coreInstance = Engine::Core::getInstance();
    Game::Game* gameInstance = Game::Game::getInstance();
    coreInstance->init();
    gameInstance->init();

    while (!coreInstance->appSurface.glfwContext.shouldClose()) {

        //Engine code
        coreInstance->update();

        //Game code
        gameInstance->update(coreInstance->systemTimer.getDeltaSeconds());

        coreInstance->appSurface.update();
    }
   
    return 0;
}

#endif
