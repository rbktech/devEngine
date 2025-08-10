#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <string>
#include <thread>

#include "core/object/ebo.h"
#include <core/object/vao.h>

#include <core/error.h>
#include <core/initialization.h>
#include <core/object/buffer.h>
#include <core/object/draw.h>
#include <core/mash.h>
#include <core/object/shader.h>
#include <core/resources.h>
#include <core/variable.h>


#define SRC_WIDTH 800
#define SRC_HEIGHT 600

class CGLProcess
{
private:
    CResource RB;
    CResource RI;
    CResource RSV;
    CResource RSF;

    core::CMash* pMashRectangle = nullptr;

public:
    void ReleaseGL()
    {
        delete pMashRectangle;
    }

    void InitializeGL()
    {
        GLenum result = 0;

        result = RSV.Load(RESOURCES "shaders/color.vert");
        if(result != 0)
            throw std::runtime_error("error: to load shader: " + RSV.GetPathFile());

        result = RSF.Load(RESOURCES "shaders/color.frag");
        if(result != 0)
            throw std::runtime_error("error: to load shader: " + RSF.GetPathFile());

        result = RB.Load(RESOURCES "vertex/rectangle.xyrgb", 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + RB.GetPathFile());

        result = RI.Load(RESOURCES "vertex/rectangle.index", 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + RI.GetPathFile());

        pMashRectangle = new core::CMash();
        pMashRectangle->Set<core::CVAO>(core::VAO);
        pMashRectangle->Set<core::CBuffer>(core::Buffer, RB.GetData<GLfloat>(), RB.GetCount(), &core::xyrgb);
        pMashRectangle->Set<core::CEBO>(core::EBO, RI.GetData<GLuint>(), RI.GetCount());
        pMashRectangle->Set<core::CDrawElements>(core::Elements, GL_TRIANGLE_FAN, RI.GetCount());
        pMashRectangle->Set<core::CShaderProgram>(core::Shader, RSV.GetRaw<GLchar>(), RSV.GetSize(), GL_VERTEX_SHADER);
        pMashRectangle->Set<core::CShaderProgram>(core::Shader, RSF.GetRaw<GLchar>(), RSF.GetSize(), GL_FRAGMENT_SHADER);
        pMashRectangle->Apply();
    }

    void PaintGL()
    {
        // DrawScene();
        // e(glEnable(GL_DEPTH_TEST));
        e(glClearColor(0.7, 0.5, 0.3, 1.0f));
        e(glClear(GL_COLOR_BUFFER_BIT));

        // SettingView

        // DrawCamera();

        // DrawObject();

        if(pMashRectangle != nullptr)
            pMashRectangle->Draw();
    }

    static void ModeGL(const uint16_t& mode)
    {
        core::Mode(mode);
    }
};

int main(int argc, char** argv)
{
    CGLProcess process;
    GLenum result = 0;
    GLFWwindow* window = nullptr;
    static uint16_t mode = 0;

    std::string title = "Example GLFW + OpenGL 3.3" + std::string(VERSION);

    result = glfwInit();
    if(result == GLFW_TRUE) {

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // Окно не изменяет размер

        window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, title.data(), nullptr, nullptr);
        if(window != nullptr) {

            glfwMakeContextCurrent(window);

            // make sure the viewport matches the new window dimensions;
            // note that width and height will be significantly larger than specified on retina displays.
            glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
                if(key == GLFW_KEY_F4 && action == GLFW_PRESS) {
                    CGLProcess::ModeGL(mode++);
                }
            });

            core::Init(window, false);

            e(glViewport(0, 0, SRC_WIDTH, SRC_HEIGHT));

            const GLubyte* version = glGetString(GL_VERSION);
            const GLubyte* renderer = glGetString(GL_RENDERER);

            std::cout << version << std::endl;
            std::cout << renderer << std::endl;

            // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            process.InitializeGL();

            while(!glfwWindowShouldClose(window)) {

                process.PaintGL();

                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                glfwSwapBuffers(window);
                glfwPollEvents();
            }

            process.ReleaseGL();

            glfwTerminate();
        } else
            std::cout << "error: create GLFW window" << std::endl;
    } else
        std::cout << "error: GLFW initialize" << std::endl;

    return 0;
}