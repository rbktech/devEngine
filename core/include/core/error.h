#pragma once

#include <iostream>

#define e(X)                                                      \
        X;                                                        \
        {                                                         \
            GLenum errorCode = glGetError();                      \
            if(errorCode != GL_NO_ERROR)                          \
                std::cout << errorCode << " " << #X << std::endl; \
        }
