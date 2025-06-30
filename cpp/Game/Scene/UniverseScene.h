#pragma once

#include "Universe.h"
#include "OrbitCameraController.h"
#include "CameraController.h"
#include "TranslateCameraController.h"
//#include "StraightMoveCameraController.h"
#include "Timer.h"

namespace Game {

    enum class StateCamera {
        UNIVERSE_IDLE = 0,
        UNIVERSE_MOVE = 1,
        UNIVERSE_MOVE_TARGET = 2,
        SOLAR_SYSTEM_IDLE = 3,
        SOLAR_SYSTEM_MOVE = 4,
        SOLAR_SYSTEM_MOVE_TARGET = 5,
        ORBIT_IDLE = 6,
        ORBIT_MOVE = 7,
        ORBIT_MOVE_TARGET = 8
    };

    class UniverseScene {
    private:

        //glm::vec3 previousCameraPosition;
        //float getCameraSpeed(float dt);

        StaticArray<Planet, 16> currentPlanetList;
        StaticArray<Satellite, 16> currentSatelliteList;
        StaticArray<Planet, 16> previousPlanetList;
        StaticArray<Satellite, 16> previousSatelliteList;
        Sun currentSun;
        Sun previousSun;
        Planet currentPlanet;

        CameraController cameraCtrl;
        TranslateCameraController translateCameraCtrl;
        //StraightMoveCameraController straightMoveCameraController;

        StateCamera stateCameraMovement;

    public:

        UniverseScene() {}
        ~UniverseScene() {}

        void init();
        void start();
        void update(float dt);

        void stateUniverseIdle(float dt);
        void stateUniverseMoveTarget(float dt);
        void solarSystemIdle(float dt);
        void stateSolarSystemMoveTarget(float dt);
        void stateOrbitIdle(float dt);
        void stateOrbitMoveTarget(float dt);

        glm::vec3 getArrivalPoint(glm::vec3& sunPosition);
        glm::vec3 getArrivalPointPlanet(glm::vec3& planetPosition, glm::vec3& sunPosition);
        void setCameraTransformQueue(glm::vec3& arrivalPoint, glm::vec3& lastLookAtPosition);
        glm::vec2 getPointScreenSpacePosition(glm::mat4& projectionView, glm::vec3& position);
        void setPlanetList(unsigned int solarSystemId);
        void cleanPreviousSolarSystem();

        void renderSolarSystem();
        void renderStars();

        bool solarSystemClick();
        bool planetClick();

        void translateCameraUpdate(float dt);
    };
}