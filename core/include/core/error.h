#pragma once

#include <iostream>

#include "core/type.h"

class error
{
public:
    error() = default;
    ~error() = default;

    static const char* get(GLenum errorCode);
};

#define e(X)                                                              \
    X;                                                                    \
    {                                                                     \
        GLenum errorCode = glGetError();                                  \
        if(errorCode != GL_NO_ERROR)                                      \
            std::cout << error::get(errorCode) << " " << #X << std::endl; \
    }
