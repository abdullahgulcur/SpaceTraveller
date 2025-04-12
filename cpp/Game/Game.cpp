#include "pch.h"
#include "Game.h"

namespace Game{

    Game* Game::instance;

    void Game::init(){

        scene.init();
    }

    void Game::update(float dt){

        scene.update(dt);
    }

    Game* Game::getInstance() {
        if (!instance)
            instance = new Game;
        return instance;
    }
}