#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/trigonometric.hpp>

#include <iostream>

#include <core/mash.h>
#include <core/resources.h>

#include "core/object/cbo.h"
#include "core/object/vbo.h"
#include <core/object/bitmap.h>
#include <core/object/buffer.h>
#include <core/object/draw.h>
#include <core/object/ebo.h>
#include <core/object/matrix.h>
#include <core/object/rotate.h>
#include <core/object/scale.h>
#include <core/object/shader.h>
#include <core/object/texture.h>
#include <core/object/translate.h>
#include <core/object/vao.h>

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

class CProcess
{
private:
    CResource R;
    CResource RV0;
    CResource RV1;
    CResource RC1;
    CResource RI1;
    CResource RV2;
    CResource RSV;
    CResource RSF;

    core::CMash* mRect = nullptr;
    core::CMash* mRhombus = nullptr;
    core::CMash* mTriangle = nullptr;
    core::CMash* mShader = nullptr;

public:
    void ReleaseGL()
    {
        delete mRect;
        delete mShader;
        delete mTriangle;
        delete mRhombus;
    }

    void InitializeGL()
    {
        GLenum result = 0;

        result = RSV.Load(RESOURCES "shaders/pos3.vert");
        if(result != 0)
            throw std::runtime_error("error: to load shader: " + RSV.GetPathFile());

        mShader = new core::CMash;
        mShader->Set<core::CShaderProgram>(core::Shader, RSV.GetRaw<GLchar>(), RSV.GetSize(), GL_VERTEX_SHADER);
        mShader->Apply();

        result = RV0.Load(RESOURCES "vertex/rect.xyz", 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + RV0.GetPathFile());

        mRect = new core::CMash;
        mRect->Set<core::CVAO>(core::VAO);
        mRect->Set<core::CDrawArrays>(core::Array, GL_LINE_LOOP, 0, RV0.GetCount() / 3);
        mRect->Set<core::CMatrix>(core::Matrix);
        mRect->Set<core::CRotate>(core::Rotate);
        mRect->Set<core::CTranslate>(core::Translate);
        mRect->Set<core::CVBO>(core::VBO, RV0.GetData<GLfloat>(), RV0.GetCount());
        mRect->Apply();

        result = RV2.Load(RESOURCES "vertex/triangle.xyz", 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + RV2.GetPathFile());

        mTriangle = new core::CMash;
        mTriangle->Set<core::CVAO>(core::VAO);
        mTriangle->Set<core::CDrawArrays>(core::Array, GL_LINE_LOOP, 0, RV2.GetCount() / 3);
        mTriangle->Set<core::CMatrix>(core::Matrix);
        mTriangle->Set<core::CScale>(core::Scale);
        mTriangle->Set<core::CVBO>(core::VBO, RV2.GetData<GLfloat>(), RV2.GetCount());
        mTriangle->Set(mShader);
        mTriangle->Apply();

        result = RSV.Load(RESOURCES "shaders/pos3col3.vert");
        if(result != 0)
            throw std::runtime_error("error: to load shader: " + RSV.GetPathFile());

        result = RSF.Load(RESOURCES "shaders/pos3col3.frag");
        if(result != 0)
            throw std::runtime_error("error: to load shader: " + RSF.GetPathFile());

        result = RV1.Load(RESOURCES "vertex/rhombus.xyz", 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + RV1.GetPathFile());

        result = RC1.Load(RESOURCES "vertex/rhombus.rgb", 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + RC1.GetPathFile());

        result = RI1.Load(RESOURCES "vertex/rhombus.index", 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + RI1.GetPathFile());

        mRhombus = new core::CMash();
        mRhombus->Set<core::CVAO>(core::VAO);
        mRhombus->Set<core::CDrawElements>(core::Elements, GL_TRIANGLE_FAN, RI1.GetCount());
        mRhombus->Set<core::CMatrix>(core::Matrix);
        mRhombus->Set<core::CRotate>(core::Rotate);
        mRhombus->Set<core::CTranslate>(core::Translate);
        mRhombus->Set<core::CVBO>(core::VBO, RV1.GetData<GLfloat>(), RV1.GetCount());
        mRhombus->Set<core::CCBO>(core::CBO, RC1.GetData<GLfloat>(), RC1.GetCount());
        mRhombus->Set<core::CEBO>(core::EBO, RI1.GetData<GLfloat>(), RI1.GetCount());
        mRhombus->Set<core::CShaderProgram>(core::Shader, RSV.GetRaw<GLchar>(), RSV.GetSize(), GL_VERTEX_SHADER);
        mRhombus->Set<core::CShaderProgram>(core::Shader, RSF.GetRaw<GLchar>(), RSF.GetSize(), GL_FRAGMENT_SHADER);
        mRhombus->Apply();
    };

    void PaintGL()
    {
        glClearColor(0.2f, 0.8f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw
        mTriangle->Draw();

        mRhombus->Draw();

        mShader->Draw();
        mRect->Draw(mShader->Get<core::CShaderProgram>(core::Shader)->Get());

        // Change value
        mRhombus->Set<core::CMatrix>(core::Matrix);
        mRhombus->Set<core::CRotate>(core::Rotate, glm::degrees(glfwGetTime()), 0.0f, 0.0f, 1.0f);
        mRhombus->Set<core::CTranslate>(core::Translate, 0.5f, 0.5f, 0.0f);
        mRhombus->Update();

        mTriangle->Set<core::CMatrix>(core::Matrix);
        mTriangle->Set<core::CScale>(core::Scale, std::sin(glfwGetTime()));
        mTriangle->Update();
    }

    void RefreshGL() // Change value
    {
        GLenum result = 0;
        GLfloat* array = nullptr;

        result = RV2.Load(RESOURCES "vertex/triangle.xyz", 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + RV2.GetPathFile());

        mTriangle->Set<core::CVBO>(core::VBO, RV2.GetData<GLfloat>(), RV2.GetCount());
        mTriangle->Set<core::CScale>(core::Scale, -0.5f);

        mTriangle->Update();

        // ----

        result = RV0.Load(RESOURCES "vertex/rect.xyz", 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + RV0.GetPathFile());

        mRect->Set<core::CVBO>(core::VBO, RV0.GetData<GLfloat>(), RV0.GetCount());

        // ----

        mRect->Set<core::CMatrix>(core::Matrix);

        result = R.Load(RESOURCES "vertex/translate.xyz", 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + R.GetPathFile());

        array = R.GetData<GLfloat>();
        glm::vec3 position(array[0], array[1], array[2]);

        mRect->Set<core::CTranslate>(core::Translate, position.x, position.y, position.z);

        // ----

        result = R.Load(RESOURCES "vertex/rotate.dxyz", 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + R.GetPathFile());

        array = R.GetData<GLfloat>();
        GLfloat degrees = array[0];
        glm::vec3 rotate(array[1], array[2], array[3]);

        mRect->Set<core::CRotate>(core::Rotate, degrees, rotate.x, rotate.y, rotate.z);

        // ----

        mRect->Update();
    }

    static void ResizeGL(int width, int height)
    {
        glViewport(0, 0, width, height);
    }
};

// -----------------------------------------------------------------------

void glfwProcessInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    CProcess process;
    GLenum result = 0;
    GLFWwindow* window = nullptr;

    std::string title = "Load texture EBO OpenGL 3.3";

    result = glfwInit();
    if(result == GLFW_TRUE) {

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, title.data(), nullptr, nullptr);
        if(window != nullptr) {

            glfwSetWindowUserPointer(window, &process);

            glfwMakeContextCurrent(window);

            // make sure the viewport matches the new window dimensions;
            // note that width and height will be significantly larger than specified on retina displays.
            glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int w, int h) {
                CProcess::ResizeGL(w, h); //
            });

            glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
                if(key == GLFW_KEY_R && action == GLFW_PRESS) {

                    CProcess* process = static_cast<CProcess*>(glfwGetWindowUserPointer(window));
                    if(process != nullptr)
                        process->RefreshGL();
                }
            });

            result = glewInit();
            if(result == GLEW_OK) {

                const GLubyte* version = glGetString(GL_VERSION);
                const GLubyte* renderer = glGetString(GL_RENDERER);

                std::cout << version << std::endl;
                std::cout << renderer << std::endl;

                process.InitializeGL();

                while(!glfwWindowShouldClose(window)) {

                    process.PaintGL();

                    glfwProcessInput(window);
                    glfwSwapBuffers(window);
                    glfwPollEvents();
                }

                process.ReleaseGL();
            } else
                std::cout << "error: GLEW initialize" << std::endl;
        } else
            std::cout << "Failed to create GLFW window" << std::endl;

        glfwTerminate();
    } else
        std::cout << "error: GLFW initialize" << std::endl;

    return 0;
}