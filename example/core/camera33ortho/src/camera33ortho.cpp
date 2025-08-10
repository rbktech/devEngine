#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <core/core.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

class CProcess
{
private:
    GLfloat mScreenWidth = 1024.0f;
    GLfloat mScreenHeight = 768.0f;

    GLboolean mMouseLeftPressed = false;
    GLboolean mMouseRightPressed = false;

    GLfloat mXPosition = 0.0f;
    GLfloat mYPosition = 0.0f;

    GLfloat mZoom = 1.0f;

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
        glEnable(GL_DEPTH_TEST);

        core::object("shader") //
            .Shader(RESOURCES "shaders/pos3col3.vert")
            .Shader(RESOURCES "shaders/pos3col3.frag")
            .Apply();

        core::object("projection") //
            .Orthographic(-50.0f, -50.0f + mScreenWidth, -50.0f, -50.0f + mScreenHeight, -1.0f, 1.0f)
            .Apply();

        core::object("cursor_projection") //
            .Orthographic(-50.0f, -50.0f + mScreenWidth, -50.0f, -50.0f + mScreenHeight, -1.0f, 1.0f)
            .Apply();

        core::object("rect") //
            .VAO()
            .VBO(RESOURCES "vertex/rect.xyz")
            .CBO(RESOURCES "vertex/rect.rgb")
            .Orthographic(core::object("projection"))
            .Shader(core::object("shader"))
            .Matrix()
            .Arrays(GL_LINE_LOOP, 0, 4)
            .Apply();

        core::object("cursor") //
            .VAO()
            .VBO(RESOURCES "vertex/cursor.xyz")
            .CBO(RESOURCES "vertex/cursor.rgb")
            .Orthographic(core::object("cursor_projection"))
            .Shader(core::object("shader"))
            .Matrix()
            .Translate((mScreenWidth / 2.0f) - 50.0f, (mScreenHeight / 2.0f) - 50.0f)
            .Arrays(GL_LINES, 0, 4)
            .Apply();

        core::object("coordinate") //
            .VAO()
            .VBO(RESOURCES "vertex/coordinate.xyz")
            .CBO(RESOURCES "vertex/coordinate.rgb")
            .Orthographic(core::object("projection"))
            .Shader(core::object("shader"))
            .Matrix()
            .Arrays(GL_LINES, 0, 4)
            .Apply();

        GLfloat cPoint[12] {
            1.0f, 0.0f, 0.0f, //
            1.0f, 0.0f, 0.0f, //
            1.0f, 0.0f, 0.0f, //
            1.0f, 0.0f, 0.0f, //
        };

        core::object("point") //
            .VAO()
            .VBO(nullptr, 0)
            .CBO(cPoint, sizeof(cPoint) / sizeof(cPoint[0]))
            .Orthographic(core::object("projection"))
            .Shader(core::object("shader"))
            .Matrix()
            .Arrays(GL_LINE_LOOP, 0, 0)
            .Apply();

        GLfloat vZero[3] {
            0.0f, 0.0f, 0.0f, //
        };

        core::object("zero") //
            .VAO()
            .VBO(vZero, sizeof(vZero) / sizeof(vZero[0]))
            .Orthographic(core::object("projection"))
            .Shader(core::object("shader"))
            .Matrix()
            .Arrays(GL_POINTS, 0, 1)
            .Apply();
    };

    void PaintGL()
    {
        glClearColor(0.3f, 0.8f, 0.59f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        core::draw();
    }

    void RefreshKeyGL(const int& key) // Change value
    {
        core::COrthographic::TScale scale;
        core::COrthographic::TMoveXY move;

        switch(key) {
            case KEY_PRESS_Q: {

                scale.value = 100;

                core::object("projection") //
                    .Orthographic(scale)
                    .Update();
                break;
            }
            case KEY_PRESS_E: {

                scale.value = -100;

                core::object("projection") //
                    .Orthographic(scale)
                    .Update();
                break;
            }
            case KEY_PRESS_W: {

                move.y = 100;

                core::object("projection") //
                    .Orthographic(move)
                    .Update();
                break;
            }
            case KEY_PRESS_S: {

                move.y = -100;

                core::object("projection") //
                    .Orthographic(move)
                    .Update();
                break;
            }
            case KEY_PRESS_A: {

                move.x = -100;

                core::object("projection") //
                    .Orthographic(move)
                    .Update();
                break;
            }
            case KEY_PRESS_D: {

                move.x = 100;

                core::object("projection") //
                    .Orthographic(move)
                    .Update();
                break;
            }
            default:
                break;
        }
    }

    void RefreshScrollGL(const GLfloat& xOffset, const GLfloat& yOffset)
    {
        GLfloat zoom = mZoom + yOffset / 10.0f;
        if(zoom > 0.01)
            mZoom = zoom;

        core::COrthographic::TScale scale { yOffset * 10.0f };

        core::object("projection").Orthographic(scale).Update();
    };

    void RefreshMouseGL(const GLfloat& xPosition, const GLfloat& yPosition)
    {
        std::shared_ptr<core::CVBO> pVBO = nullptr;
        std::shared_ptr<core::COrthographic> pOrthographic = nullptr;

        std::vector<std::shared_ptr<core::CVBO>> collision;

        pOrthographic = core::object("projection").Get()->Get<core::COrthographic>(core::Orthographic);
        if(pOrthographic != nullptr) {

            GLfloat ndcX = (2.0f * xPosition) / mScreenWidth - 1.0f;
            GLfloat ndcY = 1.0f - (2.0f * yPosition) / mScreenHeight;
            glm::vec4 rayCentreNDC(ndcX, ndcY, 0.0f, 1.0f); // z = 1 (дальняя плоскость)
            glm::mat4 inverseVP = glm::inverse(pOrthographic->GetMatrix());
            glm::vec3 rayCentreWorld = inverseVP * rayCentreNDC;

            core::print(rayCentreWorld);

            pVBO = core::object("zero").Get()->Get<core::CVBO>(core::VBO);
            if(pVBO != nullptr)
                collision.emplace_back(pVBO);

            pVBO = core::object("rect").Get()->Get<core::CVBO>(core::VBO);
            if(pVBO != nullptr)
                collision.emplace_back(pVBO);

            float* point = nullptr;

            for(auto& vbo : collision) {

                GLint size = 0;

                glBindBuffer(GL_ARRAY_BUFFER, vbo->Get());

                glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

                size /= sizefloat * 3;

                glm::vec3* ptr = static_cast<glm::vec3*>(glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY));
                if(ptr != nullptr) {

                    for(int i = 0; i < size; i++) {
                        if((ptr[i].x - 1.0f < rayCentreWorld.x && rayCentreWorld.x < ptr[i].x + 1.0f) &&
                            (ptr[i].y - 1.0f < rayCentreWorld.y && rayCentreWorld.y < ptr[i].y + 1.0f)) {

                            point = new float[12] {
                                ptr[i].x + 10.0f, ptr[i].y + 10.0f, ptr[i].z, //
                                ptr[i].x + 10.0f, ptr[i].y - 10.0f, ptr[i].z, //
                                ptr[i].x - 10.0f, ptr[i].y - 10.0f, ptr[i].z, //
                                ptr[i].x - 10.0f, ptr[i].y + 10.0f, ptr[i].z  //
                            };

                            break;
                        }
                    }
                }

                glUnmapBuffer(GL_ARRAY_BUFFER);

                if(point != nullptr)
                    break;
            }

            if(point == nullptr) {
                core::object("point") //
                    .VBO(nullptr, 0)
                    .Arrays(GL_LINE_LOOP, 0, 0)
                    .Update();
            } else {
                core::object("point") //
                    .VBO(point, 12)
                    .Arrays(GL_LINE_LOOP, 0, 4)
                    .Update();

                delete[] point;
            }
        }

        pOrthographic = core::object("cursor_projection").Get()->Get<core::COrthographic>(core::Orthographic);
        if(pOrthographic != nullptr) {

            GLfloat ndcX = (2.0f * xPosition) / mScreenWidth - 1.0f;
            GLfloat ndcY = 1.0f - (2.0f * yPosition) / mScreenHeight;
            glm::vec4 rayCentreNDC(ndcX, ndcY, 0.0f, 1.0f); // z = 1 (дальняя плоскость)
            glm::mat4 inverseVP = glm::inverse(pOrthographic->GetMatrix());
            glm::vec3 rayCentreWorld = inverseVP * rayCentreNDC;

            core::object("cursor").Translate(rayCentreWorld.x, rayCentreWorld.y).Update();
        }

        if(mMouseLeftPressed == true) {

            core::COrthographic::TMoveXY move;

            move.x = (mXPosition - xPosition) * mZoom;
            move.y = (yPosition - mYPosition) * mZoom;

            core::object("projection").Orthographic(move).Update();
            core::object("cursor_projection").Orthographic(move).Update();
        }

        if(mMouseRightPressed == true) {}

        mXPosition = xPosition;
        mYPosition = yPosition;
    }

    void RefreshCenter()
    {
        mZoom = 1.0f;
        core::object("projection") //
            .Orthographic(-50.0f, -50.0f + SCREEN_WIDTH, -50.0f, -50.0f + SCREEN_HEIGHT, -1.0f, 1.0f)
            .Update();
    }

    void RefreshGL(const GLfloat& pitch, const GLfloat& yaw)
    {
    }

    void ResizeGL(int width, int height)
    {
        mScreenWidth = width;
        mScreenHeight = height;

        core::object("projection") //
            .Orthographic(core::COrthographic::TSize { (GLfloat)width, (GLfloat)height })
            .Update();

        core::object("cursor_projection") //
            .Orthographic(core::COrthographic::TSize { (GLfloat)width, (GLfloat)height })
            .Update();

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

            glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
                CProcess* process = static_cast<CProcess*>(glfwGetWindowUserPointer(window));
                if(process != nullptr) {
                    process->RefreshScrollGL(xoffset, yoffset);
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

            core::Init(window);
            core::Version();

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