#include "core/object/vbo.h"

#include <GL/glew.h>

#include "core/error.h"

namespace core
{
    CVBO::CVBO()
        : CData(nullptr, 0)
    {
        e(glGenBuffers(1, &m_vertex_buffer_object));
    }

    CVBO::~CVBO()
    {
        e(glDeleteBuffers(1, &m_vertex_buffer_object));
    }

    GLvoid CVBO::init(Node* node)
    {
        CVBO::Bind();

        e(glBufferData(GL_ARRAY_BUFFER, m_size * sizefloat, m_data, GL_STATIC_DRAW));

        e(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr));
        e(glEnableVertexAttribArray(0));

        if(node != nullptr)
            node->Init();

        // CVBO::UnBind();
    }

    GLvoid CVBO::init(const GLint& param, Node* node)
    {
        CVBO::Bind();

        e(glBufferData(GL_ARRAY_BUFFER, m_size * sizefloat, m_data, GL_STATIC_DRAW));

        e(glVertexAttribPointer(param, 3, GL_FLOAT, GL_FALSE, 0, nullptr));
        e(glEnableVertexAttribArray(param));

        if(node != nullptr)
            node->Init(param + 1);

        // CVBO::UnBind();
    }

    GLvoid CVBO::init(glm::mat4& transform, Node* node)
    {
        CVBO::Bind();

        e(glBufferData(GL_ARRAY_BUFFER, m_size * sizefloat, m_data, GL_STATIC_DRAW));

        e(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr));
        e(glEnableVertexAttribArray(0));

        if(node != nullptr)
            node->Init(transform);

        // CVBO::UnBind();
    }

    GLvoid CVBO::draw(Node* node)
    {
        // CVBO::Bind();

        if(node != nullptr)
            node->Draw();

        // CVBO::UnBind();
    }

    GLvoid CVBO::draw(const GLuint* array, Node* node)
    {
        // CVBO::Bind();

        if(node != nullptr)
            node->Draw(array);

        // CVBO::UnBind();
    }

    GLvoid CVBO::draw(const GLuint& shader_program, Node* node)
    {
        // CVBO::Bind();

        if(node != nullptr)
            node->Draw(shader_program);

        // CVBO::UnBind();
    }

    GLvoid CVBO::draw(const GLuint& shader_program, const GLuint* array, Node* node)
    {
        // CVBO::Bind();

        if(node != nullptr)
            node->Draw(shader_program, array);

        // CVBO::UnBind();
    }

    GLvoid CVBO::Bind()
    {
        e(glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_object));
    }

    GLvoid CVBO::UnBind()
    {
        e(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    GLuint CVBO::Get()
    {
        return m_vertex_buffer_object;
    }

    GLvoid CVBO::update(Node* node)
    {
        Update();

        if(node != nullptr)
            node->Update();
    }

    GLvoid CVBO::update(glm::mat4& transform, Node* node)
    {
        Update();

        if(node != nullptr)
            node->Update(transform);
    }

    GLvoid CVBO::Update()
    {
        if(m_data != nullptr && m_size > 0) {

            CVBO::Bind();

            e(glBufferData(GL_ARRAY_BUFFER, m_size * sizefloat, m_data, GL_STATIC_DRAW));

            CVBO::UnBind();
        }
    }

    GLvoid CVBO::Update(const GLuint& offset)
    {
        if(m_data != nullptr && m_size > 0) {

            CVBO::Bind();

            e(glBufferSubData(GL_ARRAY_BUFFER, offset, m_size * sizefloat, m_data));

            CVBO::UnBind();
        }
    }
}