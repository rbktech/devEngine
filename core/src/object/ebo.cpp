#include "core/object/ebo.h"

#include <GL/glew.h>

#include "core/error.h"

namespace core
{
    CEBO::CEBO()
        : CData(nullptr, 0)
        , m_element_buffer_object(0)
    {
        e(glGenBuffers(1, &m_element_buffer_object)); // return void
    }

    CEBO::CEBO(const GLvoid* data, const GLsizei& size)
        : CData(data, size)
    // , m_vertex_array_object(0)
    // , m_vertex_buffer_objects(0)
    // , m_element_buffer_object(0)
    // , m_type(0)
    // , m_size(0)
    // , m_x(0.0f)
    // , m_y(0.0f)
    // , m_z(0.0f)
    {
        // e(glGenVertexArrays(1, &m_vertex_array_object)); // return void
        // e(glGenBuffers(1, &m_vertex_buffer_objects));    // return void
        e(glGenBuffers(1, &m_element_buffer_object)); // return void
    }

    CEBO::~CEBO()
    {
        // e(glDeleteVertexArrays(1, &m_vertex_array_object));
        // e(glDeleteBuffers(1, &m_vertex_buffer_objects)); // return void
        e(glDeleteBuffers(1, &m_element_buffer_object)); // return void
    }

    GLvoid CEBO::SetBuffer(const GLfloat* buffer, const GLsizei& size)
    {
        // e(glBindVertexArray(m_vertex_array_object));

        // e(glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_objects)); // return void

        e(glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), buffer, GL_STATIC_DRAW)); // return void

        e(glBindVertexArray(0));
    }

    GLvoid CEBO::SetElements(const GLuint* elements, const GLsizei& size)
    {
        // e(glBindVertexArray(m_vertex_array_object));

        e(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_buffer_object)); // return void

        e(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLuint), elements, GL_STATIC_DRAW)); // return void

        e(glBindVertexArray(0));
    }
    GLvoid CEBO::EnableVertex(const GLint& nCoordinates, const GLsizei& stride, const GLint& beginByte)
    {
        // e(glBindVertexArray(m_vertex_array_object));

        e(glVertexAttribPointer(
            0, nCoordinates, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(beginByte * sizeof(GLfloat))));
        e(glEnableVertexAttribArray(0));

        e(glBindVertexArray(0));
    }

    GLvoid CEBO::EnableColor(const GLint& nColor, const GLsizei& stride, const GLint& beginByte)
    {
        // e(glBindVertexArray(m_vertex_array_object));

        e(glVertexAttribPointer(
            1, nColor, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(beginByte * sizeof(GLfloat))));
        e(glEnableVertexAttribArray(1));

        e(glBindVertexArray(0));
    }

    GLvoid CEBO::EnableTextureCoord(const GLint& nTextureCoord, const GLsizei& stride, const GLint& beginByte)
    {
        // e(glBindVertexArray(m_vertex_array_object));

        e(glVertexAttribPointer(
            2, nTextureCoord, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(beginByte * sizeof(GLfloat))));
        e(glEnableVertexAttribArray(2));

        e(glBindVertexArray(0));
    }

    /*GLvoid CEBO::EnableVertex(const GLint& nCoordinates, const GLsizei& stride, const GLint& beginByte)
    {
        // e(glBindVertexArray(m_vertex_array_object));

        // e(glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_objects));

        e(glVertexPointer(
            nCoordinates, GL_FLOAT, (GLsizei)(stride * sizefloat), (GLvoid*)(beginByte * sizefloat))); // return void

        e(glEnableClientState(GL_VERTEX_ARRAY));

        e(glBindVertexArray(0));
    }

    GLvoid CEBO::EnableColor(const GLint& nColor, const GLsizei& stride, const GLint& beginByte)
    {
        // e(glBindVertexArray(m_vertex_array_object));

        // e(glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_objects));

        e(glColorPointer(nColor, GL_FLOAT, (GLsizei)(stride * sizefloat),
            (GLvoid*)(beginByte * sizefloat))); // return void

        e(glEnableClientState(GL_COLOR_ARRAY));

        e(glBindVertexArray(0));
    }

    GLvoid CEBO::EnableTextureCoord(const GLint& nTextureCoord, const GLsizei& stride, const GLint& beginByte)
    {
        // e(glBindVertexArray(m_vertex_array_object));

        // e(glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_objects));

        e(glTexCoordPointer(nTextureCoord, GL_FLOAT, (GLsizei)(stride * sizefloat),
            (GLvoid*)(beginByte * sizefloat))); // return void

        e(glEnableClientState(GL_COLOR_ARRAY));

        e(glBindVertexArray(0));
    }*/

    GLvoid CEBO::DisableVertex()
    {
        e(glDisableClientState(GL_VERTEX_ARRAY));
    }

    GLvoid CEBO::DisableColor()
    {
        e(glDisableClientState(GL_COLOR_ARRAY));
    }

    GLvoid CEBO::DisableTextureCoord()
    {
        e(glDisableClientState(GL_TEXTURE_COORD_ARRAY));
    }

    GLvoid CEBO::Draw()
    {
        // e(glBindVertexArray(m_vertex_array_object));

        // e(glDrawElements(m_type, m_size, GL_UNSIGNED_INT, 0)); // return void

        e(glBindVertexArray(0));
    }

    GLvoid CEBO::SetDrawCoordinate(const GLfloat& x, const GLfloat& y, const GLfloat& z)
    {
        // m_x = x;
        // m_y = y;
        // m_z = z;
    }

    GLvoid CEBO::SetDrawParams(const GLenum& type, const GLsizei& size)
    {
        // m_type = type;
        // m_size = size;
    }

    /*GLvoid CEBO::Bind()
    {
        e(glBindVertexArray(m_vertex_array_object));
    }

    GLvoid CEBO::UnBind()
    {
        e(glBindVertexArray(0));
    }*/

    GLvoid CEBO::Bind()
    {
        // e(glBindVertexArray(m_vertex_array_object));
        e(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_buffer_object)); // return void
    }

    GLvoid CEBO::UnBind()
    {
        // e(glBindVertexArray(0));
        e(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); // return void
    }

    /*GLvoid CEBO::Bind()
    {
        e(glBindVertexArray(m_vertex_array_object));
    }

    GLvoid CEBO::UnBind()
    {
        e(glBindVertexArray(0));
    }*/

    GLvoid CEBO::init(Node* node)
    {
        CEBO::Bind();

        e(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size * sizeuint, m_data, GL_STATIC_DRAW));

        if(node != nullptr)
            node->Init();

        // Обязательно не должно быть UnBind у VAO
    }

    GLvoid CEBO::init(const GLint& param, Node* node)
    {
        CEBO::Bind();

        e(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size * sizeuint, m_data, GL_STATIC_DRAW));

        if(node != nullptr)
            node->Init(param);

        // Обязательно не должно быть UnBind у VAO
    }

    GLvoid CEBO::init(glm::mat4& transform, Node* node)
    {
        CEBO::Bind();

        e(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size * sizeuint, m_data, GL_STATIC_DRAW));

        if(node != nullptr)
            node->Init(transform);

        // Обязательно не должно быть UnBind у VAO
    }

    GLvoid CEBO::draw(Node* node)
    {
        if(node != nullptr)
            node->Draw();
    }

    GLvoid CEBO::draw(const GLuint* array, Node* node)
    {
        // CEBO::Bind();

        if(node != nullptr)
            node->Draw(array);
    }

    GLvoid CEBO::draw(const GLuint& shader_program, Node* node)
    {
        if(node != nullptr)
            node->Draw(shader_program);
    }

    GLvoid CEBO::draw(const GLuint& shader_program, const GLuint* array, Node* node)
    {
        if(node != nullptr)
            node->Draw(shader_program, array);
    }

    GLvoid CEBO::update(Node* node)
    {
        CEBO::Update();

        if(node != nullptr)
            node->Update();
    }

    GLvoid CEBO::update(glm::mat4& transform, Node* node)
    {
        CEBO::Update();

        if(node != nullptr)
            node->Update(transform);
    }

    GLvoid CEBO::Update()
    {
        if(m_data != nullptr && m_size > 0) {

            CEBO::Bind();

            e(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size * sizeuint, m_data, GL_STATIC_DRAW));

            CEBO::UnBind();
        }
    }

    GLvoid CEBO::Update(const GLuint& offset)
    {
        if(m_data != nullptr && m_size > 0) {

            CEBO::Bind();

            e(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, m_size * sizeuint, m_data));

            CEBO::UnBind();
        }
    }

    GLuint CEBO::Get()
    {
        return m_element_buffer_object;
    }

    /*GLvoid CEBO::draw(const GLuint* array)
    {
        CEBO::Bind();
        CBBO::Next(array);
        CEBO::UnBind();
    }*/
}