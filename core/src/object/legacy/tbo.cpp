#include "core/object/tbo.h"

#include <GL/glew.h>

#include "core/error.h"

namespace core
{
    CTBO::CTBO()
        : CData(nullptr, 0)
        , m_texture_buffer_object(0)
    {
        e(glGenBuffers(1, &m_texture_buffer_object));
    }

    CTBO::CTBO(const GLvoid* data, const GLsizei& size)
        : CData(data, size)
        , m_texture_buffer_object(0)
    {
        e(glGenBuffers(1, &m_texture_buffer_object));
    }

    CTBO::~CTBO()
    {
        e(glDeleteBuffers(1, &m_texture_buffer_object));
    }

    GLvoid CTBO::init(Node* node)
    {
        CTBO::Bind();

        e(glBufferData(GL_ARRAY_BUFFER, m_size * sizefloat, m_data, GL_STATIC_DRAW));

        if(node != nullptr)
            node->Init();

        CTBO::UnBind();
    }

    GLvoid CTBO::init(const GLint& param, Node* node)
    {
        CTBO::Bind();

        e(glBufferData(GL_ARRAY_BUFFER, m_size * sizefloat, m_data, GL_STATIC_DRAW));

        if(node != nullptr)
            node->Init(param);

        CTBO::UnBind();
    }

    GLvoid CTBO::init(glm::mat4& transform, Node* node)
    {
        throw std::runtime_error("error: wrong call: GLvoid CTBO::init(glm::mat4& transform, Node* node)");
    }

    GLvoid CTBO::draw(Node* node)
    {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        CTBO::Bind();

        e(glTexCoordPointer(2, GL_FLOAT, 0, nullptr));

        if(node != nullptr)
            node->Draw();

        e(glDisableClientState(GL_TEXTURE_COORD_ARRAY));
    }

    GLvoid CTBO::draw(const GLuint* array, Node* node)
    {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        CTBO::Bind();

        e(glTexCoordPointer(2, GL_FLOAT, 0, nullptr));

        if(node != nullptr)
            node->Draw(array);

        e(glDisableClientState(GL_TEXTURE_COORD_ARRAY));
    }

    GLvoid CTBO::draw(const GLuint& shader_program, Node* node)
    {
        throw std::runtime_error("error: wrong call: GLvoid CTBO::draw(const GLuint& shader_program, Node* node)");
    }

    GLvoid CTBO::draw(const GLuint& shader_program, const GLuint* array, Node* node)
    {
        throw std::runtime_error("error: wrong call: GLvoid CTBO::draw(const GLuint& shader_program, const GLuint* array, Node* node)");
    }

    GLvoid CTBO::update(Node* node)
    {
        if(node != nullptr)
            node->Update();
    }

    GLvoid CTBO::update(glm::mat4& transform, Node* node)
    {
        if(node != nullptr)
            node->Update(transform);
    }

    GLvoid CTBO::Bind()
    {
        e(glBindBuffer(GL_ARRAY_BUFFER, m_texture_buffer_object));
    }

    GLvoid CTBO::UnBind()
    {
        e(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    GLuint CTBO::Get()
    {
        return m_texture_buffer_object;
    }
}