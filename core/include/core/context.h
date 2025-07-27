#pragma once

#include "type.h"

class CContext
{
public:
    CContext() = default;
    ~CContext();

    GLenum Create();

    GLvoid GetFramebufferSize(GLvoid* window);
};