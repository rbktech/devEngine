#include "core/initialization.h"

#include <GL/glew.h>

#include <stdexcept>

#include "core/error.h"

namespace core
{
    // glew: load all OpenGL function pointers
    GLvoid Init(GLvoid* context, const int& experimental)
    {
        glewExperimental =
            experimental; // GLEW будет использовать современный подход к извлечению указателей функций и расширений.

        GLenum result = glewInit();
        if(result != GLEW_OK) {

            const GLubyte* error = glewGetErrorString(result);

            throw std::runtime_error(std::string("GLEW Error: ") + reinterpret_cast<const char*>(error));
        }
    }

    GLvoid Version()
    {
        const GLubyte* version = nullptr;
        const GLubyte* renderer = nullptr;

        version = glGetString(GL_VERSION);
        renderer = glGetString(GL_RENDERER);

        std::cout << version << std::endl;
        std::cout << renderer << std::endl;
    }

    GLvoid Version(int& major, int& minor)
    {
        e(glGetIntegerv(GL_MAJOR_VERSION, &major));
        e(glGetIntegerv(GL_MINOR_VERSION, &minor));
    }

    GLvoid MaxVertexAttribs()
    {
        GLint maxVertexAttribs;

        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);

        std::cout << "Max Vertex Attribs: " << maxVertexAttribs << std::endl;
    }

    GLvoid Mode(const GLuint& mode)
    {
        const GLuint polygonMode = GL_POINT | mode % core::COUNT;

        if(polygonMode == GL_FILL)
            glEnable(GL_DEPTH_TEST);
        else
            glDisable(GL_DEPTH_TEST);

        e(glPolygonMode(GL_FRONT_AND_BACK, polygonMode));
    }

    const GLchar* IsMode(const GLuint& mode)
    {
        switch(mode) {
            case GL_POINT: {
                return "GL_POINT";
            }
            case GL_LINE: {
                return "GL_LINE";
            }
            case GL_FILL: {
                return "GL_FILL";
            }
            default: {
                return "GL_UNKNOWN";
            }
        }
    }
}