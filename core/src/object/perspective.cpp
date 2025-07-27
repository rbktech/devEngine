#include "core/object/perspective.h"

#include <GL/glew.h>

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/error.h"

#include "core/object/shader.h"

namespace core
{
    CPerspective::CPerspective()
        : m_fovy(45.0f)
        , m_aspect(1.0f)
        , m_near(0.1f)
        , m_far(100.0f)
    {
    }

    GLvoid CPerspective::init(Node* node)
    {
        Update();

        if(node != nullptr)
            node->Init();
    }

    GLvoid CPerspective::init(const GLint& param, Node* node)
    {
        Update();

        if(node != nullptr)
            node->Init(param);
    }

    GLvoid CPerspective::init(glm::mat4& transform, Node* node)
    {
        Update();

        if(node != nullptr)
            node->Init(transform);
    }

    GLvoid CPerspective::draw(Node* node)
    {
        if(node != nullptr)
            node->Draw();
    }

    GLvoid CPerspective::draw(const GLuint* array, Node* node)
    {
        if(node != nullptr)
            node->Draw(array);
    }

    GLvoid CPerspective::draw(const GLuint& shader_program, Node* node)
    {
        CShaderProgram::Update(shader_program, "u_projection", glm::value_ptr(m_projection));

        if(node != nullptr)
            node->Draw(shader_program);
    }

    GLvoid CPerspective::draw(const GLuint& shader_program, const GLuint* array, Node* node)
    {
        CShaderProgram::Update(shader_program, "u_projection", glm::value_ptr(m_projection));

        if(node != nullptr)
            node->Draw(shader_program, array);
    }

    GLvoid CPerspective::update(Node* node)
    {
        if(node != nullptr)
            node->Update();

        Update();
    }

    GLvoid CPerspective::update(glm::mat4& transform, Node* node)
    {
        if(node != nullptr)
            node->Update(transform);

        Update();
    }

    GLvoid CPerspective::Bind()
    {
    }

    GLvoid CPerspective::UnBind()
    {
    }

    GLuint CPerspective::Get()
    {
        return 0;
    }

    // -------------------------------------------------------------------

    GLvoid CPerspective::Set(const GLfloat& fovy, const GLfloat& aspect, const GLfloat& near, const GLfloat& far)
    {
        m_fovy = fovy;
        m_aspect = aspect;
        m_near = near;
        m_far = far;
    }

    GLvoid CPerspective::Update()
    {
        m_projection = glm::perspective(glm::radians(m_fovy), m_aspect, m_near, m_far);
    }
}