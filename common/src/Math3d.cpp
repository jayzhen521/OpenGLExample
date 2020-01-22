#pragma once

#include "Math3d.h"

PersProjInfo::PersProjInfo(
    float fov,
    float width,
    float height,
    float zNear,
    float zFar)
    :fov(fov),
    width(width),
    height(height),
    zNear(zNear),
    zFar(zFar)
{}