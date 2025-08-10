// #include <SFML/Graphics.hpp>
// #include <SFML/OpenGL.hpp>

// #include <GL/glu.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/trigonometric.hpp>

#include <core/core.h>

#include <iostream>
#include <thread>

#include <core/error.h>

#define SCREEN_WIDTH 1027.0f
#define SCREEN_HEIGHT 768.0f

void InitOpenGL()
{
    // it works out of the box
    e(glEnable(GL_TEXTURE_2D));

    // Set color and depth clear value
    e(glClearDepth(1.f));                // Core Profile
    e(glClearColor(0.f, 0.f, 0.f, 0.f)); // Core Profile

    // Enable Z-buffer read and write
    e(glEnable(GL_DEPTH_TEST)); // Core Profile
    e(glDepthMask(GL_TRUE));    // Core Profile

    // Setup a perspective projection
    e(glMatrixMode(GL_PROJECTION));
    e(glLoadIdentity()); // Сбрасывает все передвижения в системе координат
    // gluPerspective(90.f, 1.f, 1.f, 100.f);
}

void DrowRect(GLuint texture_handle[], int size)
{
    glBindTexture(GL_TEXTURE_2D, texture_handle[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-size, -size, -size); // Вершина
    glTexCoord2f(1, 0);
    glVertex3f(-size, size, -size);
    glTexCoord2f(1, 1);
    glVertex3f(size, size, -size);
    glTexCoord2f(0, 1);
    glVertex3f(size, -size, -size);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture_handle[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-size, -size, size);
    glTexCoord2f(1, 0);
    glVertex3f(-size, size, size);
    glTexCoord2f(1, 1);
    glVertex3f(size, size, size);
    glTexCoord2f(0, 1);
    glVertex3f(size, -size, size);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture_handle[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-size, -size, -size);
    glTexCoord2f(1, 0);
    glVertex3f(-size, size, -size);
    glTexCoord2f(1, 1);
    glVertex3f(-size, size, size);
    glTexCoord2f(0, 1);
    glVertex3f(-size, -size, size);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture_handle[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(size, -size, -size);
    glTexCoord2f(1, 0);
    glVertex3f(size, size, -size);
    glTexCoord2f(1, 1);
    glVertex3f(size, size, size);
    glTexCoord2f(0, 1);
    glVertex3f(size, -size, size);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture_handle[4]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-size, -size, size);
    glTexCoord2f(1, 0);
    glVertex3f(-size, -size, -size);
    glTexCoord2f(1, 1);
    glVertex3f(size, -size, -size);
    glTexCoord2f(0, 1);
    glVertex3f(size, -size, size);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture_handle[5]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-size, size, size);
    glTexCoord2f(1, 0);
    glVertex3f(-size, size, -size);
    glTexCoord2f(1, 1);
    glVertex3f(size, size, -size);
    glTexCoord2f(0, 1);
    glVertex3f(size, size, size);
    glEnd();
}

/*GLuint LoadImage(const char* nameImage)
{
    sf::Image image;
    image.loadFromFile(nameImage);

    int x = image.getSize().x;
    int y = image.getSize().y;
    auto ptr = image.getPixelsPtr();

    GLuint texture_handle = 0;

    glGenTextures(1, &texture_handle);
    glBindTexture(GL_TEXTURE_2D, texture_handle);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, x, y, GL_RGBA, GL_UNSIGNED_BYTE, ptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    return texture_handle;
}

sf::Clock clockd;

int main(int argc, char** argv)
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antiAliasingLevel = 0;
    settings.majorVersion = 0;
    settings.minorVersion = 0;

    sf::RenderWindow window(sf::VideoMode({ HSCREEN, WSCREEN }), "Round cube. Legacy OpenGL with SFML",
sf::Style::Default);

    sf::Texture t_texture;
    t_texture.loadFromFile(RESOURCES "starsky.png");
    sf::Sprite background(t_texture);

    GLuint brick[6] = { 0 };

    brick[0] = LoadImage(RESOURCES "box/1.jpg");
    brick[1] = LoadImage(RESOURCES "box/2.jpg");
    brick[2] = LoadImage(RESOURCES "box/3.jpg");
    brick[3] = LoadImage(RESOURCES "box/4.jpg");
    brick[4] = LoadImage(RESOURCES "box/5.jpg");
    brick[5] = LoadImage(RESOURCES "box/6.jpg");

    InitOpenGL();

    float size = 5.f;

    while(window.isOpen()) {

        while(const std::optional event = window.pollEvent()) {
            if(event->is<sf::Event::Closed>())
                window.close();
            if(event->is<sf::Event::Resized>()) {
                glViewport(0, 0, window.getSize().x, window.getSize().y);
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Очищается буфер цвета и глубины

        window.pushGLStates();
        window.draw(background);
        window.popGLStates();

        float time = clockd.getElapsedTime().asSeconds() * 100;

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        // Камера находится в (0, 0, 0)
        glTranslatef(0, 0, -50); // Сдвигаем систему координат. Перо где будем рисовать. (X, Y, Z)
        glRotatef(time, 50, 50, 0); // Угол на который поворачивается и вектор во круг которого будет вращаться

        for(int y = 0; y < 5; y++)
            for(int x = 0; x < 5; x++) {
                glTranslatef(x * size * 2, y * size * 2, 0);
                DrowRect(brick, size);
                glTranslatef(-x * size * 2, -y * size * 2, 0);
            }

        window.display();
    }
}*/

class CProcess
{
private:
    uint16_t mMode = 0;

    GLboolean mMouseLeftPressed = false;
    GLboolean mMouseRightPressed = false;

    GLfloat mXPosition = 0.0f;
    GLfloat mYPosition = 0.0f;

    std::shared_ptr<core::CTexture> mTextureBox1 = nullptr;
    std::shared_ptr<core::CTexture> mTextureBox2 = nullptr;
    std::shared_ptr<core::CTexture> mTextureBox3 = nullptr;
    std::shared_ptr<core::CTexture> mTextureBox4 = nullptr;
    std::shared_ptr<core::CTexture> mTextureBox5 = nullptr;
    std::shared_ptr<core::CTexture> mTextureBox6 = nullptr;

    core::CMash* mCubeRound = nullptr;

    GLuint m_vao = 0;

public:
    void ReleaseGL()
    {
        delete mCubeRound;

        mTextureBox1.reset();
        mTextureBox2.reset();
        mTextureBox3.reset();
        mTextureBox4.reset();
        mTextureBox5.reset();
        mTextureBox6.reset();

        core::release();
    }

    void InitializeGL()
    {
        core::object("camera") //
            .Camera(core::CCamera::TRadius { 5.0f })
            .Camera(core::CCamera::TRotate { 45.0f, 45.0f })
            .Apply();

        core::object("perspective") //
            .Perspective(45.0f, SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f)
            .Apply();

        core::object("shader_texture")
            .Camera(core::object("camera"))
            .Perspective(core::object("perspective"))
            .Shader(RESOURCES "shaders/pos3tex2.vert")
            .Shader(RESOURCES "shaders/pos3tex2.frag")
            .Apply();

        core::object("shader_color")
            .Camera(core::object("camera"))
            .Perspective(core::object("perspective"))
            .Shader(RESOURCES "shaders/pos3col3.vert")
            .Shader(RESOURCES "shaders/pos3col3.frag")
            .Apply();

        core::object("shader_background")
            .Camera()
            .Perspective(core::object("perspective"))
            .Shader(RESOURCES "shaders/pos3tex2.vert")
            .Shader(RESOURCES "shaders/pos3tex2.frag")
            .Apply();

        core::object("cube_center")
            .VAO()
            .VBO(RESOURCES "vertex/cube.xyz")
            .TBO(RESOURCES "vertex/cube.st")
            .EBO(RESOURCES "vertex/cube.index")
            .Texture(RESOURCES "textures/box/1.bmp")
            .Matrix()
            .Translate(-0.5, -0.5, 0.5)
            .Rotate()
            .Scale()
            .Elements(GL_TRIANGLES, 36)
            .Shader(core::object("shader_texture"))
            .Apply();

        core::object("coordinate")
            .VAO()
            .Buffer(RESOURCES "vertex/coordinate.xyzrgb")
            .Arrays(GL_LINES, 0, 6)
            .Shader(core::object("shader_color"))
            .Matrix()
            .Apply();

        float vBackground[] = {
            0.0f, 0.0f, 0.0f, //
            0.0f, 1.0f, 0.0f, //
            1.0f, 1.0f, 0.0f, //
            1.0f, 0.0f, 0.0f, //
        };

        float tBackground[] = {
            0.0f, 0.0f, //
            0.0f, 1.0f, //
            1.0f, 1.0f, //
            1.0f, 0.0f, //
        };

        core::object("background")
            .VAO()
            .Texture(RESOURCES "textures/starsky.bmp")
            .VBO(vBackground, sizeof(vBackground) / sizeof(vBackground[0]))
            .TBO(tBackground, sizeof(tBackground) / sizeof(tBackground[0]))
            .Shader(core::object("shader_background"))
            .Arrays(GL_TRIANGLE_FAN, 0, 4)
            .Matrix()
            .Scale(110.0f)
            .Translate(-55.0f, -55.0, -95.0f)
            .Apply();

        CResource R;
        CResource RV;
        CResource RI;
        GLenum result = 0;
        TBMPHeader* bmp = nullptr;

        result = R.Load(RESOURCES "textures/box/1.bmp");
        if(result != 0)
            throw std::runtime_error("error: to load texture: " + R.GetPathFile());

        bmp = R.GetRaw<TBMPHeader>();
        if(bmp == nullptr)
            throw std::runtime_error("error: bring bmp");

        mTextureBox1 = std::make_shared<core::CTexture>();
        mTextureBox1->Bind();
        mTextureBox1->Create(R.GetRaw<GLubyte>(), bmp->Width, bmp->Height, bmp->DataOffset, bmp->Bits_Per_Pixel);
        mTextureBox1->ParamBase();
        mTextureBox1->UnBind();

        // ---------------------------------------------------------------

        result = R.Load(RESOURCES "textures/box/2.bmp");
        if(result != 0)
            throw std::runtime_error("error: to load texture: " + R.GetPathFile());

        bmp = R.GetRaw<TBMPHeader>();
        if(bmp == nullptr)
            throw std::runtime_error("error: bring bmp");

        mTextureBox2 = std::make_shared<core::CTexture>();
        mTextureBox2->Bind();
        mTextureBox2->Create(R.GetRaw<GLubyte>(), bmp->Width, bmp->Height, bmp->DataOffset, bmp->Bits_Per_Pixel);
        mTextureBox2->ParamBase();
        mTextureBox2->UnBind();

        // ---------------------------------------------------------------

        result = R.Load(RESOURCES "textures/box/3.bmp");
        if(result != 0)
            throw std::runtime_error("error: to load texture: " + R.GetPathFile());

        bmp = R.GetRaw<TBMPHeader>();
        if(bmp == nullptr)
            throw std::runtime_error("error: bring bmp");

        mTextureBox3 = std::make_shared<core::CTexture>();
        mTextureBox3->Bind();
        mTextureBox3->Create(R.GetRaw<GLubyte>(), bmp->Width, bmp->Height, bmp->DataOffset, bmp->Bits_Per_Pixel);
        mTextureBox3->ParamBase();
        mTextureBox3->UnBind();

        // ---------------------------------------------------------------

        result = R.Load(RESOURCES "textures/box/4.bmp");
        if(result != 0)
            throw std::runtime_error("error: to load texture: " + R.GetPathFile());

        bmp = R.GetRaw<TBMPHeader>();
        if(bmp == nullptr)
            throw std::runtime_error("error: bring bmp");

        mTextureBox4 = std::make_shared<core::CTexture>();
        mTextureBox4->Bind();
        mTextureBox4->Create(R.GetRaw<GLubyte>(), bmp->Width, bmp->Height, bmp->DataOffset, bmp->Bits_Per_Pixel);
        mTextureBox4->ParamBase();
        mTextureBox4->UnBind();

        // ---------------------------------------------------------------

        result = R.Load(RESOURCES "textures/box/5.bmp");
        if(result != 0)
            throw std::runtime_error("error: to load texture: " + R.GetPathFile());

        bmp = R.GetRaw<TBMPHeader>();
        if(bmp == nullptr)
            throw std::runtime_error("error: bring bmp");

        mTextureBox5 = std::make_shared<core::CTexture>();
        mTextureBox5->Bind();
        mTextureBox5->Create(R.GetRaw<GLubyte>(), bmp->Width, bmp->Height, bmp->DataOffset, bmp->Bits_Per_Pixel);
        mTextureBox5->ParamBase();
        mTextureBox5->UnBind();

        // ---------------------------------------------------------------

        result = R.Load(RESOURCES "textures/box/6.bmp");
        if(result != 0)
            throw std::runtime_error("error: to load texture: " + R.GetPathFile());

        bmp = R.GetRaw<TBMPHeader>();
        if(bmp == nullptr)
            throw std::runtime_error("error: bring bmp");

        mTextureBox6 = std::make_shared<core::CTexture>();
        mTextureBox6->Bind();
        mTextureBox6->Create(R.GetRaw<GLubyte>(), bmp->Width, bmp->Height, bmp->DataOffset, bmp->Bits_Per_Pixel);
        mTextureBox6->ParamBase();
        mTextureBox6->UnBind();

        result = RV.Load(RESOURCES "vertex/box.xyzst", 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + RV.GetPathFile());

        result = RI.Load(RESOURCES "vertex/box.index", 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + R.GetPathFile());

        mCubeRound = new core::CMash();
        mCubeRound->Set<core::CVAO>(core::VAO);
        mCubeRound->Set<core::CBuffer>(core::Buffer, RV.GetData<GLfloat>(), RV.GetCount(), &core::xyzst);
        mCubeRound->Set<core::CEBO>(core::EBO, RI.GetData<GLfloat>(), RI.GetCount());
        mCubeRound->Set<core::CShaderProgram>(
            core::Shader, core::object("shader_texture").Get()->Get<core::CShaderProgram>(core::Shader));
        mCubeRound->Set<core::CPerspective>(
            core::Perspective, core::object("perspective").Get()->Get<core::CPerspective>(core::Perspective));
        mCubeRound->Set<core::CCamera>(core::Camera, core::object("camera").Get()->Get<core::CCamera>(core::Camera));
        mCubeRound->Set<core::CMatrix>(core::Matrix);
        mCubeRound->Set<core::CDrawElements>(core::Elements, GL_TRIANGLES, 6);
        mCubeRound->Set<core::CTranslate>(core::Translate);
        mCubeRound->Set<core::CRotate>(core::Rotate);
        mCubeRound->Apply();

        glEnable(GL_DEPTH_TEST);
    };

    void PaintGL()
    {
        glClearColor(0.3f, 0.8f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        GLfloat x = 0.0f;
        GLfloat y = 0.0f;

        for(int i = 0; i < 12; i++) {

            mCubeRound->Set<core::CTranslate>(core::Translate, x - 10.0, y - 10.0, - 10.0);
            mCubeRound->Update();

            mTextureBox1->Bind();
            mCubeRound->Draw((GLuint*)(0 * 6 * sizeuint));

            mTextureBox2->Bind();
            mCubeRound->Draw((GLuint*)(1 * 6 * sizeuint));

            mTextureBox3->Bind();
            mCubeRound->Draw((GLuint*)(2 * 6 * sizeuint));

            mTextureBox4->Bind();
            mCubeRound->Draw((GLuint*)(3 * 6 * sizeuint));

            mTextureBox5->Bind();
            mCubeRound->Draw((GLuint*)(4 * 6 * sizeuint));

            mTextureBox6->Bind();
            mCubeRound->Draw((GLuint*)(5 * 6 * sizeuint));

            if(x++ > 4) {
                x = 0.0f;
                y++;
            }
        }

        // mCubeRound->Set<core::CRotate>(core::Rotate, glm::degrees(glfwGetTime() * glm::radians(50.0f)), 0.5f, 1.0f, 0.0f);
        mCubeRound->Set<core::CRotate>(core::Rotate, glm::degrees(glfwGetTime()), 1.0f, 1.0f, 0.0f);

        core::draw();
    }

    void RefreshGL() // Change value
    {
        // core::object("cube_center")
        // .VBO(RESOURCES "vertex/cube.xyz")
        // .EBO(RESOURCES "vertex/cube.index")
        // .TBO(RESOURCES "vertex/cube.st")
        // .Update();

        CResource RV;
        CResource RI;
        GLenum result = 0;

        result = RV.Load(RESOURCES "vertex/box.xyzst", 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + RV.GetPathFile());

        result = RI.Load(RESOURCES "vertex/box.index", 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + RI.GetPathFile());

        mCubeRound->Set<core::CEBO>(core::EBO, RI.GetData<GLuint>(), RI.GetCount());
        mCubeRound->Set<core::CBuffer>(core::Buffer, RV.GetData<GLfloat>(), RV.GetCount());
        mCubeRound->Update();
    }

    void ModeGL()
    {
        core::Mode(mMode++);
    }

    void ResizeGL(int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void SetMouseLeftPressed(const bool& value)
    {
        mMouseLeftPressed = value;
    }

    void SetMouseRightPressed(const bool& value)
    {
        mMouseRightPressed = value;
    }

    void CenterGL()
    {
        core::object("camera").Camera(core::CCamera::TCentre { 0.0f, 0.0f, 0.0f }).Update();
    }

    void RefreshMouseGL(const GLfloat& xPosition, const GLfloat& yPosition)
    {
        if(mMouseLeftPressed == true) {

            GLfloat pitch = (yPosition - mYPosition) / 10.0f;
            GLfloat yaw = (mXPosition - xPosition) / 10.0f;

            core::object("camera").Camera(core::CCamera::TRotate { pitch, yaw }).Update();
        }

        if(mMouseRightPressed == true) {

            GLfloat moveX = (xPosition - mXPosition) / 10.0F;
            GLfloat moveZ = (mYPosition - yPosition) / 10.0F;

            core::object("camera").Camera(core::CCamera::TMoveXZ { moveX, moveZ }).Update();
        }

        mXPosition = xPosition;
        mYPosition = yPosition;
    }
};

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

    std::string title = "Round Cube OpenGL Core Profile";

    result = glfwInit();
    if(result == GLFW_TRUE) {

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, title.data(), nullptr, nullptr);
        if(window != nullptr) {

            glfwSetWindowUserPointer(window, &process);

            glfwMakeContextCurrent(window);

            // make sure the viewport matches the new window dimensions;
            // note that width and height will be significantly larger than specified on retina displays.
            glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int w, int h) {
                CProcess* process = static_cast<CProcess*>(glfwGetWindowUserPointer(window));
                if(process != nullptr) {
                    process->ResizeGL(w, h);
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
                        process->RefreshGL();
                    } else if(key == GLFW_KEY_T && action == GLFW_PRESS) {
                        process->CenterGL();
                    } else if(key == GLFW_KEY_F4 && action == GLFW_PRESS) {
                        process->ModeGL();
                    }
                }
            });

            core::Init(window);
            core::Version();

            process.InitializeGL();

            while(!glfwWindowShouldClose(window)) {

                std::this_thread::sleep_for(std::chrono::milliseconds(1));

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