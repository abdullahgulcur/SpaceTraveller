#include "pch.h"
#include "TranslateCameraController.h""
#include "gtc/matrix_transform.hpp"

namespace Game{

	void TranslateCameraController::init() {
		stopWatch.start();
		isUpdating = true;
	}

	void TranslateCameraController::update(float dt) {

		float duration = stopWatch.getDuration();

		unsigned int sequence = -1;
		for (int i = 0; i < 2; i++) {
			if (duration >= durationQueue[i] && duration < durationQueue[i + 1]) {
				sequence = i;
				break;
			}
		}

		if (sequence == -1) {
			isUpdating = false;
			return;
		}

		float alpha = (duration - durationQueue[sequence]) / (durationQueue[sequence + 1] - durationQueue[sequence]);
		alpha = glm::pow(glm::smoothstep(0.f, 1.f, alpha), 1.5f);

		currentTransform.position = glm::mix(transformQueue[sequence].position, transformQueue[sequence + 1].position, alpha);
		currentTransform.pitch = glm::mix(transformQueue[sequence].pitch, transformQueue[sequence + 1].pitch, alpha);
		currentTransform.yaw = glm::mix(transformQueue[sequence].yaw, transformQueue[sequence + 1].yaw, alpha);
	}

	glm::vec3 TranslateCameraController::getPosition() const {
		return currentTransform.position;
	}

	glm::vec3 TranslateCameraController::getForward() const {
		float radPitch = glm::radians(currentTransform.pitch);
		float radYaw = glm::radians(currentTransform.yaw);

		glm::vec3 dir;
		dir.x = cos(radPitch) * cos(radYaw);
		dir.y = sin(radPitch);
		dir.z = cos(radPitch) * sin(radYaw);

		return glm::normalize(dir);
	}

	//void TranslateCameraController::clampAngles() {

	//}

	//void TranslateCameraController::push(Engine::Camera::CameraTransform cameraTransform, float duration) {

	//}

}