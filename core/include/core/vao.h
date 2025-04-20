#pragma once

#include "type.h"

namespace core
{
    class CVAO
    {
    private:
        GLenum m_type;
        GLint m_first;
        GLsizei m_size;

    protected:
        GLuint m_vertex_array_object_names;

    public:
        CVAO();

        ~CVAO();

        GLvoid Bind();

        GLvoid Draw();

        GLvoid SetDrawParams(const GLenum &type, const GLint &first, const GLsizei &size);
    };

    // -----------------------------------------------------------------------

    class CVAOBuffer : public CVAO
    {
    private:
        GLuint m_buffer_object_name;

    public:
        CVAOBuffer();

        ~CVAOBuffer();

        GLvoid SetBuffer(const GLfloat *buffer, const GLsizei &size);

        GLvoid EnableVertex(const GLint &nCoordinates, const GLsizei &stride, const GLint &beginByte);

        GLvoid EnableColor(const GLint &nColors, const GLsizei &stride, const GLint &beginByte);
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
        GLvoid SetBufferVertex(const GLfloat *buffer, const GLsizei &size, const GLsizei &nCoordinates);

        GLvoid SetBufferColor(const GLfloat *buffer, const GLsizei &size, const GLsizei &nColors);
    };

    // -----------------------------------------------------------------------

    class CVAOFull : public CVAO
    {
    private:
        GLuint m_buffer_object_name;

    public:
        CVAOFull();

        ~CVAOFull();

        GLvoid Set(
                const GLfloat *buffer, const GLsizei &size,
                const GLint &nCoordinates, const GLsizei &strideCoordinates, const GLint &beginByteCoordinates,
                const GLint &nColors, const GLsizei &strideColors, const GLint &beginByteColors
        );
    };
}