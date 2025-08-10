#include "core/object/rotate.h"

#include <GL/glew.h>

#include <glm/ext/matrix_transform.hpp>

#include "core/error.h"

namespace core
{
    CRotate::CRotate()
        : m_degrees(0.0f)
        , m_x(0.0f)
        , m_y(0.0f)
        , m_z(1.0f)
    {
    }

    // -------------------------------------------------------------------

    GLvoid CRotate::init(Node* node)
    {
        throw std::runtime_error("error: wrong call: GLvoid CRotate::init(Node* node)");
    }

    GLvoid CRotate::init(const GLint& param, Node* node)
    {
        throw std::runtime_error("error: wrong call: GLvoid CRotate::init(const GLint& param, Node* node)");
    }

    GLvoid CRotate::init(glm::mat4& transform, Node* node)
    {
        if(node != nullptr)
            node->Init(transform);

        transform = Update(transform);
    }

    GLvoid CRotate::draw(const GLuint* array, Node* node)
    {
        if(node != nullptr)
            node->Draw(array);
    }

    GLvoid CRotate::draw(const GLuint& shader_program, Node* node)
    {
        if(node != nullptr)
            node->Draw(shader_program);
    }

    GLvoid CRotate::draw(const GLuint& shader_program, const GLuint* array, Node* node)
    {
        if(node != nullptr)
            node->Draw(shader_program, array);
    }

    GLvoid CRotate::draw(Node* node)
    {
        if(node != nullptr)
            node->Draw();
    }

    GLvoid CRotate::update(Node* node)
    {
        if(node != nullptr)
            node->Update();
    }

    GLvoid CRotate::update(glm::mat4& transform, Node* node)
    {
        if(node != nullptr)
            node->Update(transform);

        transform = Update(transform);
    }

    GLvoid CRotate::Bind()
    {
    }

    GLvoid CRotate::UnBind()
    {
    }

    GLuint CRotate::Get()
    {
        return 0;
    }

    GLvoid CRotate::Set(const GLfloat& degrees, const GLfloat& x, const GLfloat& y, const GLfloat& z)
    {
        m_degrees = degrees;
        m_x = x;
        m_y = y;
        m_z = z;
    }

    glm::mat4 CRotate::Update(const glm::mat4& transform)
    {
        return glm::rotate(transform, glm::radians(m_degrees), { m_x, m_y, m_z });
    }
}