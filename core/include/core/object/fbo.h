#pragma once

#include "core/object/bbo.h"

namespace core
{
    class CFBO : public CBBO
    {
    private:
        GLuint m_frame_buffer_object;

        GLvoid init(Node* node) final;
        GLvoid init(const GLint& param, Node* node) final;
        GLvoid init(glm::mat4& transform, Node* node) final;

        GLvoid draw(Node* node) final;
        GLvoid draw(const GLuint* array, Node* node) final;
        GLvoid draw(const GLuint& shader_program, Node* node) final;
        GLvoid draw(const GLuint& shader_program, const GLuint* array, Node* node) final;

        GLvoid update(Node* node) final;
        GLvoid update(glm::mat4& transform, Node* node) final;

    public:
        CFBO();
        ~CFBO() override;

        GLvoid Bind() final;
        GLvoid UnBind() final;
        GLuint Get() final;

        GLvoid Set();
    };
}