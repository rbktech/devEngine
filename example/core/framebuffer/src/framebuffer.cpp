#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <thread>

#include <core/mash.h>
#include <core/resources.h>
#include <core/initialization.h>

#include "core/object/vao.h"
#include <core/object/fbo.h>
#include <core/object/rbo.h>
#include <core/object/shader.h>
#include <core/object/texture.h>
#include <core/object/bitmap.h>

#include <core/error.h>

#define SRC_WIDTH 800
#define SRC_HEIGHT 600

class CGLProcess
{
private:
    core::CMash* mFrameBuffer = nullptr;
    core::CMash* mRenderBuffer = nullptr;
    core::CMash* mVAO = nullptr;

    core::CMash* mShader = nullptr;

    core::CTexture* m_texture;
    core::CTexture* m_texture_frame_buffer;

    CResource RSV;
    CResource RSF;
    CResource RV;
    CResource RT;

    core::CRBO* rbo;
    core::CFBO* fbo;
    core::CVAO* vao;

    TBMPHeader* bmp = nullptr;

public:
    void ReleaseGL()
    {
    }

    void InitializeGL()
    {
        GLint result = 0;

        mFrameBuffer = new core::CMash();
        fbo = mFrameBuffer->Set<core::CFBO>(core::FBO);
        fbo->Bind();

        m_texture_frame_buffer = new core::CTexture();
        m_texture_frame_buffer->Bind();
        m_texture_frame_buffer->CreateBuffer(800, 600);
        m_texture_frame_buffer->ParamBase();
        m_texture_frame_buffer->UnBind();

        e(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture_frame_buffer->Get(), 0));

        mRenderBuffer = new core::CMash();
        rbo = mRenderBuffer->Set<core::CRBO>(core::RBO);
        rbo->Bind();
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 700, 500);
        rbo->UnBind();

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo->Get());

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

        fbo->UnBind();

        result = RSV.Load(RESOURCES "shaders/pos2tex2.vert");
        if(result != 0)
            throw std::runtime_error("error: to load shader: " + RSV.GetPathFile());

        result = RSF.Load(RESOURCES "shaders/pos2tex2.frag");
        if(result != 0)
            throw std::runtime_error("error: to load shader: " + RSF.GetPathFile());

        mShader = new core::CMash();
        mShader->Set<core::CShaderProgram>(core::Shader, RSV.GetRaw<GLchar>(), RSV.GetSize(), GL_VERTEX_SHADER);
        mShader->Set<core::CShaderProgram>(core::Shader, RSF.GetRaw<GLchar>(), RSF.GetSize(), GL_FRAGMENT_SHADER);
        mShader->Apply();

        result = RV.Load(RESOURCES "vertex/quad.xyst", 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + RV.GetPathFile());

        mVAO = new core::CMash();
        vao = mVAO->Set<core::CVAO>(core::VAO);
        mVAO->Set<core::CBuffer>(core::Buffer, RV.GetData<GLfloat>(), RV.GetCount(), &core::xyst);
        mVAO->Apply();

        result = RT.Load(RESOURCES "textures/test.bmp");
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + RT.GetPathFile());

        bmp = RT.GetRaw<TBMPHeader>();

        m_texture = new core::CTexture();
        m_texture->Bind();
        m_texture->Create(RT.GetRaw<GLubyte>(), bmp->Width, bmp->Height, bmp->DataOffset, bmp->Bits_Per_Pixel);
        m_texture->ParamBase();
        m_texture->UnBind();
    }

    void PaintGL()
    {
        fbo->Bind();
        glClearColor(0.1f, 0.3f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // we're not using the stencil buffer now
        glEnable(GL_DEPTH_TEST);
        m_texture->Bind();
        // DrawScene();

        // second pass
        glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
        glClearColor(0.2f, 0.7f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        mShader->Draw();
        // shader->SetTexture("u_screen_texture", m_texture->Get());

        vao->Bind();
        glDisable(GL_DEPTH_TEST);
        m_texture_frame_buffer->Bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
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