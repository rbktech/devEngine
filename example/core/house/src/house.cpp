#include <fstream>
#include <iostream>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <core/mash.h>
#include <core/resources.h>

#include <core/object/bitmap.h>
#include <core/object/ebo.h>
#include <core/object/vao.h>
#include <core/object/vbo.h>
#include <core/object/tbo.h>
#include <core/object/buffer.h>
#include <core/object/draw.h>
#include <core/object/shader.h>
#include <core/object/texture.h>

#define SCR_WIDTH 800
#define SCR_HEIGHT 800

class CProcess
{
private:
    CResource RV;
    CResource RI;
    CResource RT;
    CResource imgBrick;
    CResource imgRoof;
    CResource imgWindow;
    CResource imgTest;
    CResource RSV;
    CResource RSF;

    core::CMash* mMashRoof = nullptr;
    core::CMash* mMashFoundation = nullptr;
    core::CMash* mMashWindow = nullptr;
    core::CMash* mMashBrick = nullptr;
    core::CMash* mMashSquare = nullptr;

    core::CMash* mShaderRoof = nullptr;
    core::CMash* mShaderFoundation = nullptr;
    core::CMash* mShaderTexture = nullptr;

    std::shared_ptr<core::CTexture> mTextureWindow = nullptr;

    TBMPHeader* bmp = nullptr;

public:
    void ReleaseGL()
    {
        delete mMashRoof;
        delete mMashFoundation;
        delete mMashWindow;
        delete mMashBrick;
        delete mMashSquare;

        delete mShaderRoof;
        delete mShaderFoundation;
        delete mShaderTexture;

        mTextureWindow.reset();
    }

    void InitializeGL()
    {
        GLenum result = 0;

        result = RSV.Load(RESOURCES "shaders/roof.vert");
        if(result != 0)
            throw std::runtime_error("error: to load shader: " + RSV.GetPathFile());

        result = RSF.Load(RESOURCES "shaders/roof.frag");
        if(result != 0)
            throw std::runtime_error("error: to load shader: " + RSF.GetPathFile());

        mShaderRoof = new core::CMash();
        mShaderRoof->Set<core::CShaderProgram>(core::Shader, RSV.GetRaw<GLchar>(), RSV.GetSize(), GL_VERTEX_SHADER);
        mShaderRoof->Set<core::CShaderProgram>(core::Shader, RSF.GetRaw<GLchar>(), RSF.GetSize(), GL_FRAGMENT_SHADER);
        mShaderRoof->Apply();

        result = RSV.Load(RESOURCES "shaders/pos3tex2.vert");
        if(result != 0)
            throw std::runtime_error("error: to load shader: " + RSV.GetPathFile());

        result = RSF.Load(RESOURCES "shaders/pos3tex2.frag");
        if(result != 0)
            throw std::runtime_error("error: to load shader: " + RSF.GetPathFile());

        mShaderTexture = new core::CMash();
        mShaderTexture->Set<core::CShaderProgram>(core::Shader, RSV.GetRaw<GLchar>(), RSV.GetSize(), GL_VERTEX_SHADER);
        mShaderTexture->Set<core::CShaderProgram>(core::Shader, RSF.GetRaw<GLchar>(), RSF.GetSize(), GL_FRAGMENT_SHADER);
        mShaderTexture->Apply();

        // -------------------------------------------------------------------

        result = imgBrick.Load(RESOURCES "textures/brick.bmp");
        if(result != 0)
            throw std::runtime_error("error: to load texture: " + imgBrick.GetPathFile());

        result = imgRoof.Load(RESOURCES "textures/roof.bmp");
        if(result != 0)
            throw std::runtime_error("error: to load texture: " + imgRoof.GetPathFile());

        result = imgWindow.Load(RESOURCES "textures/window.bmp");
        if(result != 0)
            throw std::runtime_error("error: to load texture: " + imgWindow.GetPathFile());

        result = imgTest.Load(RESOURCES "textures/test.bmp");
        if(result != 0)
            throw std::runtime_error("error: to load texture: " + imgTest.GetPathFile());

        bmp = imgWindow.GetRaw<TBMPHeader>();
        if(bmp == nullptr)
            throw std::runtime_error("error: bring bmp");

        mTextureWindow = std::make_shared<core::CTexture>();
        mTextureWindow->Bind();
        mTextureWindow->Create(imgWindow.GetRaw<GLubyte>(), bmp->Width, bmp->Height, bmp->DataOffset, bmp->Bits_Per_Pixel);
        mTextureWindow->ParamBase();
        mTextureWindow->UnBind();

        // -------------------------------------------------------------------

        result = RV.Load(RESOURCES "vertex/roof.xyzrgb", 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + RV.GetPathFile());

        result = RI.Load(RESOURCES "vertex/roof.index", 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + RI.GetPathFile());

        bmp = imgRoof.GetRaw<TBMPHeader>();
        if(bmp == nullptr)
            throw std::runtime_error("error: bring bmp");

        mMashRoof = new core::CMash();
        mMashRoof->Set<core::CDrawElements>(core::Elements, GL_TRIANGLES, RI.GetCount());
        mMashRoof->Set<core::CBuffer>(core::Buffer, RV.GetData<GLfloat>(), RV.GetCount(), &core::xyzrgb);
        mMashRoof->Set<core::CEBO>(core::EBO, RI.GetData<GLuint>(), RI.GetCount());
        mMashRoof->Set<core::CVAO>(core::VAO);
        mMashRoof->Set<core::CTexture>(core::Texture, imgRoof.GetRaw<GLubyte>(), imgRoof.GetSize(), bmp->Width, bmp->Height, bmp->DataOffset, bmp->Bits_Per_Pixel);
        mMashRoof->Set<core::CShaderProgram>(core::Shader, RSV.GetRaw<GLchar>(), RSV.GetSize(), GL_VERTEX_SHADER);
        mMashRoof->Set<core::CShaderProgram>(core::Shader, RSF.GetRaw<GLchar>(), RSF.GetSize(), GL_FRAGMENT_SHADER);
        mMashRoof->Apply();

        // -------------------------------------------------------------------

        result = RSV.Load(RESOURCES "shaders/foundation.vert");
        if(result != 0)
            throw std::runtime_error("error: to load shader: " + RSV.GetPathFile());

        result = RSF.Load(RESOURCES "shaders/foundation.frag");
        if(result != 0)
            throw std::runtime_error("error: to load shader: " + RSF.GetPathFile());

        mShaderFoundation = new core::CMash();
        mShaderFoundation->Set<core::CShaderProgram>(core::Shader, RSV.GetRaw<GLchar>(), RSV.GetSize(), GL_VERTEX_SHADER);
        mShaderFoundation->Set<core::CShaderProgram>(core::Shader, RSF.GetRaw<GLchar>(), RSF.GetSize(), GL_FRAGMENT_SHADER);
        mShaderFoundation->Apply();

        result = RV.Load(RESOURCES "vertex/foundation.xyz", 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + RV.GetPathFile());

        result = RI.Load(RESOURCES "vertex/foundation.index", 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + RI.GetPathFile());

        mMashFoundation = new core::CMash();
        mMashFoundation->Set<core::CDrawElements>(core::Elements, GL_LINE_LOOP, RI.GetCount());
        mMashFoundation->Set<core::CVAO>(core::VAO);
        mMashFoundation->Set<core::CBuffer>(core::Buffer, RV.GetData<GLfloat>(), RV.GetCount(), &core::xyz);
        mMashFoundation->Set<core::CEBO>(core::EBO, RI.GetData<GLuint>(), RI.GetCount());
        // mMashFoundation->Set<core::CShaderProgram>(core::Shader, mShaderFoundation->Get<core::CShaderProgram>(core::Shader));
        mMashFoundation->Set(mShaderFoundation);
        mMashFoundation->Apply();

        // -------------------------------------------------------------------

        bmp = imgBrick.GetRaw<TBMPHeader>();
        if(bmp == nullptr)
            throw std::runtime_error("error: bring bmp");

        result = RV.Load(RESOURCES "vertex/brick.xyz", 1);
        if(result != 0)
            throw std::runtime_error("error: to load vertex: " + RV.GetPathFile());

        result = RT.Load(RESOURCES "vertex/brick.st", 1);
        if(result != 0)
            throw std::runtime_error("error: to load vertex: " + RT.GetPathFile());

        mMashBrick = new core::CMash();
        mMashBrick->Set<core::CDrawArrays>(core::Array, GL_TRIANGLE_FAN, 0, RV.GetCount() / 3);
        mMashBrick->Set<core::CVAO>(core::VAO);
        mMashBrick->Set<core::CVBO>(core::VBO, RV.GetData<GLfloat>(), RV.GetCount());
        mMashBrick->Set<core::CTBO>(core::TBO, RT.GetData<GLfloat>(), RT.GetCount());
        mMashBrick->Set<core::CTexture>(core::Texture, imgBrick.GetRaw<GLubyte>(), imgBrick.GetSize(), bmp->Width, bmp->Height, bmp->DataOffset, bmp->Bits_Per_Pixel);
        // mMashBrick->Set<core::CShaderProgram>(core::Shader, mShaderTexture->Get<core::CShaderProgram>(core::Shader));
        mMashBrick->Set(mShaderTexture);
        mMashBrick->Apply();

        result = RV.Load(RESOURCES "vertex/window.xyzst", 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + RV.GetPathFile());

        result = RI.Load(RESOURCES "vertex/window.index", 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + RI.GetPathFile());

        mMashWindow = new core::CMash();
        mMashWindow->Set<core::CDrawElements>(core::Elements, GL_TRIANGLES, RI.GetCount());
        mMashWindow->Set<core::CVAO>(core::VAO);
        mMashWindow->Set<core::CBuffer>(core::Buffer, RV.GetData<GLfloat>(), RV.GetCount(), &core::xyzst);
        mMashWindow->Set<core::CEBO>(core::EBO, RI.GetData<GLuint>(), RI.GetCount());
        mMashWindow->Set<core::CTexture>(core::Texture, mTextureWindow);
        // mMashWindow->Set<core::CShaderProgram>(core::Shader, mShaderTexture->Get<core::CShaderProgram>(core::Shader));
        mMashWindow->Set(mShaderTexture);
        mMashWindow->Apply();

        // ------------------------------------------------------------------

        result = RV.Load(RESOURCES "vertex/square.xyzrgbst", 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + RV.GetPathFile());

        result = RI.Load(RESOURCES "vertex/square.index", 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + RI.GetPathFile());

        bmp = imgTest.GetRaw<TBMPHeader>();
        if(bmp == nullptr)
            throw std::runtime_error("error: bring bmp");

        result = RSV.Load(RESOURCES "shaders/pos3col3tex2.vert");
        if(result != 0)
            throw std::runtime_error("error: to load shader: " + RSV.GetPathFile());

        result = RSF.Load(RESOURCES "shaders/pos3col3tex2.frag");
        if(result != 0)
            throw std::runtime_error("error: to load shader: " + RSF.GetPathFile());

        mMashSquare = new core::CMash();
        mMashSquare->Set<core::CDrawElements>(core::Elements, GL_TRIANGLES, 6);
        mMashSquare->Set<core::CVAO>(core::VAO);
        mMashSquare->Set<core::CBuffer>(core::Buffer, RV.GetData<GLfloat>(), RV.GetCount(), &core::xyzrgbst);
        mMashSquare->Set<core::CEBO>(core::EBO, RI.GetData<GLuint>(), RI.GetCount());
        mMashSquare->Set<core::CTexture>(core::Texture, imgTest.GetRaw<GLubyte>(), imgTest.GetSize(), bmp->Width, bmp->Height, bmp->DataOffset, bmp->Bits_Per_Pixel, &core::CTexture::ParamBase);
        mMashSquare->Set<core::CShaderProgram>(core::Shader, RSV.GetRaw<GLchar>(), RSV.GetSize(), GL_VERTEX_SHADER);
        mMashSquare->Set<core::CShaderProgram>(core::Shader, RSF.GetRaw<GLchar>(), RSF.GetSize(), GL_FRAGMENT_SHADER);
        mMashSquare->Apply();

        // -------------------------------------------------------------------

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // Define the viewport dimensions
        /*glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };*/
    };

    void PaintGL()
    {
        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        mMashBrick->Draw();
        mMashWindow->Draw();
        mMashRoof->Draw();
        mMashFoundation->Draw();
        mMashSquare->Draw();

        // glm::mat4 view;
        // GLfloat radius = 10.0f;

        // GLfloat time = glfwGetTime();

        // GLfloat camX = std::sin(time) * radius;
        // GLfloat camZ = std::cos(time) * radius;
        // view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        // Projection
        // glm::mat4 projection;
        // projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

        // for(GLuint i = 0; i < 10; i++) {
        // Calculate the model matrix for each object and pass it to shader before drawing
        // glm::mat4 model;
        // model = glm::translate(model, cubePositions[i]);
        // GLfloat angle = 20.0f * i;
        // model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
        // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        // glBindTexture(GL_TEXTURE_2D, texture);

        // render container
        // program_roof.Use();
        // ebo->Draw();
        // }
    }

    static void ResizeGL(int width, int height)
    {
        glViewport(0, 0, width, height);
    }
};


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
    CProcess process;
    GLenum result = 0;
    GLFWwindow* window = nullptr;

    std::string title = "Tutorial GLFW + OpenGL " + std::string(VERSION);

    result = glfwInit();
    if(result == GLFW_TRUE) {

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // Окно не изменяет размер

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, title.data(), nullptr, nullptr);
        if(window != nullptr) {

            glfwMakeContextCurrent(window);
            glfwSetKeyCallback(window, key_callback);

            result = glewInit();
            if(result == GLEW_OK) {

                glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

                const GLubyte* version = glGetString(GL_VERSION);
                const GLubyte* renderer = glGetString(GL_RENDERER);

                std::cout << version << std::endl;
                std::cout << renderer << std::endl;

                process.InitializeGL();

                while(!glfwWindowShouldClose(window)) {

                    process.PaintGL();

                    glfwSwapBuffers(window); // Swap the screen buffers
                    glfwPollEvents(); // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
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