#pragma once

#include "type.h"

namespace core
{
    enum {
        FILL,
        POINT,
        LINE,
        COUNT
    };

    GLvoid Init(GLvoid* context, const int& experimental = 1); // GL_TRUE 1

    /**
     * @brief Инкрементирует режим
     * @param mode 0, 1, 2
     * 0 - GL_POINT 0x1B00
     * 1 - GL_LINE 0x1B01
     * 2 - GL_FILL 0x1B02
     * Просто добавьте счетчик mode++
     * @return
     */
    GLvoid Mode(const GLuint& mode);

    GLvoid Version();

    const GLchar* IsMode(const GLuint& mode);
}