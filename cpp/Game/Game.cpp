#include "pch.h"
#include "Game.h"

namespace Game{

    Game* Game::instance;

    void Game::init(){

        scene.init();
    }

    void Game::update(){

        scene.update();
    }

    Game* Game::getInstance() {
        if (!instance)
            instance = new Game;
        return instance;
    }
}