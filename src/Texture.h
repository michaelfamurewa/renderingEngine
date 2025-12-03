#pragma once

#include "stb_image.h"
#include "string"

class Texture {
private:
    unsigned int mRendererID, mIndex;
    std::string mType;
    std::string mFilePath;
    int mWidth, mHeight, mNrChannels;
public:
    Texture();
    ~Texture();
    void Init(std::string& path, unsigned int index);
    void Bind();
    void Unbind();
};

