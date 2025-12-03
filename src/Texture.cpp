#include <GL/glew.h>
#include "Texture.h"
#include "iostream"

Texture::Texture() {
    glGenTextures(1, &mRendererID);
}

Texture::~Texture() {
    std::cout << "TEX DESTRUCTOR CALLED" << std::endl;
    glDeleteTextures(1,&mRendererID);
}

void Texture::Init(std::string& path, unsigned int index) {
    int format = (path.find(".png") != std::string::npos) ? GL_RGBA : GL_RGB;
    mIndex = index;
    glBindTexture(GL_TEXTURE_2D, mRendererID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path.c_str(), &mWidth, &mHeight, &mNrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    std::cout << "Texture Loaded" << std::endl;

}

void Texture::Bind() {
    glActiveTexture(GL_TEXTURE0 + mIndex);
    glBindTexture(GL_TEXTURE_2D, mRendererID);
}

void Texture::Unbind(){
    glActiveTexture(GL_TEXTURE0 + mIndex);
    glBindTexture(GL_TEXTURE_2D, 0);
}


