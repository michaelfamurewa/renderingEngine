#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "Shader.h"
#include "Scene.h"
#include "Renderer.h"

class Engine {

private:
    float mDeltaTime = 0.0f;
    float mLastFrame = 0.0f;
    GLFWwindow* mWindow;
    Scene mScene;
    Renderer mRenderer;

public:
    Engine() = default;
    ~Engine();
    int Init(unsigned int width, unsigned int height, const char* title);
    void Run();

private:
    static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    void UpdateCamera(float xpos, float ypos, Camera& camera);
    void ZoomCamera(double yoffset, Camera& camera);
    void ProcessInput(Camera& camera);
    void ProcessInput(Camera& camera, Mesh* obj);
};


