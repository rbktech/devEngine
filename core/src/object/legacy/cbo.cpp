#include "core/object/cbo.h"

#include <GL/glew.h>

#include "core/error.h"

namespace core
{
    CCBO::CCBO()
        : CData(nullptr, 0)
        , m_color_buffer_object(0)
    {
        e(glGenBuffers(1, &m_color_buffer_object));
    }

    CCBO::CCBO(const GLvoid* data, const GLsizei& size)
        : CData(data, size)
        , m_color_buffer_object(0)
    {
        e(glGenBuffers(1, &m_color_buffer_object));
    }

    CCBO::~CCBO()
    {
        e(glDeleteBuffers(1, &m_color_buffer_object));
    }

    GLvoid CCBO::init(Node* node)
    {
        CCBO::Bind();

        e(glBufferData(GL_ARRAY_BUFFER, m_size * sizefloat, m_data, GL_STATIC_DRAW));

        if(node != nullptr)
            node->Init();

        CCBO::UnBind();
    }

    GLvoid CCBO::init(const GLint& param, Node* node)
    {
        CCBO::Bind();

        e(glBufferData(GL_ARRAY_BUFFER, m_size * sizefloat, m_data, GL_STATIC_DRAW));

        if(node != nullptr)
            node->Init(param);

        CCBO::UnBind();
    }

    GLvoid CCBO::init(glm::mat4& transform, Node* node)
    {
        throw std::runtime_error("error: wrong call: GLvoid CCBO::init(glm::mat4& transform, Node* node)");
    }

    GLvoid CCBO::draw(Node* node)
    {
        e(glEnableClientState(GL_COLOR_ARRAY));

        CCBO::Bind();

        glColorPointer(3, GL_FLOAT, 0, nullptr);

        if(node != nullptr)
            node->Draw();

        e(glDisableClientState(GL_COLOR_ARRAY));
    }

    GLvoid CCBO::draw(const GLuint* array, Node* node)
    {
        e(glEnableClientState(GL_COLOR_ARRAY));

        CCBO::Bind();

        glColorPointer(3, GL_FLOAT, 0, nullptr);

        if(node != nullptr)
            node->Draw(array);

        e(glDisableClientState(GL_COLOR_ARRAY));
    }

    GLvoid CCBO::draw(const GLuint& shader_program, Node* node)
    {
    }

    GLvoid CCBO::draw(const GLuint& shader_program, const GLuint* array, Node* node)
    {
    }

    GLvoid CCBO::update(Node* node)
    {
    }

    GLvoid CCBO::update(glm::mat4& transform, Node* node)
    {
    }

    GLvoid CCBO::Bind()
    {
        e(glBindBuffer(GL_ARRAY_BUFFER, m_color_buffer_object));
    }

    GLvoid CCBO::UnBind()
    {
        e(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    GLuint CCBO::Get()
    {
        return m_color_buffer_object;
    }
}