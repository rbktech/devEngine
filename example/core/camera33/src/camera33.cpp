#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_transform.hpp>

#include <iostream>

#include "core/object/cbo.h"
#include "core/object/vbo.h"
#include "core/object/camera.h"
#include <core/object/matrix.h>
#include <core/object/translate.h>
#include <core/object/ebo.h>
#include <core/object/vao.h>
#include <core/object/bitmap.h>
#include <core/object/buffer.h>
#include <core/object/draw.h>
#include <core/object/perspective.h>
#include <core/object/rotate.h>
#include <core/object/scale.h>

#include <core/mash.h>
#include <core/matrixglm.h>
#include <core/object/shader.h>
#include <core/object/texture.h>
#include <core/resources.h>
#include <core/error.h>

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

glm::vec3 gCubePositions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),     //
    glm::vec3(2.0f, 5.0f, -15.0f),   //
    glm::vec3(-1.5f, -2.2f, -2.5f),  //
    glm::vec3(-3.8f, -2.0f, -12.3f), //
    glm::vec3(2.4f, -0.4f, -3.5f),   //
    glm::vec3(-1.7f, 3.0f, -7.5f),   //
    glm::vec3(1.3f, -2.0f, -2.5f),   //
    glm::vec3(1.5f, 2.0f, -2.5f),    //
    glm::vec3(1.5f, 0.2f, -1.5f),    //
    glm::vec3(-1.3f, 1.0f, -1.5f)    //
};

class CProcess
{
private:
    core::CMash* mRect = nullptr;
    core::CMash* mShader0 = nullptr;

    core::CMash* mCube = nullptr;
    core::CMash* mShader1 = nullptr;

    GLfloat mRadius = 3.0f;

    glm::vec3 mCameraEye = { 0.0f, 0.0f, mRadius };
    glm::vec3 mCameraFront = { 0.0f, 0.0f, 1.0f };
    glm::vec3 mCameraCenter = { 0.0f, 0.0f, 0.0f };
    glm::vec3 mCameraUp = { 0.0f, 1.0f, 0.0f };

    GLfloat mPitch = 0.0f; // Угол тангаж (в градусах)
    GLfloat mYaw = 0.0f;   // Угол рыскание (в градусах)
    // GLfloat mRoll = 0.0f; // Угол крен  (в градусах)

    GLboolean mMouseLeftPressed = false;
    GLboolean mMouseRightPressed = false;

    GLfloat mXPosition = 0.0f;
    GLfloat mYPosition = 0.0f;

public:
    enum {
        KEY_PRESS_Q,
        KEY_PRESS_E,
        KEY_PRESS_W,
        KEY_PRESS_A,
        KEY_PRESS_S,
        KEY_PRESS_D,
    };

    void SetMouseLeftPressed(const bool& value)
    {
        mMouseLeftPressed = value;
    }

    void SetMouseRightPressed(const bool& value)
    {
        mMouseRightPressed = value;
    }

    void ReleaseGL()
    {
        delete mRect;
        delete mShader0;

        delete mCube;
        delete mShader1;
    }

    void InitializeGL()
    {
        GLenum result = 0;

        {
            CResource RV0;
            CResource RI0;
            CResource RSV;
            CResource RSF;
            CResource RIM0;

            TBMPHeader* bmp = nullptr;

            result = RIM0.Load(RESOURCES "textures/bit.bmp");
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
            mShader0->Set<core::CPerspective>(core::Perspective, 45.0f, SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
            mShader0->Apply();

            bmp = RIM0.GetRaw<TBMPHeader>();
            if(bmp == nullptr)
                throw std::runtime_error("error: bring bmp");

            mRect = new core::CMash();
            mRect->Set<core::CVAO>(core::VAO);
            mRect->Set<core::CMatrix>(core::Matrix);
            mRect->Set<core::CTranslate>(core::Translate, 0.0f, 0.0f, -3.0f);
            mRect->Set<core::CRotate>(core::Rotate, -55.0f, 1.0f, 0.0f, 0.0f);
            mRect->Set<core::CDrawElements>(core::Elements, GL_TRIANGLES, RI0.GetCount());
            mRect->Set<core::CBuffer>(core::Buffer, RV0.GetData<GLfloat>(), RV0.GetCount(), &core::xyzrgbst);
            mRect->Set<core::CEBO>(core::EBO, RI0.GetData<GLuint>(), RI0.GetCount());
            mRect->Set<core::CTexture>(core::Texture, RIM0.GetRaw<GLchar>(), RIM0.GetSize(), bmp->Width, bmp->Height,
                bmp->DataOffset, bmp->Bits_Per_Pixel);
            mRect->Set(mShader0);
            mRect->Apply();
        }

        {
            CResource RV1;
            CResource RSV;
            CResource RSF;
            CResource RIM1;

            TBMPHeader* bmp = nullptr;

            result = RIM1.Load(RESOURCES "textures/bit.bmp");
            if(result != 0)
                throw std::runtime_error("error: to load texture: " + RIM1.GetPathFile());

            result = RSV.Load(RESOURCES "shaders/pos3tex2.vert");
            if(result != 0)
                throw std::runtime_error("error: to load shader: " + RSV.GetPathFile());

            result = RSF.Load(RESOURCES "shaders/pos3tex2.frag");
            if(result != 0)
                throw std::runtime_error("error: to load shader: " + RSF.GetPathFile());

            result = RV1.Load(RESOURCES "vertex/cube.xyzst", 1);
            if(result != 0)
                throw std::runtime_error("error: to load resource: " + RV1.GetPathFile());

            mShader1 = new core::CMash();
            mShader1->Set<core::CShaderProgram>(core::Shader, RSV.GetRaw<GLchar>(), RSV.GetSize(), GL_VERTEX_SHADER);
            mShader1->Set<core::CShaderProgram>(core::Shader, RSF.GetRaw<GLchar>(), RSF.GetSize(), GL_FRAGMENT_SHADER);
            mShader1->Set<core::CPerspective>(core::Perspective, 45.0f, SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
            mShader1->Apply();

            bmp = RIM1.GetRaw<TBMPHeader>();
            if(bmp == nullptr)
                throw std::runtime_error("error: bring bmp");

            mCube = new core::CMash();
            mCube->Set<core::CVAO>(core::VAO);
            mCube->Set<core::CMatrix>(core::Matrix);
            // mCube->Set<core::CTranslate>(core::Translate, 0.0f, 0.0f, -3.0f);
            mCube->Set<core::CTranslate>(core::Translate);
            mCube->Set<core::CRotate>(core::Rotate);
            // mCube->Set<core::CScale>(core::Scale, 1.0f, 1.0f, 3.0f);
            mCube->Set<core::CDrawArrays>(core::Array, GL_TRIANGLES, 0, RV1.GetCount() / 3);
            mCube->Set<core::CBuffer>(core::Buffer, RV1.GetData<GLfloat>(), RV1.GetCount(), &core::xyzst);
            mCube->Set<core::CTexture>(core::Texture, RIM1.GetRaw<GLfloat>(), RIM1.GetSize(), bmp->Width, bmp->Height,
                bmp->DataOffset, bmp->Bits_Per_Pixel);
            mCube->Set(mShader1);
            mCube->Apply();
        }

        glEnable(GL_DEPTH_TEST);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    };

    void PaintGL()
    {
        glClearColor(0.3f, 0.8f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // const float radius = 10.0f;
        // float camX = sin(glfwGetTime()) * radius;
        // float camZ = cos(glfwGetTime()) * radius;

        // glm::mat4 view;
        // view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        // glm::mat4 view = glm::lookAt(mCameraEye, mCameraEye - mCameraFront, mCameraUp);
        glm::mat4 view = glm::lookAt(mCameraEye, mCameraCenter, mCameraUp);

        mCube->Get<core::CShaderProgram>(core::Shader)->Use();
        mCube->Get<core::CShaderProgram>(core::Shader)->Update("u_view", glm::value_ptr(view));

        // mCube->Draw();

        mCube->Set<core::CMatrix>(core::Matrix, glm::mat4(1.0f));
        mCube->Set<core::CTranslate>(core::Translate, 0.0f, 0.0f, -3.0f);
        mCube->Set<core::CRotate>(core::Rotate, glm::degrees(glfwGetTime() * glm::radians(50.0f)), 0.5f, 1.0f, 0.0f);
        mCube->Update();

        mRect->Draw();
        mCube->Draw();

        for(unsigned int i = 0; i < 10; i++) {

            glm::vec3 vec = gCubePositions[i];

            float angle = 20.0f * i;

            mCube->Set<core::CMatrix>(core::Matrix, glm::mat4(1.0f));
            mCube->Set<core::CTranslate>(core::Translate, vec.x, vec.y, vec.z - 3);
            mCube->Set<core::CRotate>(core::Rotate, angle, 1.0f, 0.3f, 0.5f);
            mCube->Update();
            mCube->Draw();
        }
    }

    void RefreshKeyGL(const int& key) // Change value
    {
        switch(key) {
            case KEY_PRESS_Q: {
                mRadius -= 1.0f;
                break;
            }
            case KEY_PRESS_E: {
                mRadius += 1.0f;
                break;
            }
            case KEY_PRESS_W: {
                (mCameraCenter -= glm::normalize(mCameraFront)).y = 0.0f;
                break;
            }
            case KEY_PRESS_S: {
                (mCameraCenter += glm::normalize(mCameraFront)).y = 0.0f;
                break;
            }
            case KEY_PRESS_A: {
                (mCameraCenter += glm::normalize(glm::cross(mCameraFront, mCameraUp))).y = 0.0f;
                break;
            }
            case KEY_PRESS_D: {
                (mCameraCenter -= glm::normalize(glm::cross(mCameraFront, mCameraUp))).y = 0.0f;
                break;
            }
            default:
                break;
        }

        Refresh();
    }

    void RefreshMouseGL(const GLfloat& xPosition, const GLfloat& yPosition)
    {
        if(mMouseRightPressed == true) {

            GLfloat pitch = mPitch + (yPosition - mYPosition) / 10.0f;
            GLfloat yaw = mYaw + (mXPosition - xPosition) / 10.0f;

            if(-90 < pitch && pitch < 90.0f) {
                mPitch = pitch;
                mYaw = yaw;
                Refresh();
            }
        }

        if(mMouseLeftPressed == true) {

            glm::vec3 movement;

            movement.x = (xPosition - mXPosition) / 10.0F;
            movement.z = (mYPosition - yPosition) / 10.0F;

            glm::vec3 right = glm::cross(mCameraFront, mCameraUp);

            mCameraCenter +=               //
                movement.x * right +       // движение влево/вправо
                movement.z * mCameraFront; // движение вперед/назад

            Refresh();
        }

        mXPosition = xPosition;
        mYPosition = yPosition;
    }

    void RefreshCenter()
    {
        mCameraCenter = glm::vec3(0.0f);
        mRadius = 3.0f;
        mPitch = 0.0f;
        mYaw = 0.0f;

        Refresh();
    }

    void RefreshGL(const GLfloat& pitch, const GLfloat& yaw)
    {
        if(-90 < mPitch + pitch && mPitch + pitch < 90.0f) {
            mPitch += pitch;
            mYaw += yaw;

            Refresh();
        }
    }

    void Refresh()
    {
        mCameraEye.x = mCameraCenter.x + mRadius * glm::sin(glm::radians(mYaw)) * glm::cos(glm::radians(mPitch));
        mCameraEye.y = mCameraCenter.y + mRadius * glm::sin(glm::radians(mPitch));
        mCameraEye.z = mCameraCenter.z + mRadius * glm::cos(glm::radians(mYaw)) * glm::cos(glm::radians(mPitch));

        {
            mCameraFront.x = glm::sin(glm::radians(mYaw)) * glm::cos(glm::radians(mPitch));
            mCameraFront.z = glm::cos(glm::radians(mYaw)) * glm::cos(glm::radians(mPitch));
        }

        // или

        {
            // mCameraFront = glm::normalize(mCameraCenter - mCameraEye);
        }

        core::print(mCameraEye, "mCameraEye");
        core::print(mCameraFront, "mCameraFront");
        core::print(mCameraCenter, "mCameraCenter");

        core::print(mYaw, "mYaw");
        core::print(mPitch, "mPitch");
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
            glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
                CProcess::ResizeGL(width, height); //
            });

            glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
                CProcess* process = static_cast<CProcess*>(glfwGetWindowUserPointer(window));
                if(process != nullptr) {
                    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
                        process->SetMouseLeftPressed(true);
                    } else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
                        process->SetMouseLeftPressed(false);
                    } else if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
                        process->SetMouseRightPressed(true);
                    } else if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
                        process->SetMouseRightPressed(false);
                    }
                }
            });

            glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos) {
                CProcess* process = static_cast<CProcess*>(glfwGetWindowUserPointer(window));
                if(process != nullptr) {
                    process->RefreshMouseGL(xPos, yPos);
                }
            });

            glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
                CProcess* process = static_cast<CProcess*>(glfwGetWindowUserPointer(window));
                if(process != nullptr) {
                    if(key == GLFW_KEY_R && action == GLFW_PRESS) {
                        process->RefreshCenter();
                    } else if(key == GLFW_KEY_Q && action == GLFW_PRESS) {
                        process->RefreshKeyGL(CProcess::KEY_PRESS_Q);
                    } else if(key == GLFW_KEY_E && action == GLFW_PRESS) {
                        process->RefreshKeyGL(CProcess::KEY_PRESS_E);
                    } else if(key == GLFW_KEY_W && action == GLFW_PRESS) {
                        process->RefreshKeyGL(CProcess::KEY_PRESS_W);
                    } else if(key == GLFW_KEY_S && action == GLFW_PRESS) {
                        process->RefreshKeyGL(CProcess::KEY_PRESS_S);
                    } else if(key == GLFW_KEY_A && action == GLFW_PRESS) {
                        process->RefreshKeyGL(CProcess::KEY_PRESS_A);
                    } else if(key == GLFW_KEY_D && action == GLFW_PRESS) {
                        process->RefreshKeyGL(CProcess::KEY_PRESS_D);
                    } else if(key == GLFW_KEY_UP && action == GLFW_PRESS) {
                        process->RefreshGL(-10.0f, 0.0f);
                    } else if(key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
                        process->RefreshGL(+10.0f, 0.0f);
                    } else if(key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
                        process->RefreshGL(0.0f, +10.0f);
                    } else if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
                        process->RefreshGL(0.0f, -10.0f);
                    }
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