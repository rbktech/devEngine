#pragma once

#include "core/object/bbo.h"

namespace core
{
    class CVAO : public CBBO
    {
    private:
        // GLenum m_type;
        // GLint m_first;
        // GLsizei m_size;
        // GLboolean m_show;

        // GLfloat m_x;
        // GLfloat m_y;
        // GLfloat m_z;

        GLvoid init(Node* node) final;
        GLvoid init(const GLint& param, Node* node) final;
        GLvoid init(glm::mat4& transform, Node* node) final;

        GLvoid draw(Node* node) final;
        GLvoid draw(const GLuint* array, Node* node) final;
        GLvoid draw(const GLuint& shader_program, Node* node) final;
        GLvoid draw(const GLuint& shader_program, const GLuint* array, Node* node) final;

        GLvoid update(Node* node) final;
        GLvoid update(glm::mat4& transform, Node* node) final;

    protected:
        GLuint m_vertex_array_object;

    public:
        CVAO();
        ~CVAO() override;

        GLvoid Bind() final;
        GLvoid UnBind() final;
        GLuint Get() final;

        GLvoid Set();

        GLvoid Draw();

        GLvoid SetDrawParams(const GLenum& type, const GLint& first, const GLsizei& size);

        GLvoid SetDrawCoordinate(const GLfloat& x, const GLfloat& y, const GLfloat& z = 0.0f);

        GLboolean IsShow();

        GLvoid IsShow(GLboolean value);
    };

    // -----------------------------------------------------------------------

    class CVAOBuffer : public CVAO
    {
    private:
        GLuint m_buffer_object_name;

    public:
        CVAOBuffer();

        ~CVAOBuffer();

        GLvoid SetBuffer(const GLfloat* buffer, const GLsizei& size);

        GLvoid EnableVertex(const GLint& nCoordinates, const GLsizei& stride, const GLint& beginByte);

        GLvoid EnableColor(const GLint& nColors, const GLsizei& stride, const GLint& beginByte);
    };

    // -----------------------------------------------------------------------

    class CVAOParams : public CVAO
    {
    public:
        CVAOParams();

        ~CVAOParams();

        GLuint m_buffer_object_name_vertex;
        GLuint m_buffer_object_name_color;

    public:
        GLvoid SetBufferVertex(const GLfloat* buffer, const GLsizei& size, const GLsizei& nCoordinates);

        GLvoid SetBufferColor(const GLfloat* buffer, const GLsizei& size, const GLsizei& nColors);
    };

    // -----------------------------------------------------------------------

    class CVAOFull : public CVAO
    {
    private:
        GLuint m_buffer_object_name;

    public:
        CVAOFull();

        ~CVAOFull();

        GLvoid Set(const GLfloat* buffer,
            const GLsizei& size,
            const GLint& nCoordinates,
            const GLsizei& strideCoordinates,
            const GLint& beginByteCoordinates,
            const GLint& nColors,
            const GLsizei& strideColors,
            const GLint& beginByteColors);
    };
}