#include "Renderer.h"

void Renderer::Clear() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::DrawByIndex(VertexBuffer& vb, IndexBuffer& ib) {
    vb.Bind();
    ib.Bind();
    glDrawElements(GL_TRIANGLES,ib.GetCount(),GL_UNSIGNED_INT, 0);
}

void Renderer::DrawByVertex(VertexBuffer &vb, Shader &s) {
    s.Bind();
    glDrawArrays(GL_TRIANGLES, 0, vb.GetCount());
}
