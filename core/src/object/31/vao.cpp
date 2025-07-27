#include "core/31/vao.h"

#include <GL/glew.h>

#include "core/error.h"

namespace core
{
    CVAO::CVAO()
        : m_type(0)
        , m_first(0)
        , m_size(0)
        , m_show(false)
        , m_vertex_array_object_names(0)
        , m_x(0.0f)
        , m_y(0.0f)
        , m_z(0.0f)
    {
        e(glGenVertexArrays(1, &m_vertex_array_object_names)) // return void
    }

    CVAO::~CVAO()
    {
        e(glDeleteVertexArrays(1, &m_vertex_array_object_names))
    }

    GLvoid CVAO::SetDrawParams(const GLenum &type, const GLint &first, const GLsizei &size)
    {
        m_type = type;
        m_first = first;
        m_size = size;
    }

    GLvoid CVAO::SetDrawCoordinate(const GLfloat& x, const GLfloat& y, const GLfloat& z)
    {
        m_x = x;
        m_y = y;
        m_z = z;
    }

    GLvoid CVAO::Bind()
    {
        e(glBindVertexArray(m_vertex_array_object_names));
    }

    GLvoid CVAO::UnBind()
    {
        e(glBindVertexArray(0));
    }

    /*GLvoid CVAO::Draw()
{
    e(glPushMatrix());

    // e(glBindVertexArray(m_vertex_array_object));

    CVAO::Bind();

    e(glTranslatef(m_x, m_y, m_z));

    e(glDrawArrays(m_type, m_first, m_size)); // return void

    // e(glBindBuffer(GL_ARRAY_BUFFER, 0));

    // e(glBindVertexArray(0));

    e(glPopMatrix());

    // e(glFlush());
}*/

    GLvoid CVAO::Draw()
    {
        e(glPushMatrix());

        // e(glBindVertexArray(m_vertex_array_object_names));

        CVAO::Bind();

        e(glTranslatef(m_x, m_y, m_z));

        e(glDrawArrays(m_type, m_first, m_size)); // return void

        // e(glBindBuffer(GL_ARRAY_BUFFER, 0));

        // e(glBindVertexArray(0));

        e(glPopMatrix());

        // e(glFlush());
    }

    GLboolean CVAO::IsShow()
    {
        return m_show;
    }

    GLvoid CVAO::IsShow(GLboolean value)
    {
        m_show = value;
    }

    GLvoid CVAO::draw(const GLuint* array, Node* node)
    {
        CVAO::Bind();
        CBBO::Next(array);
        CVAO::UnBind();
    }

    // -----------------------------------------------------------------------

    CVAOBuffer::CVAOBuffer()
        : m_buffer_object_name(0)
    {
        e(glGenBuffers(1, &m_buffer_object_name)); // return void
    }

    CVAOBuffer::~CVAOBuffer()
    {
        e(glDeleteBuffers(1, &m_buffer_object_name)); // return void
    }

    GLvoid CVAOBuffer::SetBuffer(const GLfloat* buffer, const GLsizei& size)
    {
        e(glBindVertexArray(m_vertex_array_object));
        {
            e(glBindBuffer(GL_ARRAY_BUFFER, m_buffer_object_name)); // return void
            {
                e(glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), buffer, GL_STATIC_DRAW)); // return void
            }

            e(glBindVertexArray(0));
        }
    }

    GLvoid CVAOBuffer::EnableVertex(const GLint& nCoordinates, const GLsizei& stride, const GLint& beginByte)
    {
        e(glBindVertexArray(m_vertex_array_object));
        {
            e(glBindBuffer(GL_ARRAY_BUFFER, m_buffer_object_name));
            {
                e(glVertexPointer(nCoordinates, GL_FLOAT, (GLsizei)(stride * sizeof(GLfloat)), (GLvoid*)(beginByte * sizeof(GLfloat)))); // return void

                e(glEnableClientState(GL_VERTEX_ARRAY));
            }

            e(glBindVertexArray(0));
        }
    }

    GLvoid CVAOBuffer::EnableColor(const GLint& nColor, const GLsizei& stride, const GLint& beginByte)
    {
        e(glBindVertexArray(m_vertex_array_object));
        {
            e(glBindBuffer(GL_ARRAY_BUFFER, m_buffer_object_name));
            {
                e(glColorPointer(nColor, GL_FLOAT, (GLsizei)(stride * sizeof(GLfloat)), (GLvoid*)(beginByte * sizeof(GLfloat)))); // return void

                e(glEnableClientState(GL_COLOR_ARRAY));
            }

            e(glBindVertexArray(0));
        }
    }

    // -----------------------------------------------------------------------

    CVAOParams::CVAOParams()
        : m_buffer_object_name_vertex(0)
        , m_buffer_object_name_color(0)
    {
        e(glGenBuffers(1, &m_buffer_object_name_vertex)); // return void
        e(glGenBuffers(1, &m_buffer_object_name_color));  // return void
    }

    CVAOParams::~CVAOParams()
    {
        e(glDeleteBuffers(1, &m_buffer_object_name_vertex)); // return void
        e(glDeleteBuffers(1, &m_buffer_object_name_vertex)); // return void
    }

    GLvoid CVAOParams::SetBufferVertex(const GLfloat* buffer, const GLsizei& size, const GLsizei& nCoordinates)
    {
        e(glBindVertexArray(m_vertex_array_object));
        {
            e(glBindBuffer(GL_ARRAY_BUFFER, m_buffer_object_name_vertex));
            {
                e(glVertexPointer(nCoordinates, GL_FLOAT, 0, nullptr));
                e(glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), buffer, GL_STATIC_DRAW));
                e(glEnableClientState(GL_VERTEX_ARRAY));
            }
            e(glBindVertexArray(0));
        }
    }

    GLvoid CVAOParams::SetBufferColor(const GLfloat* buffer, const GLsizei& size, const GLsizei& nColors)
    {
        e(glBindVertexArray(m_vertex_array_object));
        {
            e(glBindBuffer(GL_ARRAY_BUFFER, m_buffer_object_name_color));
            {
                e(glColorPointer(nColors, GL_FLOAT, 0, nullptr));
                e(glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), buffer, GL_STATIC_DRAW));
                e(glEnableClientState(GL_COLOR_ARRAY));
            }
            e(glBindVertexArray(0));
        }
    }

    // -----------------------------------------------------------------------

    CVAOFull::CVAOFull()
        : m_buffer_object_name(0)
    {
        e(glGenBuffers(1, &m_buffer_object_name)); // return void
    }

    CVAOFull::~CVAOFull()
    {
        e(glDeleteBuffers(1, &m_buffer_object_name)); // return void
    }

    GLvoid CVAOFull::Set(const GLfloat* buffer,
        const GLsizei& size,
        const GLint& nCoordinates,
        const GLsizei& strideCoordinates,
        const GLint& beginByteCoordinates,
        const GLint& nColors,
        const GLsizei& strideColors,
        const GLint& beginByteColors)
    {
        e(glBindVertexArray(m_vertex_array_object));
        {
            e(glBindBuffer(GL_ARRAY_BUFFER, m_buffer_object_name));
            {
                e(glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), buffer, GL_STATIC_DRAW));

                e(glVertexPointer(nCoordinates, GL_FLOAT, (GLsizei)(strideCoordinates * sizeof(GLfloat)),
                    (GLvoid*)(beginByteCoordinates * sizeof(GLfloat)))); // return void

                e(glEnableClientState(GL_VERTEX_ARRAY));

                e(glColorPointer(nColors, GL_FLOAT, (GLsizei)(strideColors * sizeof(GLfloat)),
                    (GLvoid*)(beginByteColors * sizeof(GLfloat)))); // return void

                e(glEnableClientState(GL_COLOR_ARRAY));
            }

            e(glBindVertexArray(0));
        }
    }
}