#include "pch.h"
#include "TranslateCameraController.h""
#include "gtc/matrix_transform.hpp"
#include "Algebra.h"
#include "Game.h"

namespace Game {

	void TranslateCameraController::init() {
		stopWatch.start();
		isUpdating = true;

		//TranslateCameraController::update(0.f);
	}

	void TranslateCameraController::update(float dt) {

		float duration = stopWatch.getDuration();

		unsigned int sequence = -1;
		for (int i = 0; i < 3; i++) {
			if (duration >= durationQueue[i] && duration < durationQueue[i + 1]) {
				sequence = i;
				break;
			}
		}

		if (sequence == -1) {
			isUpdating = false;
			return;
		}

		float power = 3.0f; // parameter
		float alpha = (duration - durationQueue[sequence]) / (durationQueue[sequence + 1] - durationQueue[sequence]);
		alpha = Engine::Algebra::parametricSmooth(alpha, power);

		currentTransform.position = glm::mix(transformQueue[sequence].position, transformQueue[sequence + 1].position, alpha);
		currentTransform.pitch = TranslateCameraController::lerpAngle(transformQueue[sequence].pitch, transformQueue[sequence + 1].pitch, alpha);// glm::mix(transformQueue[sequence].pitch, transformQueue[sequence + 1].pitch, alpha);
		currentTransform.yaw = TranslateCameraController::lerpAngle(transformQueue[sequence].yaw, transformQueue[sequence + 1].yaw, alpha);
	}

	float TranslateCameraController::lerpAngle(float a, float b, float t) {
		float diff = fmodf(b - a, 360.0f);
		if (diff > 180.0f) diff -= 360.0f;
		if (diff < -180.0f) diff += 360.0f;
		return a + diff * t;
	}

	void TranslateCameraController::push(Engine::Camera::CameraTransform& cameraTransform, float timeStamp) {
		transformQueue.push(cameraTransform);
		durationQueue.push(timeStamp);
	}

	void TranslateCameraController::cleanQueue() {
		transformQueue.clean();
		durationQueue.clean();
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