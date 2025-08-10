#include "core/object/vbo.h"

#include <GL/glew.h>

#include "core/error.h"

namespace core
{
    CVBO::CVBO()
        : CData(nullptr, 0)
        , m_vertex_buffer_object(0)
    {
        e(glGenBuffers(1, &m_vertex_buffer_object)); // return void
    }

    CVBO::CVBO(const GLvoid* data, const GLsizei& size)
        : CData(data, size)
        , m_vertex_buffer_object(0)
    {
        e(glGenBuffers(1, &m_vertex_buffer_object)); // return void
    }

    CVBO::~CVBO()
    {
        e(glDeleteBuffers(1, &m_vertex_buffer_object)); // return void
    }

    GLvoid CVBO::init(Node* node)
    {
        CVBO::Bind();

        e(glBufferData(GL_ARRAY_BUFFER, m_size * sizefloat, m_data, GL_STATIC_DRAW));

        if(node != nullptr)
            node->Init();

        CVBO::UnBind();
    }

    GLvoid CVBO::init(const GLint& param, Node* node)
    {
        CVBO::Bind();

        e(glBufferData(GL_ARRAY_BUFFER, m_size * sizefloat, m_data, GL_STATIC_DRAW));

        if(node != nullptr)
            node->Init(param);

        CVBO::UnBind();
    }

    GLvoid CVBO::init(glm::mat4& transform, Node* node)
    {
        throw std::runtime_error("error: wrong call: GLvoid CVBO::init(glm::mat4& transform, Node* node)");
    }

    GLvoid CVBO::draw(Node* node)
    {
        e(glEnableClientState(GL_VERTEX_ARRAY));

        CVBO::Bind();

        e(glVertexPointer(3, GL_FLOAT, 0, nullptr));

        if(node != nullptr)
            node->Draw();

        e(glDisableClientState(GL_VERTEX_ARRAY));
    }

    GLvoid CVBO::draw(const GLuint* array, Node* node)
    {
        e(glEnableClientState(GL_VERTEX_ARRAY));

        CVBO::Bind();

        e(glVertexPointer(3, GL_FLOAT, 0, nullptr));

        if(node != nullptr)
            node->Draw(array);

        e(glDisableClientState(GL_VERTEX_ARRAY));
    }

    GLvoid CVBO::draw(const GLuint& shader_program, Node* node)
    {
        throw std::runtime_error("error: wrong call: GLvoid CVBO::draw(const GLuint& shader_program, Node* node)");
    }

    GLvoid CVBO::draw(const GLuint& shader_program, const GLuint* array, Node* node)
    {
        throw std::runtime_error("error: wrong call: GLvoid CVBO::draw(const GLuint& shader_program, const GLuint* array, Node* node)");
    }

    GLvoid CVBO::update(Node* node)
    {
    }

    GLvoid CVBO::update(glm::mat4& transform, Node* node)
    {
    }

    GLvoid CVBO::Bind()
    {
        e(glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_object)); // return void
    }

    GLvoid CVBO::UnBind()
    {
        e(glBindBuffer(GL_ARRAY_BUFFER, 0)); // return void
    }

    GLuint CVBO::Get()
    {
        return m_vertex_buffer_object;
    }
}