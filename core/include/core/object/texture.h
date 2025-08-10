#pragma once

#include "core/type.h"

#include "core/object/buffer.h"

namespace core
{
    class CTexture : public CData
    {
    private:
        GLuint m_texture = 0;

        GLint m_width = 0;
        GLint m_height = 0;
        GLint m_offset = 0;
        GLint m_bits = 0;
        GLvoid (CTexture::*Param)() = {};

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
        CTexture();
        CTexture(const GLvoid* data,
            const GLsizei& size,
            const GLint& width,
            const GLint& height,
            const GLint& offset,
            const GLint& bits,
            GLvoid (CTexture::*param)() = &CTexture::ParamBase);
        ~CTexture() override;

        GLvoid Create(const GLubyte* data, const GLint& width, const GLint& height, const GLint& offset, const GLint& bits);
        GLvoid CreateBuffer(const GLint& w, const GLint& h);

        GLvoid ParamBase();
        GLvoid ParamRepeatNearest();
        GLvoid ParamRepeatLinear();
        GLvoid ParamMipMap();

        static GLvoid Enable();
        static GLvoid Disable();

        GLvoid Bind() final;
        GLvoid UnBind() final;
        GLuint Get() final;

        GLvoid Set(const GLvoid* data,
            const GLsizei& size,
            const GLint& width,
            const GLint& height,
            const GLint& offset,
            const GLint& bits,
            GLvoid (CTexture::*param)() = &CTexture::ParamBase);
    };
}