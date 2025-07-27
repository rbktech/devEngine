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
        // : m_type(0)
        // , m_first(0)
        // , m_size(0)
        : CData(data, size)
        , m_vertex_buffer_object(0)
    {
        e(glGenBuffers(1, &m_vertex_buffer_object)); // return void
    }

    CVBO::~CVBO()
    {
        e(glDeleteBuffers(1, &m_vertex_buffer_object)); // return void
    }

    GLvoid CVBO::EnableVertex(const GLint& nCoord, const GLsizei& stride, const GLint& beginByte)
    {
        e(glVertexPointer(nCoord, GL_FLOAT, (GLsizei)(stride * sizeof(GLfloat)),
            (GLvoid*)(beginByte * sizeof(GLfloat)))); // return void

        e(glEnableClientState(GL_VERTEX_ARRAY));
    }

    GLvoid CVBO::EnableColor(const GLint& nColor, const GLsizei& stride, const GLint& beginByte)
    {
        e(glColorPointer(nColor, GL_FLOAT, (GLsizei)(stride * sizeof(GLfloat)),
            (GLvoid*)(beginByte * sizeof(GLfloat)))); // return void

        e(glEnableClientState(GL_COLOR_ARRAY));
    }

    GLvoid CVBO::EnableTexCoord(const GLint& nTexCoord, const GLsizei& stride, const GLint& beginByte)
    {
        e(glTexCoordPointer(nTexCoord, GL_FLOAT, (GLsizei)(stride * sizeof(GLfloat)),
            (GLvoid*)(beginByte * sizeof(GLfloat)))); // return void

        e(glEnableClientState(GL_TEXTURE_COORD_ARRAY));
    }

    GLvoid CVBO::DisableVertex()
    {
        glDisableClientState(GL_VERTEX_ARRAY);
    }

    GLvoid CVBO::DisableColor()
    {
        glDisableClientState(GL_COLOR_ARRAY);
    }

    GLvoid CVBO::DisableTexCoord()
    {
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }

    /*GLvoid CVBO::SetDrawParams(const GLenum& type, const GLint& first, const GLsizei& size)
    {
        m_type = type;
        m_first = first;
        m_size = size;
    }*/

    // -----------------------------------------------------------------------

    GLvoid CVBO::SetBuffer(const GLfloat* buffer, const GLsizei& size)
    {
        e(glBufferData(GL_ARRAY_BUFFER, size * sizefloat, buffer, GL_STATIC_DRAW)); // return void
    }

    /*GLvoid CVBO::Draw()
    {
        e(glDrawArrays(m_type, m_first, m_size)); // return void
    }*/

    // -------------------------------------------------------------------

    // Development

    GLvoid CVBO::Bind()
    {
        e(glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_object)); // return void
    }

    GLvoid CVBO::UnBind()
    {
        e(glBindBuffer(GL_ARRAY_BUFFER, 0)); // return void
    }

    GLvoid CVBO::init(Node* node)
    {
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
    }

    GLvoid CVBO::draw(Node* node)
    {
    }

    GLvoid CVBO::draw(const GLuint* array, Node* node)
    {
        e(glEnableClientState(GL_VERTEX_ARRAY));

        CVBO::Bind();

        e(glVertexPointer(2, GL_FLOAT, 0, nullptr));

        if(node != nullptr)
            node->Draw(array);

        e(glDisableClientState(GL_VERTEX_ARRAY));
    }

    GLvoid CVBO::draw(const GLuint& shader_program, Node* node)
    {
    }

    GLvoid CVBO::draw(const GLuint& shader_program, const GLuint* array, Node* node)
    {
    }

    GLuint CVBO::Get()
    {
        return m_vertex_buffer_object;
    }

    GLvoid CVBO::update(Node* node)
    {
    }

    GLvoid CVBO::update(glm::mat4& transform, Node* node)
    {
    }
}