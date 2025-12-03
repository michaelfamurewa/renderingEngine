#include "IndexBuffer.h"
#include "Renderer.h"
#include <cstdio>


IndexBuffer::IndexBuffer() {
    glGenBuffers(1, &mRendererID);
    printf("ASSIGNED IBO ID: %d\n", mRendererID);
}

void IndexBuffer::Init(const std::vector<unsigned int>& indices) {
    mCount = indices.size();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mCount * sizeof(float), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer() {
    std::cout << "IBO DESTRUCTOR CALLED!" << "\n";
    glDeleteBuffers(1, &mRendererID);
}

unsigned int IndexBuffer::GetCount() const{
    return mCount;
}

void IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
}

void IndexBuffer::Unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::PrintIndices(std::vector<unsigned int> &indices) {
    int length = indices.size();
    printf("Indices: {");
    for(unsigned int i = 0; i < length; i++){
        if(i == length - 1){
            printf("%d}\n", indices[i]);
            break;
        }
        printf("%d, ", indices[i]);
    }
}

