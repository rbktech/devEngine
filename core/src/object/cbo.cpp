#include "core/object/cbo.h"

#include <GL/glew.h>

#include "core/error.h"

namespace core
{
    CCBO::CCBO()
        : CData(nullptr, 0)
        ,m_color_buffer_object(0)
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

        e(glBufferData(GL_ARRAY_BUFFER, m_size * sizefloat, m_data, GL_DYNAMIC_DRAW));

        e(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr));
        e(glEnableVertexAttribArray(0));

        if(node != nullptr)
            node->Init();

        CCBO::UnBind();
    }

    GLvoid CCBO::init(const GLint& param, Node* node)
    {
        CCBO::Bind();

        e(glBufferData(GL_ARRAY_BUFFER, m_size * sizefloat, m_data, GL_DYNAMIC_DRAW));

        e(glVertexAttribPointer(param, 3, GL_FLOAT, GL_FALSE, 0, nullptr));
        e(glEnableVertexAttribArray(param));

        if(node != nullptr)
            node->Init(param + 1);

        CCBO::UnBind();
    }

    GLvoid CCBO::init(glm::mat4& transform, Node* node)
    {
        CCBO::Bind();

        e(glBufferData(GL_ARRAY_BUFFER, m_size * sizefloat, m_data, GL_DYNAMIC_DRAW));

        e(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr));
        e(glEnableVertexAttribArray(0));

        if(node != nullptr)
            node->Init(transform);

        CCBO::UnBind();
    }

    GLvoid CCBO::draw(Node* node)
    {
        if(node != nullptr)
            node->Draw();
    }

    GLvoid CCBO::draw(const GLuint* array, Node* node)
    {
        if(node != nullptr)
            node->Draw(array);
    }

    GLvoid CCBO::draw(const GLuint& shader_program, Node* node)
    {
        if(node != nullptr)
            node->Draw(shader_program);
    }

    GLvoid CCBO::draw(const GLuint& shader_program, const GLuint* array, Node* node)
    {
        if(node != nullptr)
            node->Draw(shader_program, array);
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

    GLvoid CCBO::update(Node* node)
    {
        Update();

        if(node != nullptr)
            node->Update();
    }

    GLvoid CCBO::update(glm::mat4& transform, Node* node)
    {
        Update();

        if(node != nullptr)
            node->Update(transform);
    }

    GLvoid CCBO::Update()
    {
        if(m_data != nullptr && m_size > 0) {

            CCBO::Bind();

            e(glBufferData(GL_ARRAY_BUFFER, m_size * sizefloat, m_data, GL_STATIC_DRAW));

            CCBO::UnBind();
        }
    }

    GLvoid CCBO::Update(const GLuint& offset)
    {
        if(m_data != nullptr && m_size > 0) {

            CCBO::Bind();

            e(glBufferSubData(GL_ARRAY_BUFFER, offset, m_size * sizefloat, m_data));

            CCBO::UnBind();
        }
    }
}