#include "core/object/draw.h"

#include <GL/glew.h>

#include "core/error.h"

namespace core
{
    CDrawArrays::CDrawArrays()
        : m_type(0)
        , m_first(0)
        , m_size()
    {
    }

    CDrawArrays::CDrawArrays(const GLenum& type, const GLint& first, const GLsizei& size)
        : m_type(type)
        , m_first(first)
        , m_size(size)
    {
    }

    GLvoid CDrawArrays::init(Node* node)
    {
    }

    GLvoid CDrawArrays::init(const GLint& param, Node* node)
    {
    }

    GLvoid CDrawArrays::init(glm::mat4& transform, Node* node)
    {
    }

    GLvoid CDrawArrays::draw(Node* node)
    {
        e(glDrawArrays(m_type, m_first, m_size));
    }

    GLvoid CDrawArrays::draw(const GLuint* array, Node* node)
    {
        e(glDrawArrays(m_type, m_first, m_size));
    }

    GLvoid CDrawArrays::draw(const GLuint& shader_program, Node* node)
    {
        e(glDrawArrays(m_type, m_first, m_size));
    }

    GLvoid CDrawArrays::draw(const GLuint& shader_program, const GLuint* array, Node* node)
    {
        e(glDrawArrays(m_type, m_first, m_size));
    }

    GLvoid CDrawArrays::update(Node* node)
    {
    }

    GLvoid CDrawArrays::update(glm::mat4& transform, Node* node)
    {
    }

    GLvoid CDrawArrays::Bind()
    {
    }

    GLvoid CDrawArrays::UnBind()
    {
    }

    GLuint CDrawArrays::Get()
    {
        return 0;
    }

    GLvoid CDrawArrays::Set(const GLenum& type, const GLint& first, const GLsizei& size)
    {
        m_type = type;
        m_first = first;
        m_size = size;
    }

    GLvoid CDrawArrays::Set(const GLsizei& size)
    {
        m_size += size;
    }

    GLint CDrawArrays::Size()
    {
        return m_size;
    }
}

namespace core
{
    CDrawElements::CDrawElements()
        : m_type(0)
        , m_size()
    {
    }

    CDrawElements::CDrawElements(const GLenum& type, const GLsizei& size)
        : m_type(type)
        , m_size(size)
    {
    }

    GLvoid CDrawElements::init(Node* node)
    {
    }

    GLvoid CDrawElements::init(const GLint& param, Node* node)
    {
    }

    GLvoid CDrawElements::init(glm::mat4& transform, Node* node)
    {
    }

    GLvoid CDrawElements::draw(Node* node)
    {
        e(glDrawElements(m_type, m_size, GL_UNSIGNED_INT, nullptr));
    }

    GLvoid CDrawElements::draw(const GLuint* array, Node* node)
    {
        e(glDrawElements(m_type, m_size, GL_UNSIGNED_INT, array));
    }

    GLvoid CDrawElements::draw(const GLuint& shader_program, Node* node)
    {
        e(glDrawElements(m_type, m_size, GL_UNSIGNED_INT, nullptr));
    }

    GLvoid CDrawElements::draw(const GLuint& shader_program, const GLuint* array, Node* node)
    {
        e(glDrawElements(m_type, m_size, GL_UNSIGNED_INT, array));
    }

    GLvoid CDrawElements::update(Node* node)
    {
    }

    GLvoid CDrawElements::update(glm::mat4& transform, Node* node)
    {
    }

    GLvoid CDrawElements::Bind()
    {
    }

    GLvoid CDrawElements::UnBind()
    {
    }

    GLuint CDrawElements::Get()
    {
        return 0;
    }

    GLvoid CDrawElements::Set(const GLenum& type, const GLsizei& size)
    {
        m_type = type;
        m_size = size;
    }
}