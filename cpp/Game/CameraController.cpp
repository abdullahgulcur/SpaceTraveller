#include "pch.h"
#include "Camera.h"
#include "CameraController.h"
#include "AppSurface.h"
#include "Core.h"
#include "Input.h"

namespace Game{

    void CameraController::init(Engine::Camera::Camera& camera){

        //Engine::Camera::perspectiveProjection(camera.projection, 90.0f, Engine::Core::getInstance()->appSurface.getAspectRatio(), 0.1f, 1000.0f);
    }

    void CameraController::update(Engine::Camera::Camera& camera, float dt){

//        Engine::Core* core = Engine::Core::getInstance();
//        Engine::Camera::perspectiveProjection(camera.projection, 90.0f, core->appSurface.getAspectRatio(), 0.1f, 1000.0f);
//
//#if PLATFORM == WIN
//        if(core->input.getButtonDown(Engine::InputCode::Mouse_Left)) {
//#endif
//            // TODO
////            targetHorizontalAngle += -core->input.getPointerDelta().x * 0.01f;
////            horizontalAngle = glm::mix(horizontalAngle, targetHorizontalAngle, 0.1);
//
//            //core->input.set
//
//#if PLATFORM == WIN
//        }
//#endif
//
//        float radius = 5;
//        camera.position = glm::vec3(radius * glm::sin(horizontalAngle), 0, radius * glm::cos(horizontalAngle));
//        Engine::Camera::view(camera.view, camera.position, glm::vec3(0));
    }

}