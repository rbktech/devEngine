#pragma once

#include "core/object/bbo.h"

namespace core
{
    class CDrawArrays : public CBBO
    {
    private:
        GLenum m_type;
        GLint m_first;
        GLsizei m_size;

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
        CDrawArrays();

        CDrawArrays(const GLenum& type, const GLint& first, const GLsizei& size);

        ~CDrawArrays() override = default;

        GLvoid Set(const GLenum& type, const GLint& first, const GLsizei& size);

        GLvoid Set(const GLsizei& size);

        GLint Size();
    };

    class CDrawElements : public CBBO
    {
    private:
        GLenum m_type = 0;
        GLsizei m_size = 0;

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
        CDrawElements();

        CDrawElements(const GLenum& type, const GLsizei& size);

        ~CDrawElements() override = default;

        GLvoid Set(const GLenum& type, const GLsizei& size);
    };
}