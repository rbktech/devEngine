#include "core/object/rbo.h"

#include <GL/glew.h>

#include "core/error.h"

namespace core
{
    CRBO::CRBO()
    {
        e(glGenRenderbuffers(1, &m_render_buffer_object));
    }

    CRBO::~CRBO()
    {
        e(glDeleteRenderbuffers(1, &m_render_buffer_object));
    }

    GLvoid CRBO::init(Node* node)
    {
        CRBO::Bind();

        if(node != nullptr)
            node->Init();

        // CRBO::UnBind();
    }

    GLvoid CRBO::init(const GLint& param, Node* node)
    {
        CRBO::Bind();

        if(node != nullptr)
            node->Init(param);

        // CRBO::UnBind();
    }

    GLvoid CRBO::init(glm::mat4& transform, Node* node)
    {
        CRBO::Bind();

        if(node != nullptr)
            node->Init(transform);

        // CRBO::UnBind();
    }

    GLvoid CRBO::draw(Node* node)
    {
        if(node != nullptr)
            node->Draw();
    }

    GLvoid CRBO::draw(const GLuint* array, Node* node)
    {
        if(node != nullptr)
            node->Draw(array);
    }

    GLvoid CRBO::draw(const GLuint& shader_program, Node* node)
    {
        if(node != nullptr)
            node->Draw(shader_program);
    }

    GLvoid CRBO::draw(const GLuint& shader_program, const GLuint* array, Node* node)
    {
        if(node != nullptr)
            node->Draw(shader_program, array);
    }

    GLvoid CRBO::update(Node* node)
    {
        if(node != nullptr)
            node->Update();
    }

    GLvoid CRBO::update(glm::mat4& transform, Node* node)
    {
        if(node != nullptr)
            node->Update(transform);
    }

    GLvoid CRBO::Bind()
    {
        e(glBindRenderbuffer(GL_RENDERBUFFER, m_render_buffer_object));
    }

    GLvoid CRBO::UnBind()
    {
        e(glBindRenderbuffer(GL_RENDERBUFFER, 0));
    }

    GLuint CRBO::Get()
    {
        return m_render_buffer_object;
    }

    GLvoid CRBO::Set()
    {
    }
}