#include "initialization.h"

#include <GL/glew.h>

#include <stdexcept>

namespace core
{
    GLvoid Init()
    {
        GLenum result = glewInit();
        if(result != GLEW_OK) {

            const GLubyte* error = glewGetErrorString(result);

            throw std::runtime_error(std::string("GLEW Error: ") + reinterpret_cast<const char *>(error));
        }
    }
}