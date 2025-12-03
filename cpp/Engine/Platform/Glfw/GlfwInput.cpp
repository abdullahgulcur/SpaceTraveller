#include "pch.h"
#include "GlfwInput.h"
#include "BitOperation.h"

namespace Engine {

    void GlfwInput::init(GLFWwindow* glfwMainWindow) {
        this->glfwMainWindow = glfwMainWindow;
    }

    void GlfwInput::update() {

		auto getMousePress = [&](GlfwInputCode key) {
			return glfwGetMouseButton(glfwMainWindow, int(key)) == GLFW_PRESS;
		};

		auto getMouseRelease = [&](GlfwInputCode key) {
			return glfwGetMouseButton(glfwMainWindow, int(key)) == GLFW_RELEASE;
		};

		auto getKeyPress = [&](GlfwInputCode key) {
			return glfwGetKey(glfwMainWindow, int(key)) == GLFW_PRESS;
		};

		auto getKeyRelease = [&](GlfwInputCode key) {
			return glfwGetKey(glfwMainWindow, int(key)) == GLFW_RELEASE;
		};

		auto pressButton = [&](InputCode key) {

			BitOperation::setBit(downBuffer, int(key));
			BitOperation::clearBit(upLockBuffer, int(key));

			if (!BitOperation::getBit(pressLockBuffer, int(key))) {
				BitOperation::setBit(pressBuffer, int(key));
				BitOperation::setBit(pressLockBuffer, int(key));
			}

		};

		auto releaseButton = [&](InputCode key) {

			BitOperation::clearBit(downBuffer, int(key));
			BitOperation::clearBit(pressLockBuffer, int(key));

			if (!BitOperation::getBit(upLockBuffer, int(key))) {
				BitOperation::setBit(upBuffer, int(key));
				BitOperation::setBit(upLockBuffer, int(key));
			}
		};

		auto clickButton = [&](InputCode key) {

			BitOperation::setBit(clickBuffer, int(key));
		};

		pressBuffer = 0;
		upBuffer = 0;
		downBuffer = 0;
		clickBuffer = 0;

		scrollDelta = 0.f;

		glm::ivec2 newPointerPos;
		GlfwInput::getCursorPos(newPointerPos);



		pointerDelta = newPointerPos - pointerPosition;

		//std::cout << "pointer delta x: " << pointerDelta.x << std::endl;


		pointerPosition = newPointerPos;

		//------------- Press ------------- 

		if (getMousePress(GlfwInputCode::Mouse_Left))
			pressButton(InputCode::Mouse_Left);

		if (getMousePress(GlfwInputCode::Mouse_Right))
			pressButton(InputCode::Mouse_Right);

		if (getMousePress(GlfwInputCode::Mouse_Middle))
			pressButton(InputCode::Mouse_Middle);

        if (getKeyPress(GlfwInputCode::Q))
			pressButton(InputCode::Q);

		if (getKeyPress(GlfwInputCode::W))
			pressButton(InputCode::W);

		if (getKeyPress(GlfwInputCode::E))
			pressButton(InputCode::E);

		if (getKeyPress(GlfwInputCode::A))
			pressButton(InputCode::A);

		if (getKeyPress(GlfwInputCode::S))
			pressButton(InputCode::S);

		if (getKeyPress(GlfwInputCode::D))
			pressButton(InputCode::D);

		if (getKeyPress(GlfwInputCode::Space))
			pressButton(InputCode::Space);

		if (getKeyPress(GlfwInputCode::LShift))
			pressButton(InputCode::LShift);

		//------------- Release ------------- 

		if (getMouseRelease(GlfwInputCode::Mouse_Left))
			releaseButton(InputCode::Mouse_Left);

		if (getMouseRelease(GlfwInputCode::Mouse_Right))
			releaseButton(InputCode::Mouse_Right);

		if (getMouseRelease(GlfwInputCode::Mouse_Middle))
			releaseButton(InputCode::Mouse_Middle);

		if (getKeyRelease(GlfwInputCode::Q))
			releaseButton(InputCode::Q);

		if (getKeyRelease(GlfwInputCode::W))
			releaseButton(InputCode::W);

		if (getKeyRelease(GlfwInputCode::E))
			releaseButton(InputCode::E);

		if (getKeyRelease(GlfwInputCode::A))
			releaseButton(InputCode::A);

		if (getKeyRelease(GlfwInputCode::S))
			releaseButton(InputCode::S);

		if (getKeyRelease(GlfwInputCode::D))
			releaseButton(InputCode::D);

		if (getKeyRelease(GlfwInputCode::Space))
			releaseButton(InputCode::Space);

		if (getKeyRelease(GlfwInputCode::LShift))
			releaseButton(InputCode::LShift);

		//------------- Click ------------- 

		if (GlfwInput::getButtonPress(InputCode::Mouse_Left))
			pointerPositionLastPress = pointerPosition;

		if (GlfwInput::getButtonUp(InputCode::Mouse_Left)) {
			if (glm::distance(glm::vec2(pointerPositionLastPress), glm::vec2(pointerPosition)) < 5.f)
				clickButton(InputCode::Mouse_Left);
		}
    }

	bool GlfwInput::getButtonDown(InputCode inputCode) {
		return BitOperation::getBit(downBuffer, int(inputCode));
	}

	bool GlfwInput::getButtonPress(InputCode inputCode) {
		return BitOperation::getBit(pressBuffer, int(inputCode));
	}

	bool GlfwInput::getButtonUp(InputCode inputCode) {
		return BitOperation::getBit(upBuffer, int(inputCode));
	}

	bool GlfwInput::getButtonClick(InputCode inputCode) {
		return BitOperation::getBit(clickBuffer, int(inputCode));
	}

	void GlfwInput::setCursorPos(glm::ivec2 cursorPos) {
		glfwSetCursorPos(glfwMainWindow, cursorPos.x, cursorPos.y);
	}

	void GlfwInput::getCursorPos(glm::ivec2& cursorPos) {
		double xPos, yPos;
		glfwGetCursorPos(glfwMainWindow, &xPos, &yPos);
		cursorPos = glm::ivec2(xPos, yPos);
	}

	void GlfwInput::setCursorVisible(bool visible) {

		int value = visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN;
		glfwSetInputMode(glfwMainWindow, GLFW_CURSOR, value);
	}

}