#pragma once

#include "core/object/buffer.h"

namespace core
{
    class CTBO : public CData
    {
    private:
        GLuint m_texture_buffer_object; // Texture Buffer Object

        GLvoid init(Node* node) final;
        GLvoid init(const GLint& param, Node* node) final;
        GLvoid init(glm::mat4& transform, Node* node) final;

        GLvoid draw(Node* node) final;
        GLvoid draw(const GLuint* array, Node* node) final;
        GLvoid draw(const GLuint& shader_program, Node* node) final;
        GLvoid draw(const GLuint& shader_program, const GLuint* array, Node* node) final;

        GLvoid update(Node* node) final;
        GLvoid update(glm::mat4& transform, Node* node) final;

        GLvoid Update();
        GLvoid Update(const GLuint& offset);

    public:
        CTBO();
        CTBO(const GLvoid* data, const GLsizei& size);
        ~CTBO() override;

        GLvoid Bind() final;
        GLvoid UnBind() final;
        GLuint Get() final;
    };
}