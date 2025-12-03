#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>


struct ShaderProgramSource{
    std::string vertexSource;
    std::string fragmentSource;
};


class Shader{
private:
    std::string mFilepath;
    unsigned int mRendererID;
    std::unordered_map<std::string, int> uniformLocationCache;
public:
    Shader();
    void Init(std::string& filepath);
    ~Shader();
    void Bind() const;
    void Unbind() const;
    void SetUniform4f(std::string& name, float v0, float v1, float v2, float v3);
    void SetUniform3f(std::string &name, float v0, float v1, float v2);
    void SetUniform1i(std::string& name, int v0);
    void SetUniformMatrix4fv(std::string& name, int count, unsigned char transpose, float* v0);
    void SetUniform1f(std::string& name, float v0);

private:
    unsigned int GetUniformLocation(std::string& name);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    ShaderProgramSource ParseShader(std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);

};