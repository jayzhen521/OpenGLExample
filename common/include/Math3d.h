#pragma once

#include "Config.h"

class PersProjInfo
{
public:
    PersProjInfo(
        float fov = 30.0f / 180.0f * PI,
        float width = WINDOW_WIDTH,
        float height = WINDOW_HEIGHT,
        float zNear = 1.0f,
        float zFar = 100.0f);

    float fov;
    float width;
    float height;
    float zNear;
    float zFar;
};