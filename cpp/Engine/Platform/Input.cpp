#include "pch.h"
#include "Input.h"

#ifdef PLATFORM "ANDROID"
#include "AndroidInput.h"
#elif PLATFORM "WIN"

#endif

namespace Engine {

    void Input::init() {
#ifdef PLATFORM "ANDROID"
        AndroidInput input;
        input.init(*this);
#elif PLATFORM "WIN"

#endif
    }

    void Input::update(){

#ifdef PLATFORM "ANDROID"
        AndroidInput input;
        input.update(*this);
#elif PLATFORM "WIN"

#endif

    }

}