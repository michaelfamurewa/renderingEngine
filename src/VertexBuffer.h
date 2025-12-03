#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;

    bool operator==(const Vertex& right) const{
        if(!(Position == right.Position)){
            return false;
        }
        if(!(Normal == right.Normal)){
            return false;
        }
        if(!(TexCoords == right.TexCoords)){
            return false;
        }
        return true;
    }
};

class VertexBuffer{
private:
    unsigned int mRendererID;
    unsigned int mSize;
    unsigned int mLength;
public:
    VertexBuffer();
    ~VertexBuffer();
    void Init(const std::vector<Vertex>& vertices);
    unsigned int GetSize();
    unsigned int GetCount();
    unsigned int GetID();
    void Bind();
    void Unbind();
    static std::vector<Vertex> FormatVertexData(const float data[], unsigned int size);
    static std::vector<unsigned int> CreateIndexedData(std::vector<Vertex>& vertices);
    static void PrintVertices(std::vector<Vertex>& vertices);
};

