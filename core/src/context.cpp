#include "core/context.h"

#include <GLFW/glfw3.h>

#include "core/initialization.h"

CContext::~CContext()
{
    glfwTerminate();
}

GLenum CContext::Create()
{
    GLenum result = 1;

    result = glfwInit();
    if(result == GLFW_TRUE) {
        GLFWwindow* window = glfwCreateWindow(640, 480, "", nullptr, nullptr);
        if(window != nullptr) {

            glfwMakeContextCurrent(window);

            core::Init(window);

            result = 0;
        }
    }

    return result;
}

GLvoid CContext::GetFramebufferSize(GLvoid* window)
{
    int width = 0;
    int height = 0;
    GLFWwindow* obj = nullptr;

    obj = static_cast<GLFWwindow*>(window);
    if(obj != nullptr) {
        glfwGetFramebufferSize(obj, &width, &height);
    }
}