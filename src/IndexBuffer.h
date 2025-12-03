#pragma once

#include <vector>

class IndexBuffer{

private:
    unsigned int mRendererID;
    unsigned int mCount;
public:
    IndexBuffer();
    ~IndexBuffer();
    void Init(const std::vector<unsigned int>& indices);
    unsigned int GetCount() const;
    void Bind() const;
    void Unbind() const;
    unsigned int GetID() const {return  mRendererID;}
    static void PrintIndices(std::vector<unsigned int>& indices);
};
