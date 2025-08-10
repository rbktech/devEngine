#include "core/object/tbo.h"

#include <GL/glew.h>

#include "core/error.h"

namespace core
{
    CTBO::CTBO()
        : CData(nullptr, 0)
        , m_texture_buffer_object(0)
    {
        e(glGenBuffers(1, &m_texture_buffer_object));
    }

    CTBO::CTBO(const GLvoid* data, const GLsizei& size)
        : CData(data, size)
        , m_texture_buffer_object(0)
    {
        e(glGenBuffers(1, &m_texture_buffer_object));
    }

    CTBO::~CTBO()
    {
        e(glDeleteBuffers(1, &m_texture_buffer_object));
    }

    GLvoid CTBO::init(Node* node)
    {
        CTBO::Bind();

        e(glBufferData(GL_ARRAY_BUFFER, m_size * sizefloat, m_data, GL_STATIC_DRAW));

        e(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr));
        e(glEnableVertexAttribArray(0));

        if(node != nullptr)
            node->Init();

        CTBO::UnBind();
    }

    GLvoid CTBO::init(const GLint& param, Node* node)
    {
        CTBO::Bind();

        e(glBufferData(GL_ARRAY_BUFFER, m_size * sizefloat, m_data, GL_STATIC_DRAW));

        e(glVertexAttribPointer(param, 2, GL_FLOAT, GL_FALSE, 0, nullptr));
        e(glEnableVertexAttribArray(param));

        if(node != nullptr)
            node->Init(param + 1);

        CTBO::UnBind();
    }

    GLvoid CTBO::init(glm::mat4& transform, Node* node)
    {
        CTBO::Bind();

        e(glBufferData(GL_ARRAY_BUFFER, m_size * sizefloat, m_data, GL_STATIC_DRAW));

        e(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr));
        e(glEnableVertexAttribArray(0));

        if(node != nullptr)
            node->Init(transform);

        CTBO::UnBind();
    }

    GLvoid CTBO::draw(Node* node)
    {
        if(node != nullptr)
            node->Draw();
    }

    GLvoid CTBO::draw(const GLuint* array, Node* node)
    {
        if(node != nullptr)
            node->Draw(array);
    }

    GLvoid CTBO::draw(const GLuint& shader_program, Node* node)
    {
        if(node != nullptr)
            node->Draw(shader_program);
    }

    GLvoid CTBO::draw(const GLuint& shader_program, const GLuint* array, Node* node)
    {
        if(node != nullptr)
            node->Draw(shader_program, array);
    }

    GLvoid CTBO::update(Node* node)
    {
        CTBO::Update();

        if(node != nullptr)
            node->Update();
    }

    GLvoid CTBO::update(glm::mat4& transform, Node* node)
    {
        CTBO::Update();

        if(node != nullptr)
            node->Update(transform);
    }

    GLvoid CTBO::Bind()
    {
        e(glBindBuffer(GL_ARRAY_BUFFER, m_texture_buffer_object));
    }

    GLvoid CTBO::UnBind()
    {
        e(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    GLuint CTBO::Get()
    {
        return m_texture_buffer_object;
    }

    GLvoid CTBO::Update()
    {
        if(m_data != nullptr && m_size > 0) {

            CTBO::Bind();

            e(glBufferData(GL_ARRAY_BUFFER, m_size * sizefloat, m_data, GL_STATIC_DRAW));

            CTBO::UnBind();
        }
    }

    GLvoid CTBO::Update(const GLuint& offset)
    {
        if(m_data != nullptr && m_size > 0) {

            CTBO::Bind();

            e(glBufferSubData(GL_ARRAY_BUFFER, offset, m_size * sizefloat, m_data));

            CTBO::UnBind();
        }
    }
}