#include "Scene.h"
#include "Light.h"
#include <GLFW/glfw3.h>

Scene::Scene() {
    mProjection = glm::perspective(glm::radians(mCamera.mFOV),800.0f/600.0f,0.1f,100.0f);
    mView = glm::lookAt(mCamera.mPos, mCamera.mPos + mCamera.mFront, mCamera.mUp);
}

void Scene::LoadMeshBuffer() {
    float vertices[] = {
                        // positions               // normals           // texture coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    std::vector<Vertex> formattedVertices = VertexBuffer::FormatVertexData(vertices, sizeof(vertices));
    std::vector<unsigned int> indices = VertexBuffer::CreateIndexedData(formattedVertices);
    std::vector<std::string> textures;
    textures.emplace_back((std::string)"../res/textures/container2.png");
    textures.emplace_back((std::string)"../res/textures/container2_specular.png");

    mMeshBuffer["Light"] = new SpotLight;
    mMeshBuffer["Light"]->Init(formattedVertices, indices);
    mMeshBuffer["Light"]->SetupMesh();

    mMeshBuffer["Cube"] = new Mesh;
    mMeshBuffer["Cube"]->Init(formattedVertices, indices, textures);
    mMeshBuffer["Cube"]->SetShader((std::string&)"../res/shaders/basic.shader");
    mMeshBuffer["Cube"]->SetupMesh();

    glm::vec3 pos = glm::vec3(0.0f, 0.0f,  0.0f);
    for(int i = 0; i < 36; i++){
        mPositions.emplace_back(pos);
        pos.x += 2.0f;
        if((i+1) % 6 == 0){
            pos.x = 0.0f;
            pos.y += 2.0f;
        }
    }
}

void Scene::Update(std::string name) {
    glm::vec3 pos;
    pos.x = 2.0f;
    pos.y = sin(glfwGetTime()) + 1;
    pos.z = 0.0f;
    mMeshBuffer[name]->Translate(pos);
}

void Scene::Draw(Renderer &renderer) {

    mView = glm::lookAt(mCamera.mPos, mCamera.mPos + mCamera.mFront, mCamera.mUp);

    SpotLight* light = (SpotLight*)mMeshBuffer["Light"];
    Shader& lightShader = light->GetShader();
    glm::vec3 lightPosition = light->GetPosition();
    glm::vec3 lightDirection = glm::normalize(lightPosition - glm::vec3(lightPosition.x, lightPosition.y, 0.0f));

    Mesh* cube = mMeshBuffer["Cube"];
    Shader& cubeShader = cube->GetShader();
    glm::vec3 lightCol;
    lightCol.x = sin(glfwGetTime() * 0.1f);
    lightCol.y = sin(glfwGetTime() * 0.35f);
    lightCol.z = sin(glfwGetTime() * 0.2f);
    lightShader.Bind();
    light->SetLightColor(lightCol);
    light->Translate(lightPosition);
    lightShader.SetUniformMatrix4fv((std::string&)"model",1,GL_FALSE,glm::value_ptr(light->GetModelMatrix()));
    lightShader.SetUniformMatrix4fv((std::string&)"view",1,GL_FALSE,glm::value_ptr(mView));
    lightShader.SetUniformMatrix4fv((std::string&)"projection",1,GL_FALSE,glm::value_ptr(mProjection));
    lightShader.SetUniform3f((std::string&)"objectColor",light->GetColor().x, light->GetColor().y, light->GetColor().z);
    renderer.DrawByIndex(light->GetVBO(),light->GetIBO());

    cubeShader.Bind();
    cubeShader.SetUniformMatrix4fv((std::string&)"view",1,GL_FALSE,glm::value_ptr(mView));
    cubeShader.SetUniformMatrix4fv((std::string&)"projection",1,GL_FALSE,glm::value_ptr(mProjection));
    cubeShader.SetUniform3f((std::string&)"light.position", lightPosition.x, lightPosition.y, lightPosition.z);
    cubeShader.SetUniform3f((std::string&)"light.direction", lightDirection.x, lightDirection.y, lightDirection.z);
    cubeShader.SetUniform1f((std::string&)"light.cutOff", light->GetCutOff());
    cubeShader.SetUniform1f((std::string&)"light.outerCutOff", light->GetOuterCutOff());
    cubeShader.SetUniform3f((std::string&)"light.ambient", light->GetAmbient().x, light->GetAmbient().y, light->GetAmbient().z);
    cubeShader.SetUniform3f((std::string&)"light.diffuse", light->GetDiffuse().x, light->GetDiffuse().y, light->GetDiffuse().z);
    cubeShader.SetUniform3f((std::string&)"light.specular", light->GetSpecular().x, light->GetSpecular().y, light->GetSpecular().z);
    cubeShader.SetUniform1f((std::string&)"light.constant", light->GetConstant());
    cubeShader.SetUniform1f((std::string&)"light.linear", light->GetLinear());
    cubeShader.SetUniform1f((std::string&)"light.quadratic", light->GetQuadratic());
    cubeShader.SetUniform3f((std::string&)"viewPos", mCamera.mPos.x, mCamera.mPos.y, mCamera.mPos.z);
    cubeShader.SetUniform1i((std::string&)"material.diffuse", 0);
    cubeShader.SetUniform1i((std::string&)"material.specular", 1);
    cubeShader.SetUniform1f((std::string&)"material.shininess", 0.6f);

    for(glm::vec3& pos : mPositions){
        cube->Translate(pos);
        cubeShader.SetUniformMatrix4fv((std::string&)"model",1,GL_FALSE,glm::value_ptr(cube->GetModelMatrix()));
        renderer.DrawByIndex(cube->GetVBO(),cube->GetIBO());
    }
}

Camera &Scene::GetCamera() {
    return mCamera;
}

void Scene::CreateRandomPositions(unsigned int amount, std::vector<glm::vec3> &positions) {
    positions.reserve(amount);
    for(int i = 0; i < amount; i++) {
        float x = (float) ((rand() % 10) - 5);
        float y = (float) ((rand() % 3));
        float z = (float) ((rand() % 10) - 5);
        positions.emplace_back(x, y, z);
    }
}

