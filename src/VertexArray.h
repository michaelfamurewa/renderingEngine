#pragma once

class VertexArray {
private:
    unsigned int mRendererID;
public:
    VertexArray();
    ~VertexArray();
    void Bind();
    void Unbind();
};
