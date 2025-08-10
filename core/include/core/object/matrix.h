#pragma once

#include "core/object/bbo.h"

namespace core
{
    class CMatrix : public CBBO
    {
    private:
        glm::mat4 m_transform = glm::mat4(1.0f);

        GLvoid init(Node* node) final;
        GLvoid init(const GLint& param, Node* node) final;
        GLvoid init(glm::mat4& transform, Node* node) final;

        GLvoid draw(Node* node) final;
        GLvoid draw(const GLuint* array, Node* node) final;
        GLvoid draw(const GLuint& shader_program, Node* node) final;
        GLvoid draw(const GLuint& shader_program, const GLuint* array, Node* node) final;

        GLvoid update(Node* node) final;
        GLvoid update(glm::mat4& transform, Node* node) final;

        GLvoid Bind() final {};
        GLvoid UnBind() final {};
        GLuint Get() final { return 0; };

    public:
        CMatrix() = default;
        ~CMatrix() override = default;

        GLvoid Set(const glm::mat4& transform = glm::mat4(1.0f))
        {
            m_transform = transform;
        }

        /*GLvoid SetMatrix(const glm::mat4& transform = glm::mat4(1.0f))
        {
            m_transform = transform;
        }

        glm::mat4 GetMatrix()
        {
            return m_transform;
        }*/
    };
}