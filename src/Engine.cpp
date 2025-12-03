#include "Engine.h"
#include <iostream>

Engine::~Engine() {
    glfwTerminate();
}

int Engine::Init(unsigned int width, unsigned int height, const char* title) {

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    mWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (!mWindow){
        glfwTerminate();
        std::cout << "Window creation error!" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(mWindow);
    glfwSetWindowUserPointer(mWindow, this);
    glfwSwapInterval(1);

    if(glewInit() != GLEW_OK){
        std::cout << "GLEW is not working!" << std::endl;
        return -1;
    }

    glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(mWindow, MouseCallback);
    glfwSetScrollCallback(mWindow, ScrollCallback);

    mScene.LoadMeshBuffer();

    return 0;
}

void Engine::Run() {

    glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(mWindow)){

        float currentFrame = glfwGetTime();
        mDeltaTime = currentFrame - mLastFrame;
        mLastFrame = currentFrame;

        mRenderer.Clear();
        ProcessInput(mScene.GetCamera(), mScene.GetMesh("Light"));

        mScene.Draw(mRenderer);

        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }
    glfwTerminate();
}

void Engine::ProcessInput(Camera& camera) {
    const float cameraSpeed = 2.5f * mDeltaTime;
    if(glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(mWindow,1);
    }
    if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS){
        camera.mPos += cameraSpeed * camera.mFront;
    }
    if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS) {
        camera.mPos -= cameraSpeed * camera.mFront;
    }
    if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS) {
        camera.mPos -= glm::normalize(glm::cross(camera.mFront, camera.mUp)) * cameraSpeed;
    }
    if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS) {
        camera.mPos += glm::normalize(glm::cross(camera.mFront, camera.mUp)) * cameraSpeed;
    }
}

void Engine::ProcessInput(Camera& camera, Mesh* obj) {
    const float cameraSpeed = 2.5f * mDeltaTime;
    if(glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(mWindow,1);
    }
    if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS){
        camera.mPos += cameraSpeed * camera.mFront;
    }
    if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS) {
        camera.mPos -= cameraSpeed * camera.mFront;
    }
    if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS) {
        camera.mPos -= glm::normalize(glm::cross(camera.mFront, camera.mUp)) * cameraSpeed;
    }
    if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS) {
        camera.mPos += glm::normalize(glm::cross(camera.mFront, camera.mUp)) * cameraSpeed;
    }
    if (glfwGetKey(mWindow, GLFW_KEY_UP) == GLFW_PRESS) {
        glm::vec3 pos = obj->GetPosition();
        pos.y += 0.25;
        obj->SetPosition(pos);
    }
    if (glfwGetKey(mWindow, GLFW_KEY_DOWN) == GLFW_PRESS) {
        glm::vec3 pos = obj->GetPosition();
        pos.y -= 0.25f;
        obj->SetPosition(pos);
    }
    if (glfwGetKey(mWindow, GLFW_KEY_LEFT) == GLFW_PRESS) {
        glm::vec3 pos = obj->GetPosition();
        pos.x -= 0.25f;
        obj->SetPosition(pos);
    }
    if (glfwGetKey(mWindow, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        glm::vec3 pos = obj->GetPosition();
        pos.x += 0.25f;
        obj->SetPosition(pos);
    }
}

void Engine::UpdateCamera(float xpos, float ypos, Camera& camera) {
    if (camera.mFirstMouse){
        camera.mLastX = xpos;
        camera.mLastY = ypos;
        camera.mFirstMouse = false;
    }

    float xoffset = xpos - camera.mLastX;
    float yoffset = camera.mLastY - ypos;
    camera.mLastX = xpos;
    camera.mLastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera.mYaw   += xoffset;
    camera.mPitch += yoffset;

    if(camera.mPitch > 89.0f)
        camera.mPitch = 89.0f;
    if(camera.mPitch < -89.0f)
        camera.mPitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(camera.mYaw)) * cos(glm::radians(camera.mPitch));
    direction.y = sin(glm::radians(camera.mPitch));
    direction.z = sin(glm::radians(camera.mYaw)) * cos(glm::radians(camera.mPitch));
    camera.mFront = glm::normalize(direction);
}

void Engine::ZoomCamera(double yoffset, Camera& camera) {
    camera.mFOV -= (float)yoffset;
    if (camera.mFOV < 1.0f) {
        camera.mFOV = 1.0f;
    }
    if (camera.mFOV > 45.0f) {
        camera.mFOV = 45.0f;
    }
}


void Engine::MouseCallback(GLFWwindow* window, double xpos, double ypos) {
    auto e = (Engine*)glfwGetWindowUserPointer(window);
    e->UpdateCamera(xpos, ypos, e->mScene.GetCamera());
}

void Engine::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    auto e = (Engine*)glfwGetWindowUserPointer(window);
    e->ZoomCamera(yoffset, e->mScene.GetCamera());
}




