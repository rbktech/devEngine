#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

#include <core/core.h>

#define SCREEN_WIDTH 1024.0f
#define SCREEN_HEIGHT 768.0f

class CProcess
{
private:
    GLboolean mMouseLeftPressed = false;
    GLboolean mMouseRightPressed = false;

    GLfloat mXPosition = 0.0f;
    GLfloat mYPosition = 0.0f;

    GLint mMode = 0;

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
        core::release();
    }

    void InitializeGL()
    {
        core::Init(nullptr);

        core::object("texture_1") //
            .Texture(RESOURCES "textures/box/1.bmp")
            .Apply();

        core::object("texture_2") //
            .Texture(RESOURCES "textures/box/2.bmp")
            .Apply();

        core::object("texture_3") //
            .Texture(RESOURCES "textures/box/3.bmp")
            .Apply();

        core::object("texture_4") //
            .Texture(RESOURCES "textures/box/4.bmp")
            .Apply();

        core::object("texture_5") //
            .Texture(RESOURCES "textures/box/5.bmp")
            .Apply();

        core::object("texture_6") //
            .Texture(RESOURCES "textures/box/6.bmp")
            .Apply();

        core::object("texture_7") //
            .Texture(RESOURCES "textures/box/7.bmp")
            .Apply();

        core::object("texture_8") //
            .Texture(RESOURCES "textures/box/8.bmp")
            .Apply();

        core::object("texture_9") //
            .Texture(RESOURCES "textures/box/9.bmp")
            .Apply();

        core::object("shader")
            .Shader(RESOURCES "shaders/pos3tex2.vert")
            .Shader(RESOURCES "shaders/pos3tex2.frag")
            .Apply();

        core::object("camera") //
            .Camera()
            .Apply();

        core::object("perspective") //
            .Perspective(45.0f, SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f)
            .Apply();

        core::object("map")
            .VAO()
            .Buffer(RESOURCES "vertex/map.xyzst")
            .EBO(RESOURCES "vertex/map.index")
            .Camera(core::object("camera"))
            .Perspective(core::object("perspective"))
            .Matrix()
            .Translate(-1.5f, 3.0f, -1.5f)
            .Apply();

        core::object("cube")
            .VAO()
            .Buffer(RESOURCES "vertex/cube.xyzst")
            .EBO(RESOURCES "vertex/cube.index")
            .Camera(core::object("camera"))
            .Perspective(core::object("perspective"))
            .Matrix()
            // .Scale(10.0f)
            .Apply();

        core::object("relief")
            .VAO()
            .Buffer(RESOURCES "vertex/relief.xyzst")
            .EBO(RESOURCES "vertex/relief.index")
            .Camera(core::object("camera"))
            .Perspective(core::object("perspective"))
            .Matrix()
            .Translate(-1.0f, -1.0f, -1.0f)
            .Apply();


        core::object("test")
            .VAO()
            .Buffer(RESOURCES "vertex/test.xyzst")
            .EBO(RESOURCES "vertex/test.index")
            .Camera(core::object("camera"))
            .Perspective(core::object("perspective"))
            .Matrix()
            .Translate(-1.0f, 0.0f, -1.0f)
            .Apply();

        glEnable(GL_DEPTH_TEST);
    };

    void PaintGL()
    {
        glm::mat4 transform;

        glClearColor(0.3f, 0.8f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // core::draw();

        // ---------------------------------------------------------------

        core::object("shader").Get()->Get<core::CShaderProgram>(core::Shader)->Use();

        GLuint shader = core::object("shader").Get()->Get<core::CShaderProgram>(core::Shader)->Get();

        auto view = core::object("camera").Get()->Get<core::CCamera>(core::Camera)->GetMatrix();
        core::CShaderProgram::Update(shader, "u_view", glm::value_ptr(view));

        auto projection = core::object("perspective").Get()->Get<core::CPerspective>(core::Perspective)->GetMatrix();
        core::CShaderProgram::Update(shader, "u_projection", glm::value_ptr(projection));

        // ---------------------------------------------------------------

        core::object("map").Get()->Get<core::CVAO>(core::VAO)->Bind();

        transform = core::object("map").Get()->Get<core::CMatrix>(core::Matrix)->GetMatrix();
        core::CShaderProgram::Update(shader, "u_model", glm::value_ptr(transform));

        core::object("texture_1").Get()->Get<core::CTexture>(core::Texture)->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLuint*)(0 * sizeuint));

        core::object("texture_2").Get()->Get<core::CTexture>(core::Texture)->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLuint*)(6 * sizeuint));

        core::object("texture_3").Get()->Get<core::CTexture>(core::Texture)->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLuint*)(12 * sizeuint));

        core::object("texture_4").Get()->Get<core::CTexture>(core::Texture)->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLuint*)(18 * sizeuint));

        core::object("texture_5").Get()->Get<core::CTexture>(core::Texture)->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLuint*)(24 * sizeuint));

        core::object("texture_6").Get()->Get<core::CTexture>(core::Texture)->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLuint*)(30 * sizeuint));

        core::object("texture_7").Get()->Get<core::CTexture>(core::Texture)->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLuint*)(36 * sizeuint));

        core::object("texture_8").Get()->Get<core::CTexture>(core::Texture)->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLuint*)(42 * sizeuint));

        core::object("texture_9").Get()->Get<core::CTexture>(core::Texture)->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLuint*)(48 * sizeuint));

        // ---------------------------------------------------------------

        core::object("relief").Get()->Get<core::CVAO>(core::VAO)->Bind();

        transform = core::object("relief").Get()->Get<core::CMatrix>(core::Matrix)->GetMatrix();
        core::CShaderProgram::Update(shader, "u_model", glm::value_ptr(transform));

        core::object("texture_1").Get()->Get<core::CTexture>(core::Texture)->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLuint*)(0 * sizeuint));

        core::object("texture_2").Get()->Get<core::CTexture>(core::Texture)->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLuint*)(6 * sizeuint));

        core::object("texture_3").Get()->Get<core::CTexture>(core::Texture)->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLuint*)(12 * sizeuint));

        core::object("texture_4").Get()->Get<core::CTexture>(core::Texture)->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLuint*)(18 * sizeuint));

        // ---------------------------------------------------------------

        core::object("cube").Get()->Get<core::CVAO>(core::VAO)->Bind();

        transform = core::object("cube").Get()->Get<core::CMatrix>(core::Matrix)->GetMatrix();
        core::CShaderProgram::Update(shader, "u_model", glm::value_ptr(transform));

        core::object("texture_1").Get()->Get<core::CTexture>(core::Texture)->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLuint*)(0 * sizeuint));

        core::object("texture_2").Get()->Get<core::CTexture>(core::Texture)->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLuint*)(6 * sizeuint));

        core::object("texture_3").Get()->Get<core::CTexture>(core::Texture)->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLuint*)(12 * sizeuint));

        core::object("texture_4").Get()->Get<core::CTexture>(core::Texture)->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLuint*)(18 * sizeuint));

        // ---------------------------------------------------------------

        core::object("test").Get()->Get<core::CVAO>(core::VAO)->Bind();

        transform = core::object("test").Get()->Get<core::CMatrix>(core::Matrix)->GetMatrix();
        core::CShaderProgram::Update(shader, "u_model", glm::value_ptr(transform));

        core::object("texture_1").Get()->Get<core::CTexture>(core::Texture)->Bind();
        glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, (GLuint*)(0 * sizeuint));
    }

    void RefreshKeyGL(const int& key) // Change value
    {
        switch(key) {
            case KEY_PRESS_Q: {
                break;
            }
            case KEY_PRESS_E: {
                break;
            }
            case KEY_PRESS_W: {
                break;
            }
            case KEY_PRESS_S: {
                break;
            }
            case KEY_PRESS_A: {
                break;
            }
            case KEY_PRESS_D: {
                break;
            }
            default:
                break;
        }
    }

    void RefreshMouseGL(const GLfloat& xPosition, const GLfloat& yPosition)
    {
        if(mMouseRightPressed == true) {}

        if(mMouseLeftPressed == true) {

            GLfloat pitch = (yPosition - mYPosition) / 5.0f;
            GLfloat yaw = (mXPosition - xPosition) / 5.0f;

            core::object("camera").Camera(core::CCamera::TRotate { pitch, yaw }).Update();
        }

        mXPosition = xPosition;
        mYPosition = yPosition;
    }

    void RefreshCenter()
    {
    }

    void RefreshGL(const GLfloat& pitch, const GLfloat& yaw)
    {
    }

    void ResizeGL(int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void ModeGL()
    {
        core::Mode(mMode++);
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

        window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, title.data(), nullptr, nullptr);
        if(window != nullptr) {

            glfwSetWindowUserPointer(window, &process);

            glfwMakeContextCurrent(window);

            // make sure the viewport matches the new window dimensions;
            // note that width and height will be significantly larger than specified on retina displays.
            glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
                CProcess* process = static_cast<CProcess*>(glfwGetWindowUserPointer(window));
                if(process != nullptr) {
                    process->ResizeGL(width, height);
                }
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
                    } else if(key == GLFW_KEY_F4 && action == GLFW_PRESS) {
                        process->ModeGL();
                    }
                }
            });

            process.InitializeGL();

            while(!glfwWindowShouldClose(window)) {

                process.PaintGL();

                glfwProcessInput(window);
                glfwSwapBuffers(window);
                glfwPollEvents();
            }

            process.ReleaseGL();
        } else
            std::cout << "Failed to create GLFW window" << std::endl;

        glfwTerminate();
    } else
        std::cout << "error: GLFW initialize" << std::endl;

    return 0;
}