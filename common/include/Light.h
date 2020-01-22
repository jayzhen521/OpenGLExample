#pragma once

#include <string>
#include <glm/vec3.hpp>

class BaseLight
{
public:
    std::string Name;
    glm::vec3 Color;
    float AmbientIntensity;
    float DiffuseIntensity;

    BaseLight()
    {
        Color = glm::vec3(0.0f, 0.0f, 0.0f);
        AmbientIntensity = 0.0f;
        DiffuseIntensity = 0.0f;
    }
};


class DirectionalLight : public BaseLight
{
public:
    glm::vec3 Direction;

    DirectionalLight()
    {
        Direction = glm::vec3(0.0f, 0.0f, 0.0f);
    }
};


struct LightAttenuation
{
    float Constant;
    float Linear;
    float Exp;

    LightAttenuation()
    {
        Constant = 1.0f;
        Linear = 0.0f;
        Exp = 0.0f;
    }
};


class PointLight : public BaseLight
{
public:
    glm::vec3 Position;
    LightAttenuation Attenuation;

    PointLight()
    {
        Position = glm::vec3(0.0f, 0.0f, 0.0f);
    }
};


class SpotLight : public PointLight
{
public:
    glm::vec3 Direction;
    float Cutoff;

    SpotLight()
    {
        Direction = glm::vec3(0.0f, 0.0f, 0.0f);
        Cutoff = 0.0f;
    }
};