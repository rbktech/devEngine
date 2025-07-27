#include "core/object/orthographic.h"

#include <GL/glew.h>

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/error.h"

#include "core/object/shader.h"

namespace core
{
    COrthographic::COrthographic()
        : m_left(0.0f)
        , m_right(0.0f)
        , m_bottom(0.0f)
        , m_top(0.0f)
        , m_near(0.0f)
        , m_far(0.0f)
    {
    }

    GLvoid COrthographic::init(Node* node)
    {
        Update();

        if(node != nullptr)
            node->Init();
    }

    GLvoid COrthographic::init(const GLint& param, Node* node)
    {
        Update();

        if(node != nullptr)
            node->Init(param);
    }

    GLvoid COrthographic::init(glm::mat4& transform, Node* node)
    {
        Update();

        if(node != nullptr)
            node->Init(transform);
    }

    GLvoid COrthographic::draw(Node* node)
    {
        if(node != nullptr)
            node->Draw();
    }

    GLvoid COrthographic::draw(const GLuint* array, Node* node)
    {
        if(node != nullptr)
            node->Draw(array);
    }

    GLvoid COrthographic::draw(const GLuint& shader_program, Node* node)
    {
        CShaderProgram::Update(shader_program, "u_projection", glm::value_ptr(m_orthographic));

        if(node != nullptr)
            node->Draw(shader_program);
    }

    GLvoid COrthographic::draw(const GLuint& shader_program, const GLuint* array, Node* node)
    {
        CShaderProgram::Update(shader_program, "u_projection", glm::value_ptr(m_orthographic));

        if(node != nullptr)
            node->Draw(shader_program, array);
    }

    GLvoid COrthographic::update(Node* node)
    {
        if(node != nullptr)
            node->Update();

        Update();
    }

    GLvoid COrthographic::update(glm::mat4& transform, Node* node)
    {
        if(node != nullptr)
            node->Update(transform);

        Update();
    }

    GLvoid COrthographic::Bind()
    {
    }

    GLvoid COrthographic::UnBind()
    {
    }

    GLuint COrthographic::Get()
    {
        return 0;
    }

    GLvoid COrthographic::Set(const GLfloat& left,
        const GLfloat& right,
        const GLfloat& bottom,
        const GLfloat& top,
        const GLfloat& near,
        const GLfloat& far)
    {
        m_left = left;
        m_right = right;
        m_bottom = bottom;
        m_top = top;
        m_near = near;
        m_far = far;
    }

    GLvoid COrthographic::Update()
    {
        m_orthographic = glm::ortho(m_left, m_right, m_bottom, m_top, m_near, m_far);
    }
}