#include <iostream>
#include "VertexBuffer.h"
#include <cstdio>
#include "unordered_map"

VertexBuffer::VertexBuffer() {
    glGenBuffers(1, &mRendererID);
    std::cout << "VBO constructor called" << "\n";
    printf("ASSIGNED VBO ID: %d\n", mRendererID);
}

VertexBuffer::~VertexBuffer() {
    std::cout << "VBO DESTRUCTOR CALLED!" << "\n";
    glDeleteBuffers(1, &mRendererID);
}

void VertexBuffer::Init(const std::vector<Vertex>& vertices) {
    mLength = vertices.size();
    mSize = sizeof(Vertex) * mLength;
    glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
    glBufferData(GL_ARRAY_BUFFER, mSize, vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    std::cout << "VBO INIT called" << "\n";
}

void VertexBuffer::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
}

void VertexBuffer::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int VertexBuffer::GetCount() {
    return mLength;
}

unsigned int VertexBuffer::GetSize() {
    return mSize;
}

std::vector<Vertex> VertexBuffer::FormatVertexData(const float data[], unsigned int size) {
    std::vector<Vertex> vertexVec;
    unsigned int vertexCount = size / (sizeof(float) * 8);
    unsigned int vertexIndex = 0;

    Vertex currentVertex;
    unsigned int pos = 0, nor = 3, tex = 6;
    while(vertexIndex < vertexCount){
        currentVertex.Position.x = data[pos];
        currentVertex.Position.y = data[pos + 1];
        currentVertex.Position.z = data[pos + 2];
        pos += 8;

        currentVertex.Normal.x = data[nor];
        currentVertex.Normal.y = data[nor + 1];
        currentVertex.Normal.z = data[nor + 2];
        nor += 8;

        currentVertex.TexCoords.x = data[tex];
        currentVertex.TexCoords.y = data[tex + 1];
        tex += 8;

        vertexVec.emplace_back(currentVertex);
        vertexIndex += 1;
    }
    return vertexVec;
}

std::vector<unsigned int> VertexBuffer::CreateIndexedData(std::vector<Vertex> &vertices) {

    struct usedVertex{
        Vertex vertex;
        unsigned int index;
    };

    std::vector<unsigned int> indices;
    std::vector<usedVertex> dupes;
    std::vector<Vertex> updatedVertices;

    for(Vertex vertex : vertices){

        bool dupeFound = false;

        for(usedVertex dupe : dupes){
            if(vertex == dupe.vertex){
                indices.emplace_back(dupe.index);
                dupeFound = true;
                break;
            }
        }

        if(!dupeFound){
            usedVertex val = {vertex, (unsigned int)dupes.size()};
            dupes.emplace_back(val);
            indices.emplace_back(updatedVertices.size());
            updatedVertices.emplace_back(val.vertex);
        }
    }
    vertices = updatedVertices;
    return indices;
}

void VertexBuffer::PrintVertices(std::vector<Vertex> &vertices) {
    std::cout << "PRINT VERTICES START: ################" << "\n";
    unsigned int i =0;
    for(Vertex vertex : vertices){
        std::cout << "[" << i << "] Position: {" << vertex.Position.x << ", " << vertex.Position.y << ", " << vertex.Position.z << "}, ";
        std::cout << "Normal: {" << vertex.Normal.x << ", " << vertex.Normal.y << ", " << vertex.Normal.z << "}, ";
        std::cout << "TexCoords: {" << vertex.TexCoords.x << ", " << vertex.TexCoords.y << "}\n";
        i += 1;
    }
    std::cout << "PRINT VERTICES END: ################" << "\n\n";
}

unsigned int VertexBuffer::GetID() {
    return mRendererID;
}
