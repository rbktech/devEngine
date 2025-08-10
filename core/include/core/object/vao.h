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
    };
}