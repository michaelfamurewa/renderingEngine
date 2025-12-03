#pragma once
#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Shader.h"

class Renderer{
public:
    void DrawByIndex(VertexBuffer& vb, IndexBuffer& ib);
    void DrawByVertex(VertexBuffer &vb, Shader& s);
    void Clear() const;
};


