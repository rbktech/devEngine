#include "core/object/buffer.h"

#include <GL/glew.h>

#include "core/error.h"

namespace core
{
    CData::CData()
        : m_data(nullptr)
        , m_size(0)
    {
    }

    CData::CData(const GLvoid* data, const GLsizei& size)
        : m_data(data)
        , m_size(size)
    {
    }

    // -------------------------------------------------------------------

    /*GLvoid CData::init(const GLint& param, Node* node)
    {
        if(node != nullptr)
            node->Init(param);
    }

    GLvoid CData::draw(const GLuint* array, Node* node)
    {
        if(node != nullptr)
            node->Draw(array);
    }

    GLvoid CData::draw(const GLuint& shader_program, Node* node)
    {
        if(node != nullptr)
            node->Draw(shader_program);
    }

    GLvoid CData::draw(const GLuint& shader_program, const GLuint* array, Node* node)
    {
        if(node != nullptr)
            node->Draw(shader_program, array);
    }

    GLvoid CData::draw(Node* node)
    {
        if(node != nullptr)
            node->Draw();
    }*/

    // -------------------------------------------------------------------

    GLvoid CData::Set(const GLvoid* data, const GLsizei& size)
    {
        m_data = data;
        m_size = size;
    }

    GLvoid CData::Reset()
    {
        CData::Set(nullptr, 0);
    }
}

namespace core
{
    CBuffer::CBuffer()
        : m_buffer_object(0)
    {
        e(glGenBuffers(1, &m_buffer_object));
    }
    CBuffer::~CBuffer()
    {
        e(glDeleteBuffers(1, &m_buffer_object));
    }

    GLvoid CBuffer::Bind()
    {
        e(glBindBuffer(GL_ARRAY_BUFFER, m_buffer_object));
    }

    GLvoid CBuffer::UnBind()
    {
        e(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    GLvoid CBuffer::init(Node* node)
    {
        CBuffer::Bind();

        e(glBufferData(GL_ARRAY_BUFFER, m_size * sizefloat, m_data, GL_STATIC_DRAW));

        CBuffer::Attribute();

        if(node != nullptr)
            node->Init();

        // CBuffer::UnBind();
    }

    GLvoid CBuffer::init(const GLint& param, Node* node)
    {
        CBuffer::Bind();

        e(glBufferData(GL_ARRAY_BUFFER, m_size * sizefloat, m_data, GL_STATIC_DRAW));

        /*// position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)nullptr);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);*/

        /*e(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizefloat, nullptr));
        e(glEnableVertexAttribArray(0));

        e(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizefloat, (GLvoid*)(3 * sizefloat)));
        e(glEnableVertexAttribArray(1));*/

        CBuffer::Attribute();

        if(node != nullptr)
            node->Init(param);

        // CBuffer::UnBind();
    }

    GLvoid CBuffer::init(glm::mat4& transform, Node* node)
    {
        CBuffer::Bind();

        e(glBufferData(GL_ARRAY_BUFFER, m_size * sizefloat, m_data, GL_STATIC_DRAW));

        CBuffer::Attribute();

        if(node != nullptr)
            node->Init(transform);

        // CBuffer::UnBind();
    }

    GLvoid CBuffer::draw(Node* node)
    {
        // CBuffer::Bind();

        if(node != nullptr)
            node->Draw();
    }

    GLvoid CBuffer::draw(const GLuint* array, Node* node)
    {
        // CBuffer::Bind();

        if(node != nullptr)
            node->Draw(array);
    }

    GLvoid CBuffer::draw(const GLuint& shader_program, Node* node)
    {
        // CBuffer::Bind();

        if(node != nullptr)
            node->Draw(shader_program);
    }

    GLvoid CBuffer::draw(const GLuint& shader_program, const GLuint* array, Node* node)
    {
        // CBuffer::Bind();

        if(node != nullptr)
            node->Draw(shader_program, array);
    }

    GLvoid CBuffer::update(Node* node)
    {
        if(node != nullptr)
            node->Update();
    }

    GLvoid CBuffer::update(glm::mat4& transform, Node* node)
    {
        if(node != nullptr)
            node->Update(transform);
    }

    GLvoid CBuffer::Set(const GLvoid* data, const GLsizei& size, GLvoid (*attribute)())
    {
        m_data = data;
        m_size = size;
        Attribute = attribute;
    }

    GLuint CBuffer::Get()
    {
        return m_buffer_object;
    }
}