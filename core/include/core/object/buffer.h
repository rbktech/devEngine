#pragma once

#include "core/object/bbo.h"
#include "core/variable.h"

namespace core
{
    class CData : public CBBO
    {
    protected:
        GLsizei m_size;
        const GLvoid* m_data;

    private:

        GLvoid init(Node* node) override = 0;
        GLvoid init(const GLint& param, Node* node) override = 0;
        GLvoid init(glm::mat4& transform, Node* node) override = 0;

        GLvoid draw(Node* node) override = 0;
        GLvoid draw(const GLuint* array, Node* node) override = 0;
        GLvoid draw(const GLuint& shader_program, Node* node) override = 0;
        GLvoid draw(const GLuint& shader_program, const GLuint* array, Node* node) override = 0;

        GLvoid update(Node* node) override = 0;
        GLvoid update(glm::mat4& transform, Node* node) override = 0;

        GLvoid Bind() override = 0;
        GLvoid UnBind() override = 0;
        GLuint Get() override = 0;

    public:
        CData();

        CData(const GLvoid* data, const GLsizei& size);

        ~CData() override = default;

        GLvoid Set(const GLvoid* data, const GLsizei& size);

        GLvoid Reset() override;
    };
}

namespace core
{
    class CBuffer : public CData
    {
    private:
        GLuint m_buffer_object;

        GLvoid (*Attribute)() = {};

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
        CBuffer();
        ~CBuffer() override;

        GLvoid Bind() final;
        GLvoid UnBind() final;
        GLuint Get() final;

        GLvoid Set(const GLvoid* data, const GLsizei& size, GLvoid (*attribute)());
    };
}
