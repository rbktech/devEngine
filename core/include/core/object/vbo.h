#pragma once

#include "core/object/buffer.h"

namespace core
{
    class CVBO : public CData
    {
    private:
        GLuint m_vertex_buffer_object;

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
        CVBO();
        CVBO(const GLvoid* data, const GLsizei& size);
        ~CVBO() override;

        GLvoid Bind() final;
        GLvoid UnBind() final;
        GLuint Get() final;

        GLvoid Update();
        GLvoid Update(const GLuint& offset);

        GLvoid SetBuffer(const GLfloat* buffer, const GLsizei& size);

        GLvoid EnableVertex(const GLint& nCoord, const GLsizei& stride, const GLint& beginByte);
        GLvoid EnableColor(const GLint& nColor, const GLsizei& stride, const GLint& beginByte);
        GLvoid EnableTexCoord(const GLint& nTexCoord, const GLsizei& stride, const GLint& beginByte);

        GLvoid DisableVertex();
        GLvoid DisableColor();
        GLvoid DisableTexCoord();
    };
}