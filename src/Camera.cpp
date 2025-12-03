#include "Camera.h"

Camera::Camera() {
    mFront = glm::vec3(0.0f, 0.0f, -1.0f);
    mUp = glm::vec3(0.0f, 1.0f,  0.0f);
    mPos = glm::vec3(7.0f, 7.0f,  7.0f);
    mFOV = 45.0f;
    mFirstMouse = true;

    mLastX = 400;
    mLastY = 300;
    mYaw = -90.0f;
    mPitch = 0.0f;
}
