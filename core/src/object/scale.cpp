#include "core/object/scale.h"

#include <glm/ext/matrix_transform.hpp>

namespace core
{
    CScale::CScale()
        : m_x(1.0f)
        , m_y(1.0f)
        , m_z(1.0f)
    {
    }

    GLvoid CScale::init(Node* node)
    {
        if(node != nullptr)
            node->Init();
    }

    GLvoid CScale::init(const GLint& param, Node* node)
    {
        if(node != nullptr)
            node->Init(param);
    }

    GLvoid CScale::init(glm::mat4& transform, Node* node)
    {
        if(node != nullptr)
            node->Init(transform);

        transform = Update(transform);
    }

    GLvoid CScale::draw(const GLuint* array, Node* node)
    {
        if(node != nullptr)
            node->Draw(array);
    }

    GLvoid CScale::draw(const GLuint& shader_program, Node* node)
    {
        if(node != nullptr)
            node->Draw(shader_program);
    }

    GLvoid CScale::draw(const GLuint& shader_program, const GLuint* array, Node* node)
    {
        if(node != nullptr)
            node->Draw(shader_program, array);
    }

    GLvoid CScale::draw(Node* node)
    {
        if(node != nullptr)
            node->Draw();
    }

    GLvoid CScale::update(Node* node)
    {
        if(node != nullptr)
            node->Update();
    }

    GLvoid CScale::update(glm::mat4& transform, Node* node)
    {
        if(node != nullptr)
            node->Update(transform);

        transform = Update(transform);
    }

    GLvoid CScale::Set(const GLfloat& x, const GLfloat& y, const GLfloat& z)
    {
        m_x = x;
        m_y = y;
        m_z = z;
    }

    GLvoid CScale::Set(const GLfloat& scale)
    {
        m_x = scale;
        m_y = scale;
        m_z = scale;
    }

    glm::mat4 CScale::Update(const glm::mat4& transform)
    {
        return glm::scale(transform, glm::vec3(m_x, m_y, m_z));
    }
}