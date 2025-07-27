#pragma once

#include "core/object/bbo.h"

namespace core
{
    class COrthographic : public CBBO
    {
    private:
        glm::mat4 m_orthographic = glm::mat4(1.0f);

        GLfloat m_left;
        GLfloat m_right;
        GLfloat m_bottom;
        GLfloat m_top;
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

    public:
        COrthographic();
        ~COrthographic() override = default;

        GLvoid Set(const GLfloat& left,
            const GLfloat& right,
            const GLfloat& bottom,
            const GLfloat& top,
            const GLfloat& near,
            const GLfloat& far);

        GLvoid Update();
    };
}