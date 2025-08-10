#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <iostream>

#include <core/mash.h>
#include <core/resources.h>

#include "core/object/cbo.h"
#include "core/object/vbo.h"
#include <core/object/matrix.h>
#include <core/object/translate.h>
#include <core/object/ebo.h>
#include <core/object/vao.h>
#include <core/object/bitmap.h>
#include <core/object/buffer.h>
#include <core/object/draw.h>
#include <core/object/rotate.h>
#include <core/object/orthographic.h>
#include <core/object/scale.h>
#include <core/object/shader.h>
#include <core/object/texture.h>

#include <core/error.h>

#define SCR_WIDTH 800.0f
#define SCR_HEIGHT 600.0f

GLfloat RV1[] {
    100.0f, 100.0f, 0.0f, //
    200.0f, 100.0f, 0.0f, //
    100.0f, 200.0f, 0.0f, //
    200.0f, 200.0f, 0.0f  //
};

class CProcess
{
private:
    core::CMash* mRect = nullptr;
    core::CMash* mObject = nullptr;
    core::CMash* mShader0 = nullptr;
    core::CMash* mShader1 = nullptr;

    CResource RIM0;
    CResource RV0;
    CResource RI0;
    CResource RSV;
    CResource RSF;

    TBMPHeader* bmp = nullptr;

public:
    void ReleaseGL()
    {
        delete mRect;
        delete mObject;
        delete mShader0;
        delete mShader1;
    }

    void InitializeGL()
    {
        GLenum result = 0;

        result = RIM0.Load(RESOURCES "textures/wall_a.bmp");
        if(result != 0)
            throw std::runtime_error("error: to load texture: " + RIM0.GetPathFile());

        result = RSV.Load(RESOURCES "shaders/pos3col3tex2.vert");
        if(result != 0)
            throw std::runtime_error("error: to load shader: " + RSV.GetPathFile());

        result = RSF.Load(RESOURCES "shaders/pos3col3tex2.frag");
        if(result != 0)
            throw std::runtime_error("error: to load shader: " + RSF.GetPathFile());

        result = RV0.Load(RESOURCES "vertex/rect.xyzrgbst", 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + RV0.GetPathFile());

        result = RI0.Load(RESOURCES "vertex/rect.index", 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + RI0.GetPathFile());

        mShader0 = new core::CMash();
        mShader0->Set<core::CShaderProgram>(core::Shader, RSV.GetRaw<GLchar>(), RSV.GetSize(), GL_VERTEX_SHADER);
        mShader0->Set<core::CShaderProgram>(core::Shader, RSF.GetRaw<GLchar>(), RSF.GetSize(), GL_FRAGMENT_SHADER);
        mShader0->Set<core::COrthographic>(core::Orthographic, 0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
        mShader0->Apply();

        result = RSV.Load(RESOURCES "shaders/pos3.vert");
        if(result != 0)
            throw std::runtime_error("error: to load shader: " + RSV.GetPathFile());

        mShader1 = new core::CMash();
        mShader1->Set<core::CShaderProgram>(core::Shader, RSV.GetRaw<GLchar>(), RSV.GetSize(), GL_VERTEX_SHADER);
        mShader1->Set<core::COrthographic>(core::Orthographic, 0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
        mShader1->Apply();

        bmp = RIM0.GetRaw<TBMPHeader>();
        if(bmp == nullptr)
            throw std::runtime_error("error: bring bmp");

        mRect = new core::CMash();
        mRect->Set<core::CVAO>(core::VAO);
        mRect->Set<core::CDrawElements>(core::Elements, GL_TRIANGLES, RI0.GetSize());
        mRect->Set<core::CBuffer>(core::Buffer, RV0.GetData<GLfloat>(), RV0.GetCount(), &core::xyzrgbst);
        mRect->Set<core::CEBO>(core::EBO, RI0.GetData<GLuint>(), RI0.GetCount());
        mRect->Set<core::CTexture>(core::Texture, RIM0.GetRaw<GLfloat>(), RIM0.GetSize(), bmp->Width, bmp->Height,
            bmp->DataOffset, bmp->Bits_Per_Pixel);
        // mRect->Set<core::CShaderProgram>(core::Shader, mShader0->Get<core::CShaderProgram>(core::Shader));
        mRect->Set(mShader0);
        mRect->Apply();

        mObject = new core::CMash();
        mObject->Set<core::CVAO>(core::VAO);
        mObject->Set<core::CDrawArrays>(core::Array, GL_LINE_LOOP, 0, sizeof(RV1) / sizeof(RV1[0]) / 3);
        mObject->Set<core::CBuffer>(core::Buffer, RV1, sizeof(RV1) / sizeof(RV1[0]), &core::xyz);
        // mObject->Set<core::CShaderProgram>(core::Shader, mShader1->Get<core::CShaderProgram>(core::Shader));
        mObject->Set(mShader1);
        mObject->Apply();

        // glEnable(GL_DEPTH_TEST);
        // glDisable(GL_DEPTH_TEST);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    };

    void PaintGL()
    {
        glClearColor(0.3f, 0.8f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /*glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);

        mShader0->Get<core::CShaderProgram>(core::Shader)->Use();
        mShader0->Get<core::CShaderProgram>(core::Shader)->Update("u_projection", glm::value_ptr(projection));

        mShader1->Get<core::CShaderProgram>(core::Shader)->Use();
        mShader1->Get<core::CShaderProgram>(core::Shader)->Update("u_projection", glm::value_ptr(projection));*/

        mRect->Draw();
        mObject->Draw();
    }

    void RefreshGL() // Change value
    {
        mRect->Set<core::COrthographic>(core::Orthographic, 0.0f, 800.0f / 2, 0.0f, 600.0f / 2, -1.0f, 1.0f);
        mRect->Update();

        mObject->Set<core::COrthographic>(core::Orthographic, 0.0f, 800.0f / 2, 0.0f, 600.0f / 2, -1.0f, 1.0f);
        mObject->Update();

        GLenum result = 0;
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

    std::string title = "Camera OpenGL Core";

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
            glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int w, int h) { CProcess::ResizeGL(w, h); });

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