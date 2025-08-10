#pragma once

#include "core/object/bbo.h"

namespace core
{
    class CRotate : public CBBO
    {
    private:
        GLfloat m_degrees;

        GLfloat m_x;
        GLfloat m_y;
        GLfloat m_z;

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

        glm::mat4 Update(const glm::mat4& transform);

    public:
        CRotate();
        ~CRotate() override = default;

        GLvoid Set(const GLfloat& degrees = 0.0f, const GLfloat& x = 0.0f, const GLfloat& y = 0.0f, const GLfloat& z = 1.0f);
    };
}