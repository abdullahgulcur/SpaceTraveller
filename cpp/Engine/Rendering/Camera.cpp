#include "pch.h"
#include "camera.h"
#include "ext/matrix_clip_space.hpp"
#include "gtc/matrix_transform.hpp"

namespace Engine{

    namespace Camera{

        void init(Camera& camera, float fovY, float aspect, float zNear, float zFar) {
            camera.fovY = fovY;
            camera.aspect = aspect;
            camera.zNear = zNear;
            camera.zFar = zFar;
            perspectiveProjection(camera);
        }

        void perspectiveProjection(Camera& camera) {
            camera.projection = glm::perspective(glm::radians(camera.fovY), camera.aspect, camera.zNear, camera.zFar);
            camera.projectionView = camera.projection * camera.view;
        }

        void lookAt(Camera& camera, glm::vec3 center, glm::vec3 up) {
            camera.view = glm::lookAt(camera.position, center, up);
            camera.inverseView = glm::inverse(camera.view);
            camera.projectionView = camera.projection * camera.view;
            getCameraRightAndUp(camera);
        }

        void lookAt(Camera& camera, glm::vec3 cameraPosition, glm::vec3 center, glm::vec3 up) {
            camera.position = cameraPosition;
            camera.view = glm::lookAt(camera.position, center, up);
            camera.inverseView = glm::inverse(camera.view);
            camera.projectionView = camera.projection * camera.view;
            getCameraRightAndUp(camera);
        }

        void setFovY(Camera& camera, float fovY) {
            camera.fovY = fovY;
            perspectiveProjection(camera);
        }

        void setAspect(Camera& camera, float aspect) {
            camera.aspect = aspect;
            perspectiveProjection(camera);
        }

        void setZNear(Camera& camera, float zNear) {
            camera.zNear = zNear;
            perspectiveProjection(camera);
        }

        void setZFar(Camera& camera, float zFar) {
            camera.zFar = zFar;
            perspectiveProjection(camera);
        }

        void getCameraRightAndUp(Camera& camera) {
            camera.right = glm::vec3(camera.view[0][0], camera.view[1][0], camera.view[2][0]);
            camera.up = glm::vec3(camera.view[0][1], camera.view[1][1], camera.view[2][1]);
        }

        //void perspectiveProjection(glm::mat4& projection, float fovY, float aspect, float zNear, float zFar) {
        //    projection = glm::perspective(glm::radians(fovY), aspect, zNear, zFar);
        //}

        //void view(glm::mat4& view, glm::vec3& camPos, glm::vec3 center, glm::vec3 up){
        //    view = glm::lookAt(camPos, center, up);
        //}

        //void getCameraRightAndUp(glm::mat4& view, glm::vec3& camRight, glm::vec3& camUp) {
        //    camRight = glm::vec3(view[0][0], view[1][0], view[2][0]);
        //    camUp = glm::vec3(view[0][1], view[1][1], view[2][1]);
        //}

    }
}