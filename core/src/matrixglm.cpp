#include "core/matrixglm.h"

#include <iostream>

// #define MEASURE 0.000000001
#define MEASURE 0.0001

namespace core
{
    GLfloat p(const GLfloat& value)
    {
        if(value > -MEASURE && value < MEASURE)
            return 0.0f;
        return value;
    }

    GLvoid print(const GLfloat& value, const GLchar* tag)
    {
        if(tag != nullptr)
            std::cout << tag << ": ";

        std::cout << p(value) << std::endl;
    }

    GLvoid print(const glm::mat4& m, const GLchar* tag)
    {
        if(tag != nullptr)
            std::cout << tag << ":" << std::endl;

        try {

            // [col][row]

            std::cout << p(m[0][0]) << " ";
            std::cout << p(m[1][0]) << " ";
            std::cout << p(m[2][0]) << " ";
            std::cout << p(m[3][0]) << " ";

            std::cout << std::endl;

            std::cout << p(m[0][1]) << " ";
            std::cout << p(m[1][1]) << " ";
            std::cout << p(m[2][1]) << " ";
            std::cout << p(m[3][1]) << " ";

            std::cout << std::endl;

            std::cout << p(m[0][2]) << " ";
            std::cout << p(m[1][2]) << " ";
            std::cout << p(m[2][2]) << " ";
            std::cout << p(m[3][2]) << " ";

            std::cout << std::endl;

            std::cout << p(m[0][3]) << " ";
            std::cout << p(m[1][3]) << " ";
            std::cout << p(m[2][3]) << " ";
            std::cout << p(m[3][3]) << " ";

            std::cout << std::endl;

            /*for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 4; j++) {
                    std::cout << m[j][i] << " ";
                }
                std::cout << std::endl;
            }*/
        } catch(...) {
            std::cout << "error print matrix" << std::endl;
        }
        // std::cout << "-------" << std::endl;
    }

    GLvoid print(const glm::vec2& v, const GLchar* tag)
    {
        v.x; v.y;

        if(tag != nullptr)
            std::cout << tag << ": ";

        try {
            for(int i = 0; i < 2; i++) {
                std::cout << p(v[i]) << " ";
            }
            std::cout << std::endl;
        } catch(...) {
            std::cout << "error print vector" << std::endl;
        }
        // std::cout << "-------" << std::endl;
    }

    GLvoid print(const glm::vec3& v, const GLchar* tag)
    {
        v.x; v.y; v.z;

        if(tag != nullptr)
            std::cout << tag << ": ";

        try {
            for(int i = 0; i < 3; i++) {
                std::cout << p(v[i]) << " ";
            }
            std::cout << std::endl;
        } catch(...) {
            std::cout << "error print vector" << std::endl;
        }
        // std::cout << "-------" << std::endl;
    }

    GLvoid print(const glm::vec4& v, const GLchar* tag)
    {
        v.x; v.y; v.z; v.w;

        if(tag != nullptr)
            std::cout << tag << ": ";

        try {
            for(int i = 0; i < 4; i++) {
                std::cout << p(v[i]) << " ";
            }
            std::cout << std::endl;
        } catch(...) {
            std::cout << "error print vector" << std::endl;
        }
        // std::cout << "-------" << std::endl;
    }
}