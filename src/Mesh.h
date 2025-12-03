#pragma once

#include <vector>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

enum UniformTypes{
    INT,
    FLOAT,
    VEC2, VEC3, VEC4,
    MAT4
};

struct UniformObject{
    UniformTypes type;
    std::variant<int, float, float*, glm::vec3, glm::vec4, glm::mat4> value;
};

class Mesh {
protected:
    VertexArray mVAO;
    VertexBuffer mVBO;
    IndexBuffer mIBO;
    Shader mShader;
    std::unordered_map<std::string, UniformObject> mUniforms;
    std::vector<Texture> mTextures;
    glm::mat4 mModel;
    glm::vec3 mPosition;
    glm::vec3 mColor;
public:
    Mesh();
    ~Mesh();
    void Init(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
    void Init(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<std::string>& textures);
    void SetupMesh();
    VertexArray& GetVAO();
    VertexBuffer& GetVBO();
    IndexBuffer& GetIBO();
    Shader& GetShader();
    glm::mat4& GetModelMatrix();
    glm::vec3 GetPosition();
    glm::vec3 GetColor();
    void SetPosition(glm::vec3 position);
    void SetUniforms();
    void SetColor(glm::vec3 color);
    void LoadUniform(std::string& name, std::variant<int, float, float*, glm::vec3, glm::vec4, glm::mat4> val, UniformTypes type);
    void Translate(glm::vec3& position);
    void Rotate(float degrees, glm::vec3& axis);
    void Scale(glm::vec3& scalar);
    void SetShader(std::string& filepath);
};