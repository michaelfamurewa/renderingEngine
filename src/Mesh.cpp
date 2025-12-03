#include "Mesh.h"
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

Mesh::Mesh() {
    mColor = glm::vec3(1.0f);
    mPosition = glm::vec3(0.0f, 0.0f, 2.0f);
}

Mesh::~Mesh() {
    std::cout << "MESH DESTRUCTOR CALLED!" << "\n";
    mShader.Unbind();
    mVAO.Unbind();
    mIBO.Unbind();
    mVBO.Unbind();
}

void Mesh::Init(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
    mVBO.Init(vertices);
    mIBO.Init(indices);
    mShader.Init((std::string&) "../res/shaders/default.shader");
    mModel = glm::mat4(1.0f);
    mModel = glm::translate(mModel, glm::vec3(1.0f, 2.0f, 0.0f));
    mModel = glm::scale(mModel, glm::vec3(0.5f, 0.5f,0.5f));
}

void Mesh::Init(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, std::vector<std::string> &textures) {
    mVBO.Init(vertices);
    mIBO.Init(indices);
    mShader.Init((std::string&) "../res/shaders/default.shader");
    mTextures.reserve(textures.size());
    for(unsigned int i = 0; i < textures.size(); i++){
        mTextures.emplace_back();
        mTextures[i].Init(textures[i],i);
    }
}

void Mesh::SetupMesh() {
    mVAO.Bind();
    mVBO.Bind();
    mIBO.Bind();
    mShader.Bind();

    for(Texture& texture: mTextures){
        texture.Bind();
    }

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex,Normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,TexCoords));

}

void Mesh::SetShader(std::string &filepath) {
    mShader.Init(filepath);
}

void Mesh::SetColor(glm::vec3 color) {
    mColor = color;
}

VertexBuffer& Mesh::GetVBO() {
    return mVBO;
}

VertexArray& Mesh::GetVAO() {
    return mVAO;
}

IndexBuffer& Mesh::GetIBO() {
    return mIBO;
}

Shader& Mesh::GetShader() {
    return mShader;
}

glm::mat4 &Mesh::GetModelMatrix() {
    return mModel;
}

glm::vec3 Mesh::GetPosition() {
    return mPosition;
}

glm::vec3 Mesh::GetColor() {
    return mColor;
}

void Mesh::LoadUniform(std::string &name, std::variant<int, float, float*, glm::vec3, glm::vec4, glm::mat4> val, UniformTypes type) {
    UniformObject obj = {type, val};
    mUniforms[name] = obj;
}

void Mesh::SetPosition(glm::vec3 position) {
    mPosition = position;
}

void Mesh::SetUniforms() {

    GetVAO().Bind();
    GetVBO().Bind();
    GetIBO().Bind();
    GetShader().Bind();

    for(auto& item : mUniforms){
        std::string name = item.first;
        switch (item.second.type) {
            case INT:
                mShader.SetUniform1i(name, std::get<int>(item.second.value));
                break;
            case FLOAT:
                mShader.SetUniform1f(name, std::get<float>(item.second.value));
                break;
            case VEC4:
                mShader.SetUniform4f(name, std::get<glm::vec4>(item.second.value).x, std::get<glm::vec4>(item.second.value).y, std::get<glm::vec4>(item.second.value).z,std::get<glm::vec4>(item.second.value).w);
                break;
            case VEC3:
               mShader.SetUniform3f(name, std::get<glm::vec3>(item.second.value).x,std::get<glm::vec3>(item.second.value).y,std::get<glm::vec3>(item.second.value).z);
                break;
            case MAT4:
                mShader.SetUniformMatrix4fv(name, 1, GL_FALSE, std::get<float*>(item.second.value));
                break;
            default:
                std::cout << "UNIFORM TYPE: " << item.second.type << " NOT IMPLEMENTED!" << "\n";
                break;
        }
    }
}

void Mesh::Translate(glm::vec3 &position) {
    mModel = glm::mat4(1.0);
    mModel = glm::translate(mModel, position);
    mPosition = position;
}

void Mesh::Rotate(float degrees, glm::vec3 &axis) {
    mModel = glm::mat4(1.0);
    mModel = glm::rotate(mModel, glm::radians(degrees),axis);
}

void Mesh::Scale(glm::vec3 &scalar) {
    mModel = glm::mat4(1.0);
    mModel = glm::scale(mModel, scalar);
}


