#pragma once

#include "core/object/bbo.h"

namespace core
{
    class CPerspective : public CBBO
    {
    private:
        glm::mat4 m_projection = glm::mat4(1.0f);

        GLfloat m_fovy;
        GLfloat m_aspect;
        GLfloat m_near;
        GLfloat m_far;

        GLvoid init(Node* node) final;
        GLvoid init(const GLint& param, Node* node) final;
        GLvoid init(glm::mat4& transform, Node* node) final;

        GLvoid draw(Node* node) final;
        GLvoid draw(const GLuint* array, Node* node) final;
        GLvoid draw(const GLuint& shader_program, Node* node) final;
        GLvoid draw(const GLuint& shader_program, const GLuint* array, Node* node) final;

        GLvoid update(Node* node) final;
        GLvoid update(glm::mat4& transform, Node* node) final;

        GLvoid Bind() final;
        GLvoid UnBind() final;
        GLuint Get() final;

        GLvoid Update();

    public:
        CPerspective();
        ~CPerspective() override = default;

        GLvoid Set(const GLfloat& fovy = 45.0f,
            const GLfloat& aspect = 1.0f,
            const GLfloat& near = 0.1f,
            const GLfloat& far = 100.0f);

        glm::mat4 GetMatrix();
    };
}