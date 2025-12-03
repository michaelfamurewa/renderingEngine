#include "Light.h"

Light::Light() {
    mColor = glm::vec3(1.0f);
    mDiffuse = mColor * glm::vec3(1.0f);
    mAmbient = mDiffuse * glm::vec3(0.2f);
    mSpecular = glm::vec3(1.0f);
}

glm::vec3 Light::GetAmbient() {
    return mAmbient;
}

glm::vec3 Light::GetDiffuse() {
    return mDiffuse;
}

glm::vec3 Light::GetSpecular() {
    return mSpecular;
}

Light::Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
    mAmbient = ambient;
    mDiffuse = diffuse;
    mSpecular = specular;
}

void Light::SetLightColor(glm::vec3 col) {
    mColor = col;
    mDiffuse = mColor * glm::vec3(1.0f);
    mAmbient = mDiffuse * glm::vec3(0.2f);
    mSpecular = glm::vec3(1.0f);
}

void Light::SetAmbient(glm::vec3 col) {
    mAmbient = col;
}

void Light::SetDiffuse(glm::vec3 col) {
    mDiffuse = col;
}

void Light::SetSpecular(glm::vec3 col) {
    mSpecular = col;
}

PointLight::PointLight() {
    mConstant = 1.0f;
    mLinear = 0.09f;
    mQuadratic = 0.032f;
}

PointLight::PointLight(float constant, float linear, float quadratic) {
    mConstant = constant;
    mLinear = linear;
    mQuadratic = quadratic;
}

SpotLight::SpotLight() {
    mCutOff = 12.5f;
    mOuterCutOff = 17.5f;
}

SpotLight::SpotLight(float cutOff, float outerCutOff) {
    mCutOff = cutOff;
    mOuterCutOff = outerCutOff;
}
