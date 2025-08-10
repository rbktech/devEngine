#include "core/object/translate.h"

#include <GL/glew.h>

#include <glm/ext/matrix_transform.hpp>

#include "core/error.h"

namespace core
{
    GLvoid CTranslate::init(Node* node)
    {
        throw std::runtime_error("error: wrong call: GLvoid CTranslate::init(Node* node)");
    }

    GLvoid CTranslate::init(const GLint& param, Node* node)
    {
        throw std::runtime_error("error: wrong call: GLvoid CTranslate::init(const GLint& param, Node* node)");
    }

    GLvoid CTranslate::init(glm::mat4& transform, Node* node)
    {
        if(node != nullptr)
            node->Init(transform);

        transform = glm::translate(transform, { m_x, m_y, m_z });
    }

    GLvoid CTranslate::draw(Node* node)
    {
        // e(glTranslatef(m_x, m_y, m_z));

        if(node != nullptr)
            node->Draw();
    }

    GLvoid CTranslate::draw(const GLuint* array, Node* node)
    {
        // e(glTranslatef(m_x, m_y, m_z));

        if(node != nullptr)
            node->Draw(array);
    }

    GLvoid CTranslate::draw(const GLuint& shader_program, Node* node)
    {
        if(node != nullptr)
            node->Draw(shader_program);
    }

    GLvoid CTranslate::draw(const GLuint& shader_program, const GLuint* array, Node* node)
    {
        if(node != nullptr)
            node->Draw(shader_program, array);
    }

    GLvoid CTranslate::update(Node* node)
    {
        if(node != nullptr)
            node->Update();
    }

    GLvoid CTranslate::update(glm::mat4& transform, Node* node)
    {
        if(node != nullptr)
            node->Update(transform);

        transform = glm::translate(transform, { m_x, m_y, m_z });
    }
}