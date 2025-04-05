#pragma once

#include "Core.h"
#include "Scene.h"

namespace Game {

    class Game {
    private:

        static Game* instance;

        Scene scene;

    public:

        Game() {}
        ~Game() {}

        void init();
        void update();

        static Game* getInstance();
    };
}