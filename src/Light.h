#pragma once
#include "Mesh.h"

class Light : public Mesh{
protected:
    glm::vec3 mAmbient;
    glm::vec3 mDiffuse;
    glm::vec3 mSpecular;
    glm::vec3 mDirection;
public:
    Light();
    Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
    glm::vec3 GetAmbient();
    glm::vec3 GetDiffuse();
    glm::vec3 GetSpecular();
    void SetAmbient(glm::vec3 col);
    void SetDiffuse(glm::vec3 col);
    void SetSpecular(glm::vec3 col);
    void SetLightColor(glm::vec3 col);
};

class PointLight : public Light{
protected:
    float mConstant;
    float mLinear;
    float mQuadratic;
public:
    PointLight();
    PointLight(float constant, float linear, float quadratic);
    float GetConstant() const {return mConstant;}
    float GetLinear() const {return mLinear;}
    float GetQuadratic() const {return mQuadratic;}
};

class SpotLight : public PointLight{
private:
    float mCutOff;
    float mOuterCutOff;
public:
    SpotLight();
    SpotLight(float cutOff, float outerCutOff);
    float GetCutOff() const {return mCutOff;}
    float GetOuterCutOff() const {return mOuterCutOff;}
};
