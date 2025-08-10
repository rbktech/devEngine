#pragma once

#include "core/object/vao.h"

namespace core
{
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