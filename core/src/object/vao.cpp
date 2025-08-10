#include "core/object/vao.h"

#include <GL/glew.h>

#include "core/error.h"

namespace core
{
    CVAO::CVAO()
        : m_vertex_array_object(0)
    {
        e(glGenVertexArrays(1, &m_vertex_array_object)); // return void
    }

    CVAO::~CVAO()
    {
        e(glDeleteVertexArrays(1, &m_vertex_array_object));
    }

    GLvoid CVAO::init(Node* node)
    {
        CVAO::Bind();

        if(node != nullptr)
            node->Init();

        CVAO::UnBind();
    }

    GLvoid CVAO::init(const GLint& param, Node* node)
    {
        CVAO::Bind();

        if(node != nullptr)
            node->Init(param);

        CVAO::UnBind();
    }

    GLvoid CVAO::init(glm::mat4& transform, Node* node)
    {
        CVAO::Bind();

        if(node != nullptr)
            node->Init(transform);

        CVAO::UnBind();
    }

    GLvoid CVAO::draw(const GLuint* array, Node* node)
    {
        CVAO::Bind();

        if(node != nullptr)
            node->Draw(array);

        CVAO::UnBind();
    }

    GLvoid CVAO::draw(const GLuint& shader_program, Node* node)
    {
        CVAO::Bind();

        if(node != nullptr)
            node->Draw(shader_program);

        CVAO::UnBind();
    }

    GLvoid CVAO::draw(const GLuint& shader_program, const GLuint* array, Node* node)
    {
        CVAO::Bind();

        if(node != nullptr)
            node->Draw(shader_program, array);

        CVAO::UnBind();
    }

    GLvoid CVAO::draw(Node* node)
    {
        CVAO::Bind();

        if(node != nullptr)
            node->Draw();

        CVAO::UnBind();
    }

    GLvoid CVAO::update(Node* node)
    {
        if(node != nullptr)
            node->Update();
    }

    GLvoid CVAO::update(glm::mat4& transform, Node* node)
    {
        if(node != nullptr)
            node->Update(transform);
    }

    GLvoid CVAO::Bind()
    {
        e(glBindVertexArray(m_vertex_array_object));
    }

    GLvoid CVAO::UnBind()
    {
        e(glBindVertexArray(0));
    }

    GLuint CVAO::Get()
    {
        return m_vertex_array_object;
    }

    GLvoid CVAO::Set()
    {
    }
}