#include "core/object/translate.h"

#include <GL/glew.h>

#include "core/error.h"

namespace core
{
    CTranslate::CTranslate()
        : m_x(0.0f)
        , m_y(0.0f)
        , m_z(0.0f)
    {
    }

    CTranslate::CTranslate(const GLfloat& x, const GLfloat& y, const GLfloat& z)
        : m_x(x)
        , m_y(y)
        , m_z(z)
    {
    }

    GLvoid CTranslate::init(Node* node)
    {
        if(node != nullptr)
            node->Init();
    }

    GLvoid CTranslate::init(const GLint& param, Node* node)
    {
        if(node != nullptr)
            node->Init(param);
    }

    GLvoid CTranslate::init(glm::mat4& transform, Node* node)
    {
        throw std::runtime_error("error: wrong call: GLvoid CTranslate::init(glm::mat4& transform, Node* node)");
    }

    GLvoid CTranslate::draw(Node* node)
    {
        e(glTranslatef(m_x, m_y, m_z));

        if(node != nullptr)
            node->Draw();
    }

    GLvoid CTranslate::draw(const GLuint* array, Node* node)
    {
        e(glTranslatef(m_x, m_y, m_z));

        if(node != nullptr)
            node->Draw(array);
    }

    GLvoid CTranslate::draw(const GLuint& shader_program, Node* node)
    {
        throw std::runtime_error("error: wrong call: GLvoid CTranslate::draw(const GLuint& shader_program, Node* node)");
    }

    GLvoid CTranslate::draw(const GLuint& shader_program, const GLuint* array, Node* node)
    {
        throw std::runtime_error("error: wrong call: GLvoid CTranslate::draw(const GLuint& shader_program, const GLuint* array, Node* node)");
    }

    GLvoid CTranslate::update(Node* node)
    {
        if(node != nullptr)
            node->Update();
    }

    GLvoid CTranslate::update(glm::mat4& transform, Node* node)
    {
        throw std::runtime_error("error: wrong call: GLvoid CTranslate::update(glm::mat4& transform, Node* node)");
    }

    GLvoid CTranslate::Bind()
    {
    }

    GLvoid CTranslate::UnBind()
    {
    }

    GLuint CTranslate::Get()
    {
        return 0;
    }

    GLvoid CTranslate::Set(const GLfloat& x, const GLfloat& y, const GLfloat& z)
    {
        m_x = x;
        m_y = y;
        m_z = z;
    }
}