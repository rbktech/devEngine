#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <iostream>

#include <core/mash.h>
#include <core/resources.h>

#include <core/object/ebo.h>
#include <core/object/vao.h>
#include <core/object/bitmap.h>
#include <core/object/buffer.h>
#include <core/object/draw.h>
#include <core/object/shader.h>
#include <core/object/texture.h>

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

class CProcess
{
private:
    CResource RSV;
    CResource RSF;
    CResource imgBrick;

    core::CMash* mShader = nullptr;
    core::CMash* mObject = nullptr;

    TBMPHeader* bmp = nullptr;

    GLuint m_vao = 0;
    GLuint m_texture = 0;

public:
    void ReleaseGL()
    {
        delete mShader;
        delete mObject;
    }

    void InitializeGL()
    {
        GLenum result = 0;

        result = imgBrick.Load(RESOURCES "textures/brick_a.bmp");
        if(result != 0)
            throw std::runtime_error("error: to load texture: " + imgBrick.GetPathFile());

        result = RSV.Load(RESOURCES "shaders/pos3tex2.vert");
        if(result != 0)
            throw std::runtime_error("error: to load shader: " + RSV.GetPathFile());

        result = RSF.Load(RESOURCES "shaders/pos3tex2.frag");
        if(result != 0)
            throw std::runtime_error("error: to load shader: " + RSF.GetPathFile());

        bmp = imgBrick.GetRaw<TBMPHeader>();
        if(bmp == nullptr)
            throw std::runtime_error("error: bring bmp");

        mShader = new core::CMash();
        mShader->Set<core::CShaderProgram>(core::Shader, RSV.GetRaw<GLchar>(), RSV.GetSize(), GL_VERTEX_SHADER);
        mShader->Set<core::CShaderProgram>(core::Shader, RSF.GetRaw<GLchar>(), RSF.GetSize(), GL_FRAGMENT_SHADER);
        mShader->Apply();

        GLfloat v0[] = {
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top right
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
            0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
        };

        GLuint i0[] = { 0, 1, 2 };

        mObject = new core::CMash();
        mObject->Set<core::CDrawElements>(core::Elements, GL_TRIANGLES, 3);
        mObject->Set<core::CVAO>(core::VAO);
        mObject->Set<core::CBuffer>(core::Buffer, v0, sizeof(v0) / sizeof(v0[0]), &core::xyzrgbst);
        mObject->Set<core::CEBO>(core::EBO, i0, sizeof(i0) / sizeof(i0[0]));
        mObject->Set<core::CTexture>(core::Texture, imgBrick.GetRaw<GLchar>(), imgBrick.GetSize(), bmp->Width, bmp->Height, bmp->DataOffset, bmp->Bits_Per_Pixel);
        mObject->Apply();

        float v1[] = {
            // positions
            0.5f, 0.5f, 0.0f,   //
            0.5f, -0.5f, 0.0f,  //
            -0.5f, -0.5f, 0.0f, //
            -0.5f, 0.5f, 0.0f   //
        };

        float t1[] = {
            // texture coords
            1.0f, 1.0f, // top right
            1.0f, 0.0f, // bottom right
            0.0f, 0.0f, // bottom left
            0.0f, 1.0f  // top left
        };

        GLuint vbo;
        GLuint tbo;
        GLuint ebo;

        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &tbo);
        glGenBuffers(1, &ebo);
        glGenTextures(1, &m_texture);

        glBindTexture(GL_TEXTURE_2D, m_texture);
        if(bmp->Bits_Per_Pixel == 32)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bmp->Width, bmp->Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, imgBrick.GetRaw<signed char>() + bmp->DataOffset);
        else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp->Width, bmp->Height, 0, GL_BGR, GL_UNSIGNED_BYTE, imgBrick.GetRaw<signed char>() + bmp->DataOffset);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);

        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(v1), v1, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, tbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(t1), t1, GL_STATIC_DRAW);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(1);

        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    };

    void PaintGL()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        mShader->Draw();

        glBindTexture(GL_TEXTURE_2D, m_texture);

        glBindVertexArray(m_vao);

        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        mObject->Draw();
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

            glfwMakeContextCurrent(window);

            // make sure the viewport matches the new window dimensions;
            // note that width and height will be significantly larger than specified on retina displays.
            glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int w, int h) { CProcess::ResizeGL(w, h); });

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