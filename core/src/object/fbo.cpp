#include "core/object/fbo.h"

#include <GL/glew.h>

#include "core/error.h"

namespace core
{
    CFBO::CFBO()
    {
        e(glGenFramebuffers(1, &m_frame_buffer_object));
    }

    CFBO::~CFBO()
    {
        e(glDeleteFramebuffers(1, &m_frame_buffer_object));
    }

    GLvoid CFBO::init(Node* node)
    {
        CFBO::Bind();

        if(node != nullptr)
            node->Init();

        // CFBO::UnBind();
    }

    GLvoid CFBO::init(const GLint& param, Node* node)
    {
        CFBO::Bind();

        if(node != nullptr)
            node->Init(param);

        // CFBO::UnBind();
    }

    GLvoid CFBO::init(glm::mat4& transform, Node* node)
    {
        CFBO::Bind();

        if(node != nullptr)
            node->Init(transform);

        // CFBO::UnBind();
    }

    GLvoid CFBO::draw(Node* node)
    {
        if(node != nullptr)
            node->Draw();
    }

    GLvoid CFBO::draw(const GLuint* array, Node* node)
    {
        if(node != nullptr)
            node->Draw(array);
    }

    GLvoid CFBO::draw(const GLuint& shader_program, Node* node)
    {
        if(node != nullptr)
            node->Draw(shader_program);
    }

    GLvoid CFBO::draw(const GLuint& shader_program, const GLuint* array, Node* node)
    {
        if(node != nullptr)
            node->Draw(shader_program, array);
    }

    GLvoid CFBO::update(Node* node)
    {
        if(node != nullptr)
            node->Update();
    }

    GLvoid CFBO::update(glm::mat4& transform, Node* node)
    {
        if(node != nullptr)
            node->Update(transform);
    }

    GLvoid CFBO::Bind()
    {
        e(glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer_object));
    }

    GLvoid CFBO::UnBind()
    {
        e(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    }

    GLvoid CFBO::Set()
    {
    }

    GLuint CFBO::Get()
    {
        return m_frame_buffer_object;
    }
}