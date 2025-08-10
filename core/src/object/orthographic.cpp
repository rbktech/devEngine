#include "core/object/orthographic.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/object/shader.h"

#include "core/matrixglm.h"

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

    GLvoid COrthographic::Set(const TMoveXY& moveXY)
    {
        m_left += moveXY.x;
        m_right += moveXY.x;
        m_bottom += moveXY.y;
        m_top += moveXY.y;
    }

    GLvoid COrthographic::Set(const TSize& size)
    {
        m_right = m_left + size.w;
        m_top = m_bottom + size.h;
    }

    GLvoid COrthographic::Set(const TScale& scale)
    {
        GLfloat width = std::abs(m_right - m_left);
        GLfloat height = std::abs(m_top - m_bottom);
        const GLfloat aspect = width / height;

        // height = scale.value;
        // width = height * aspect;

        width = scale.value;
        height = width / aspect;

        const GLfloat left = m_left - width;
        const GLfloat right = m_right + width;
        const GLfloat bottom = m_bottom - height;
        const GLfloat top = m_top + height;

        if(left < right && bottom < top) {

            m_left = left;
            m_right = right;
            m_bottom = bottom;
            m_top = top;
        }
    }

    GLvoid COrthographic::Update()
    {
        m_orthographic = glm::ortho(m_left, m_right, m_bottom, m_top, m_near, m_far);
    }

    glm::mat4 COrthographic::GetMatrix()
    {
        return m_orthographic;
    }

    glm::vec3 COrthographic::ToWorldCoord(const GLfloat& x, const GLfloat& y, const GLfloat& w, const GLfloat& h)
    {
        GLfloat ndcX = (2.0f * x) / w - 1.0f;
        GLfloat ndcY = 1.0f - (2.0f * y) / h;

        glm::vec4 rayCentreNDC(ndcX, ndcY, 0.0f, 1.0f);

        glm::mat4 inverseVP = glm::inverse(m_orthographic);

        return inverseVP * rayCentreNDC;
    }
}