#include "VertexArray.h"
#include <iostream>
#include <GL/glew.h>

VertexArray::VertexArray() {
    std::cout << "VAO CONSTRUCTOR CALLED!" << "\n";
    glGenVertexArrays(1, &mRendererID);
}

VertexArray::~VertexArray() {
    std::cout << "VAO DESTRUCTOR CALLED!" << "\n";
    glDeleteVertexArrays(1, &mRendererID);
}

void VertexArray::Bind() {
    glBindVertexArray(mRendererID);
}

void VertexArray::Unbind() {
    glBindVertexArray(0);
}
