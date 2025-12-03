#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
    glm::vec3 mPos;
    glm::vec3 mFront;
    glm::vec3 mUp;
    float mFOV;

    bool mFirstMouse;
    float mLastX;
    float mLastY;
    float mYaw;
    float mPitch;
public:
    Camera();
};

