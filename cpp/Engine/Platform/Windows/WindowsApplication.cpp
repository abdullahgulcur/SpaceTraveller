#include "pch.h"
#include "WindowsApplication.h"
#include "Game.h"

WindowsApplication* WindowsApplication::instance;

void WindowsApplication::run() {
    
    Game::Game* gameInstance = Game::Game::getInstance();
    gameInstance->init();
    while (gameInstance->shouldOpen) {
        if (gameInstance->appSurface.shouldClose()) {
            gameInstance->shouldOpen = false;
            gameInstance->shutDown();
        }
        gameInstance->appSurface.pollEvents();
        gameInstance->update();
    }
        
}

WindowsApplication* WindowsApplication::getInstance() {
    if (!instance)
        instance = new WindowsApplication;
    return instance;
}