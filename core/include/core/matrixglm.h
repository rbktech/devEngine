#pragma once

#include <glm/glm.hpp>

#include "type.h"

namespace core
{
    GLfloat p(const GLfloat& value);

    GLvoid print(const GLfloat& value, const GLchar* tag = nullptr);
    GLvoid print(const glm::mat4& m, const GLchar* tag = nullptr);
    GLvoid print(const glm::vec2& v, const GLchar* tag = nullptr);
    GLvoid print(const glm::vec3& v, const GLchar* tag = nullptr);
    GLvoid print(const glm::vec4& v, const GLchar* tag = nullptr);
}