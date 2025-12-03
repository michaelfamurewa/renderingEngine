#pragma once
#include "Mesh.h"
#include "Renderer.h"
#include "Camera.h"

class Scene {
private:
    Camera mCamera;
    glm::mat4 mProjection;
    glm::mat4 mView;
    std::unordered_map<std::string,Mesh*> mMeshBuffer;
    std::vector<glm::vec3> mPositions;
public:
    Scene();
    ~Scene() = default;
    void LoadMeshBuffer();
    void Draw(Renderer& renderer);
    void Update(std::string name);
    void CreateRandomPositions(unsigned int amount, std::vector<glm::vec3>& positions);
    Mesh* GetMesh(const char* name){return mMeshBuffer[name];}
    Camera& GetCamera();
};
