#include "core/object/bbo.h"

#include <GL/glew.h>

#include "core/error.h"

namespace core
{
    CBBO::CBBO()
        // : m_type(0)
        // , m_first(0)
        // , m_size(0)
        // , m_x(0)
        // , m_y(0)
    // , m_z(0)
    {
    }

    GLvoid CBBO::DrawArray()
    {
        /*e(glPushMatrix());

        e(glTranslatef(m_x, m_y, m_z));

        e(glDrawArrays(m_type, m_first, m_size)); // return void

        e(glPopMatrix());*/
    }

    GLvoid CBBO::DrawElement(const void* indices)
    {
        /*e(glPushMatrix());

        e(glTranslatef(m_x, m_y, m_z));

        e(glDrawElements(m_type, m_size, GL_UNSIGNED_INT, indices)); // return void

        e(glPopMatrix());*/
    }

    GLvoid CBBO::SetDrawCoordinate(const GLfloat& x, const GLfloat& y, const GLfloat& z)
    {
        // m_x = x;
        // m_y = y;
        // m_z = z;
    }

    GLvoid CBBO::SetDrawArray(const GLenum& type, const GLsizei& first, const GLsizei& size)
    {
        // m_type = type;
        // m_size = size;
        // m_first = first;
    }

    GLvoid CBBO::SetDrawElement(const GLenum& type, const GLsizei& size)
    {
        // m_type = type;
        // m_size = size;
    }

    GLvoid CBBO::Reset()
    {
    }
}