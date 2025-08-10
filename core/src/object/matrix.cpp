#include "core/object/matrix.h"

#include <GL/glew.h>

#include <glm/gtc/type_ptr.hpp>

#include "core/error.h"

#include "core/matrixglm.h"
#include "core/object/shader.h"

namespace core
{
    GLvoid CMatrix::init(Node* node)
    {
        if(node != nullptr)
            node->Init(m_transform);
    }

    GLvoid CMatrix::init(const GLint& param, Node* node)
    {
        if(node != nullptr)
            node->Init(m_transform);
    }

    GLvoid CMatrix::init(glm::mat4& transform, Node* node)
    {
        throw std::runtime_error("error: wrong call: GLvoid CMatrix::init(glm::mat4& transform, Node* node)");
    }

    GLvoid CMatrix::draw(Node* node)
    {
        if(node != nullptr)
            node->Draw();
    }

    GLvoid CMatrix::draw(const GLuint* array, Node* node)
    {
        // e(glPushMatrix());

        if(node != nullptr)
            node->Draw(array);

        // e(glPopMatrix());
    }

    GLvoid CMatrix::draw(const GLuint& shader_program, Node* node)
    {
        CShaderProgram::Update(shader_program, "u_model", glm::value_ptr(m_transform));

        if(node != nullptr)
            node->Draw(shader_program);
    }

    GLvoid CMatrix::draw(const GLuint& shader_program, const GLuint* array, Node* node)
    {
        CShaderProgram::Update(shader_program, "u_model", glm::value_ptr(m_transform));

        if(node != nullptr)
            node->Draw(shader_program, array);
    }

    GLvoid CMatrix::update(Node* node)
    {
        CMatrix::Set();

        if(node != nullptr)
            node->Update(m_transform);
    }

    GLvoid CMatrix::update(glm::mat4& transform, Node* node)
    {
        throw std::runtime_error("error: wrong call: GLvoid CMatrix::update(glm::mat4& transform, Node* node)");
    }
}