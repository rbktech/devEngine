#include "core/object/matrix.h"

#include <GL/glew.h>

#include "core/error.h"

namespace core
{
    CMatrix::CMatrix(const glm::mat4& transform)
        : m_transform(transform)
    {
    }

    GLvoid CMatrix::init(Node* node)
    {
        if(node != nullptr)
            node->Init();
    }

    GLvoid CMatrix::init(const GLint& param, Node* node)
    {
        if(node != nullptr)
            node->Init();
    }

    GLvoid CMatrix::init(glm::mat4& transform, Node* node)
    {
        throw std::runtime_error("error: wrong call: GLvoid CMatrix::init(glm::mat4& transform, Node* node)");
    }

    GLvoid CMatrix::draw(Node* node)
    {
        e(glPushMatrix());

        if(node != nullptr)
            node->Draw();

        e(glPopMatrix());
    }

    GLvoid CMatrix::draw(const GLuint* array, Node* node)
    {
        e(glPushMatrix());

        if(node != nullptr)
            node->Draw(array);

        e(glPopMatrix());
    }

    GLvoid CMatrix::draw(const GLuint& shader_program, Node* node)
    {
        throw std::runtime_error("error: wrong call: GLvoid CMatrix::draw(const GLuint& shader_program, Node* node)");
    }

    GLvoid CMatrix::draw(const GLuint& shader_program, const GLuint* array, Node* node)
    {
        throw std::runtime_error("error: wrong call: GLvoid CMatrix::draw(const GLuint& shader_program, const GLuint* array, Node* node)");
    }

    GLvoid CMatrix::update(Node* node)
    {
        if(node != nullptr)
            node->Update();
    }

    GLvoid CMatrix::update(glm::mat4& transform, Node* node)
    {
        throw std::runtime_error("error: wrong call: GLvoid CMatrix::update(glm::mat4& transform, Node* node)");
    }

    GLvoid CMatrix::Set(const glm::mat4& transform)
    {
        m_transform = transform;
    }
}