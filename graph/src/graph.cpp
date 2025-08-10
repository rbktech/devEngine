#include "graph/graph.h"

#include <GL/gl.h>

#include <core/core.h>

#define rgb(x) (x / 255.0F)

extern const char binary_shaders_pos3col3_vert_start[];
extern const char binary_shaders_pos3col3_vert_end[];

extern const char binary_shaders_pos3col3_frag_start[];
extern const char binary_shaders_pos3col3_frag_end[];

extern const float binary_vertex_coordinate_xyz_start[];
extern const float binary_vertex_coordinate_xyz_end[];

extern const float binary_vertex_coordinate_rgb_start[];
extern const float binary_vertex_coordinate_rgb_end[];

extern const float binary_vertex_cursor_xyz_start[];
extern const float binary_vertex_cursor_xyz_end[];

extern const float binary_vertex_cursor_rgb_start[];
extern const float binary_vertex_cursor_rgb_end[];

namespace graph
{
    CGraph::CGraph()
        : mInit(0)
        , mBackground(1.0f)
        , mScreenWidth(1.0f)
        , mScreenHeight(1.0f)
        , mZoom(1.0f)
        , mX(100)
        , mY(100)
    {
    }

    CGraph::~CGraph()
    {
        core::release();
    }

    void CGraph::Init(const GLfloat& screenWidth, const GLfloat& screenHeight)
    {
        core::Init(nullptr);

        core::object("shader")
            .Shader(                                                                   //
                binary_shaders_pos3col3_vert_start,                                    //
                binary_shaders_pos3col3_vert_end - binary_shaders_pos3col3_vert_start, //
                core::CShader::Vertex)
            .Shader(                                                                   //
                binary_shaders_pos3col3_frag_start,                                    //
                binary_shaders_pos3col3_frag_end - binary_shaders_pos3col3_frag_start, //
                core::CShader::Fragment)
            .Apply();

        core::object("projection") //
            .Orthographic(-50.0f, -50.0f + screenWidth, -50.0f, -50.0f + screenHeight, -1.0f, 1.0f)
            .Apply();

        core::object("cursor_projection") //
            .Orthographic(-50.0f, -50.0f + screenWidth, -50.0f, -50.0f + screenHeight, -1.0f, 1.0f)
            .Apply();

        core::object("coordinate") //
            .VAO()
            .VBO(                                                                      //
                binary_vertex_coordinate_xyz_start,                                    //
                binary_vertex_coordinate_xyz_end - binary_vertex_coordinate_xyz_start) //
            .CBO(                                                                      //
                binary_vertex_coordinate_rgb_start,                                    //
                binary_vertex_coordinate_rgb_end - binary_vertex_coordinate_rgb_start) //
            .Orthographic(core::object("projection"))
            .Shader(core::object("shader"))
            .Matrix()
            .Arrays(GL_LINES, 0, 4)
            .Apply();

        core::object("cursor") //
            .VAO()
            .VBO(                                                              //
                binary_vertex_cursor_xyz_start,                                //
                binary_vertex_cursor_xyz_end - binary_vertex_cursor_xyz_start) //
            .CBO(                                                              //
                binary_vertex_cursor_rgb_start,                                //
                binary_vertex_cursor_rgb_end - binary_vertex_cursor_rgb_start) //
            .Orthographic(core::object("cursor_projection"))
            .Shader(core::object("shader"))
            .Matrix()
            .Translate()
            .Arrays(GL_LINES, 0, 4)
            .Apply();

        this->SetSize(screenWidth, screenHeight);

        mInit = 1;
    }

    void CGraph::SetBackground(const float& r, const float& g, const float& b, const float& a)
    {
        mBackground = { rgb(r), rgb(g), rgb(b), rgb(a) };
    }

    void CGraph::SetGrid(const GLint& x, const GLint& y)
    {
        mX = x;
        mY = y;
    }

    void CGraph::Create(const std::string& name)
    {
        core::object(name) //
            .VAO()
            .VBO(nullptr, mX * 3)
            .CBO(nullptr, 1)
            .Orthographic(core::object("projection"))
            .Shader(core::object("shader"))
            .Matrix()
            .Arrays(GL_LINE_STRIP, 0, mX)
            .Apply();
    }

    void CGraph::Set(const std::string& name, const float* data, const int& size)
    {
        core::object(name) //
            .VBO(data, size)
            .Update();
    }

    void CGraph::Set(const std::string& name, const glm::vec3& color)
    {
        float* data = new float[mX * 3] { color.r, color.g, color.b };

        for(int i = 0; i < mX; i++)
            memcpy(&data[i * 3], &color, sizefloat * 3);

        core::object(name) //
            .CBO(data, mX * 3)
            .Update();

        delete[] data;
    }

    void CGraph::Draw()
    {
        e(glClearColor(mBackground.r, mBackground.g, mBackground.b, mBackground.a));
        e(glClear(GL_COLOR_BUFFER_BIT));

        if(mInit == 1) {
            core::draw();
        }
    }

    void CGraph::Scroll(const GLfloat& xOffset, const GLfloat& yOffset)
    {
        GLfloat zoom = mZoom + yOffset / 10.0f;
        if(zoom > 0.01)
            mZoom = zoom;

        core::COrthographic::TScale scale { yOffset * 10.0f };

        core::object("projection").Orthographic(scale).Update();
    }

    void CGraph::Move(const GLfloat& xPosition, const GLfloat& yPosition)
    {
        core::COrthographic::TMoveXY move;

        move.x = xPosition * mZoom;
        move.y = yPosition * mZoom;

        core::object("projection").Orthographic(move).Update();
        core::object("cursor_projection").Orthographic(move).Update();
    }

    void CGraph::Cursor(const float& xPos, const float& yPos, float& xReal, float& yReal)
    {
        std::shared_ptr<core::COrthographic> pOrthographic = nullptr;

        pOrthographic = core::object("projection").Get()->Get<core::COrthographic>(core::Orthographic);
        if(pOrthographic != nullptr) {

            GLfloat ndcX = (2.0f * xPos) / mScreenWidth - 1.0f;
            GLfloat ndcY = 1.0f - (2.0f * yPos) / mScreenHeight;

            glm::vec4 rayCentreNDC(ndcX, ndcY, 0.0f, 1.0f); // z = 1 (дальняя плоскость)

            glm::mat4 inverse = glm::inverse(pOrthographic->GetMatrix());

            glm::vec3 rayCentreWorld = inverse * rayCentreNDC;

            xReal = rayCentreWorld.x;
            yReal = rayCentreWorld.y;
        }

        pOrthographic = core::object("cursor_projection").Get()->Get<core::COrthographic>(core::Orthographic);
        if(pOrthographic != nullptr) {

            GLfloat ndcX = (2.0f * xPos) / mScreenWidth - 1.0f;
            GLfloat ndcY = 1.0f - (2.0f * yPos) / mScreenHeight;

            glm::vec4 rayCentreNDC(ndcX, ndcY, 0.0f, 1.0f); // z = 0 (Центральная плоскость)

            glm::mat4 inverse = glm::inverse(pOrthographic->GetMatrix());

            glm::vec3 rayCentreWorld = inverse * rayCentreNDC;

            core::object("cursor").Translate(rayCentreWorld.x, rayCentreWorld.y).Update();
        }
    }

    void CGraph::SetSize(const GLfloat& screenWidth, const GLfloat& screenHeight)
    {
        mScreenWidth = screenWidth;
        mScreenHeight = screenHeight;

        core::object("projection") //
            .Orthographic(core::COrthographic::TSize { mScreenWidth, mScreenHeight })
            .Update();

        core::object("cursor_projection") //
            .Orthographic(core::COrthographic::TSize { mScreenWidth, mScreenHeight })
            .Update();

        glViewport(0, 0, mScreenWidth, mScreenHeight);
    }
}