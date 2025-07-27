#pragma once

#include "core/object/buffer.h"

namespace core
{
    class CEBO : public CData
    {
    private:
        // GLuint m_vertex_array_object;   // Vertex Array Object, VAO
        // GLuint m_vertex_buffer_objects; // Vertex Buffer Objects, VBO
        GLuint m_element_buffer_object; // Element (Index) Buffer Object, EBO

        // GLfloat m_x;
        // GLfloat m_y;
        // GLfloat m_z;

        // GLenum m_type;
        // GLsizei m_size;

        GLvoid init(Node* node) final;
        GLvoid init(const GLint& param, Node* node) final;
        GLvoid init(glm::mat4& transform, Node* node) final;

        GLvoid draw(const GLuint* array, Node* node) final;
        GLvoid draw(const GLuint& shader_program, Node* node) final;
        GLvoid draw(const GLuint& shader_program, const GLuint* array, Node* node) final;
        GLvoid draw(Node* node) final;

        GLvoid update(Node* node) final;
        GLvoid update(glm::mat4& transform, Node* node) final;

        GLvoid Update();
        GLvoid Update(const GLuint& offset);

    public:
        CEBO();
        CEBO(const GLvoid* data, const GLsizei& size);
        ~CEBO() override;

        GLvoid Bind() final;
        GLvoid UnBind() final;
        GLuint Get() final;

        GLvoid SetBuffer(const GLfloat* buffer, const GLsizei& size);
        GLvoid SetElements(const GLuint* elements, const GLsizei& size);

        GLvoid EnableVertex(const GLint& nCoordinates, const GLsizei& stride, const GLint& beginByte);
        GLvoid EnableColor(const GLint& nColor, const GLsizei& stride, const GLint& beginByte);
        GLvoid EnableTextureCoord(const GLint& nTextureCoord, const GLsizei& stride, const GLint& beginByte);

        GLvoid DisableVertex();
        GLvoid DisableColor();
        GLvoid DisableTextureCoord();

        GLvoid SetDrawCoordinate(const GLfloat& x, const GLfloat& y, const GLfloat& z);
        GLvoid SetDrawParams(const GLenum& type, const GLsizei& size);

        GLvoid Draw();
    };
}