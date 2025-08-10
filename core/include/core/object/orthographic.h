#pragma once

#include "core/object/bbo.h"

namespace core
{
    class COrthographic : public CBBO
    {
    public:
        struct TMoveXY {
            GLfloat x = 0.0f;
            GLfloat y = 0.0f;
        };

        struct TScale {
            GLfloat value = 0.0f;
        };

        struct TSize {
            GLfloat w = 0.0f;
            GLfloat h = 0.0f;
        };

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
            const GLfloat& near = -1.0f,
            const GLfloat& far = 1.0f);

        GLvoid Set(const TMoveXY& moveXY);

        GLvoid Set(const TScale& scale);

        GLvoid Set(const TSize& size);

        GLvoid Update();

        glm::mat4 GetMatrix();

        glm::vec3 ToWorldCoord(const GLfloat& x, const GLfloat& y, const GLfloat& w, const GLfloat& h);
    };
}