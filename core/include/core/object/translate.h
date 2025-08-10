#pragma once

#include "core/object/bbo.h"

namespace core
{
    class CTranslate : public CBBO
    {
    private:
        GLfloat m_x = 0;
        GLfloat m_y = 0;
        GLfloat m_z = 0;

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

    public:
        CTranslate();
        CTranslate(const GLfloat& x, const GLfloat& y, const GLfloat& z);
        ~CTranslate() override = default;

        GLvoid Set(const GLfloat& x = 0.0f, const GLfloat& y = 0.0f, const GLfloat& z = 0.0f);
    };
}