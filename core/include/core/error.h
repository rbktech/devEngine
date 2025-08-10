#pragma once

#include <iostream>

class error
{
public:
    error() = default;
    ~error() = default;

    static const char* get(GLenum errorCode)
    {
        switch(errorCode) {
            case GL_INVALID_ENUM:
                return "GL_INVALID_ENUM";
            case GL_INVALID_VALUE:
                return "GL_INVALID_VALUE";
            case GL_INVALID_OPERATION:
                return "GL_INVALID_OPERATION";
            case GL_OUT_OF_MEMORY:
                return "GL_OUT_OF_MEMORY";
            default:
                return "GL_UNKNOWN";
        }
    }
};

#define e(X)                                                              \
    X;                                                                    \
    {                                                                     \
        GLenum errorCode = glGetError();                                  \
        if(errorCode != GL_NO_ERROR)                                      \
            std::cout << error::get(errorCode) << " " << #X << std::endl; \
    }
