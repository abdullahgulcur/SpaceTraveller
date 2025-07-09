#include "pch.h"
#include "AndroidInput.h"
#include "BitOperation.h"

namespace Engine {

    void AndroidInput::init() {

        for(int i = 0; i < 8; i++){
            pointerPositionLastPress[i] = glm::ivec2(0);
            pointerPosition[i] = glm::ivec2(0);
            pointerDelta[i] = glm::ivec2(0);
        }
    }

    void AndroidInput::update() {

        clickBuffer = 0;

        auto *inputBuffer = android_app_swap_input_buffers(AndroidApplication::application);
        if (!inputBuffer)
            return;

        AndroidInput::handleMotionEvents(inputBuffer);
        AndroidInput::handleKeyEvents(inputBuffer);
    }

    void AndroidInput::handleMotionEvents(android_input_buffer* inputBuffer){

        auto pressScreen = [&](int index) {

            BitOperation::setBit(downBuffer, index);
            BitOperation::clearBit(upLockBuffer, index);

            if (!BitOperation::getBit(pressLockBuffer, index)) {
                BitOperation::setBit(pressBuffer, index);
                BitOperation::setBit(pressLockBuffer, index);
            }

        };

        auto releaseScreen = [&](int index) {

            BitOperation::clearBit(downBuffer, index);
            BitOperation::clearBit(pressLockBuffer, index);

            if (!BitOperation::getBit(upLockBuffer, index)) {
                BitOperation::setBit(upBuffer, index);
                BitOperation::setBit(upLockBuffer, index);
            }
        };

        auto clickScreen = [&](int index) {

            BitOperation::setBit(clickBuffer, index);
        };

        pressBuffer = 0;
        upBuffer = 0;
        //downBuffer = 0;

        // handle motion events (motionEventsCounts can be 0).
        for (auto i = 0; i < inputBuffer->motionEventsCount; i++) {
            auto &motionEvent = inputBuffer->motionEvents[i];
            auto action = motionEvent.action;

            // Find the pointer index, mask and bitshift to turn it into a readable value.
            auto pointerIndex = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)
                    >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
            //aout << "Pointer(s): ";

            // get the x and y position of this event if it is not ACTION_MOVE.
            auto &pointer = motionEvent.pointers[pointerIndex];
            auto x = GameActivityPointerAxes_getX(&pointer);
            auto y = GameActivityPointerAxes_getY(&pointer);

            // determine the action type and process the event accordingly.
            switch (action & AMOTION_EVENT_ACTION_MASK) {
                case AMOTION_EVENT_ACTION_DOWN:
                case AMOTION_EVENT_ACTION_POINTER_DOWN:{

                    pointerPosition[pointer.id] = glm::ivec2(x,y);
                    pressScreen(pointer.id);
                    //aout << "(" << pointer.id << ", " << x << ", " << y << ") "
                    //<< "Pointer Down";
                    break;
                }
                case AMOTION_EVENT_ACTION_CANCEL:
                    // treat the CANCEL as an UP event: doing nothing in the app, except
                    // removing the pointer from the cache if pointers are locally saved.
                    // code pass through on purpose.
                case AMOTION_EVENT_ACTION_UP:
                case AMOTION_EVENT_ACTION_POINTER_UP:

                    pointerPosition[pointer.id] = glm::ivec2(x,y);
                    pointerDelta[pointer.id] = glm::ivec2(0);
                    releaseScreen(pointer.id);
                    //aout << "(" << pointer.id << ", " << x << ", " << y << ") "
                    //<< "Pointer Up";
                    break;

                case AMOTION_EVENT_ACTION_MOVE:
                    // There is no pointer index for ACTION_MOVE, only a snapshot of
                    // all active pointers; app needs to cache previous active pointers
                    // to figure out which ones are actually moved.
                    for (auto index = 0; index < motionEvent.pointerCount; index++) {
                        pointer = motionEvent.pointers[index];
                        x = GameActivityPointerAxes_getX(&pointer);
                        y = GameActivityPointerAxes_getY(&pointer);

                        glm::ivec2 newPosition = glm::ivec2(x,y);
                        pointerDelta[pointer.id] = newPosition - pointerPosition[pointer.id];
                        pointerPosition[pointer.id] = newPosition;

                        //aout << "(" << pointer.id << ", " << x << ", " << y << ")";

                        //if (index != (motionEvent.pointerCount - 1)) aout << ",";
                        //aout << " ";
                    }
                    // << "Pointer Move";
                    break;
                default:
                    //aout << "Unknown MotionEvent Action: " << action;
            }
            //aout << std::endl;
        }
        // clear the motion input count in this buffer for main thread to re-use.
        android_app_clear_motion_events(inputBuffer);


        //------------- Click ------------- 

        for(int i = 0; i < 8; i++){
            if (AndroidInput::getScreenPress(i))
                pointerPositionLastPress[i] = pointerPosition[i];

            if (AndroidInput::getScreenUp(i)) {
                if (glm::distance(glm::vec2(pointerPositionLastPress[i]), glm::vec2(pointerPosition[i])) < 50.f)
                    clickScreen(i);
            }
        }
    }

    void AndroidInput::handleKeyEvents(android_input_buffer* inputBuffer){

        // handle input key events.
        for (auto i = 0; i < inputBuffer->keyEventsCount; i++) {
            auto &keyEvent = inputBuffer->keyEvents[i];
            //aout << "Key: " << keyEvent.keyCode <<" ";
            switch (keyEvent.action) {
                case AKEY_EVENT_ACTION_DOWN:
                    //aout << "Key Down";
                    break;
                case AKEY_EVENT_ACTION_UP:
                    //aout << "Key Up";
                    break;
                case AKEY_EVENT_ACTION_MULTIPLE:
                    // Deprecated since Android API level 29.
                    //aout << "Multiple Key Actions";
                    break;
                default:
                    //aout << "Unknown KeyEvent Action: " << keyEvent.action;
            }
            //aout << std::endl;
        }
        // clear the key input count too.
        android_app_clear_key_events(inputBuffer);
    }

    bool AndroidInput::getScreenDown(unsigned int index) {
        return BitOperation::getBit(downBuffer, index);
    }

    bool AndroidInput::getScreenPress(unsigned int index) {
        return BitOperation::getBit(pressBuffer, index);
    }

    bool AndroidInput::getScreenUp(unsigned int index) {
        return BitOperation::getBit(upBuffer, index);
    }

    bool AndroidInput::getScreenClick(unsigned int index) {
        return BitOperation::getBit(clickBuffer, index);
    }


}