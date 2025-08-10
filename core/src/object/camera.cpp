#include "core/object/camera.h"

#include <GL/glew.h>

// #include <glm/ext/matrix_float4x4.hpp>
// #include <glm/gtc/type_ptr.hpp>

// #include "core/error.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "core/object/shader.h"

namespace core
{
    CCamera::CCamera()
    {
    }

    GLvoid CCamera::init(Node* node)
    {
        Update();

        if(node != nullptr)
            node->Init();
    }

    GLvoid CCamera::init(const GLint& param, Node* node)
    {
        Update();

        if(node != nullptr)
            node->Init(param);
    }

    GLvoid CCamera::init(glm::mat4& transform, Node* node)
    {
        Update();

        if(node != nullptr)
            node->Init();
    }

    GLvoid CCamera::draw(Node* node)
    {
        if(node != nullptr)
            node->Draw();
    }

    GLvoid CCamera::draw(const GLuint* array, Node* node)
    {
        if(node != nullptr)
            node->Draw(array);
    }

    GLvoid CCamera::draw(const GLuint& shader_program, Node* node)
    {
        CShaderProgram::Update(shader_program, "u_view", glm::value_ptr(m_view));

        if(node != nullptr)
            node->Draw(shader_program);
    }

    GLvoid CCamera::draw(const GLuint& shader_program, const GLuint* array, Node* node)
    {
        CShaderProgram::Update(shader_program, "u_view", glm::value_ptr(m_view));

        if(node != nullptr)
            node->Draw(shader_program, array);
    }

    GLvoid CCamera::update(Node* node)
    {
        if(node != nullptr)
            node->Update();

        Update();
    }

    GLvoid CCamera::update(glm::mat4& transform, Node* node)
    {
        if(node != nullptr)
            node->Update(transform);

        Update();
    }

    GLvoid CCamera::Update()
    {
        m_view = glm::lookAt(mCameraEye, mCameraCenter, mCameraUp);
    }

    void CCamera::Refresh()
    {
        mCameraEye.x = mCameraCenter.x + mRadius * glm::sin(glm::radians(mYaw)) * glm::cos(glm::radians(mPitch));
        mCameraEye.y = mCameraCenter.y + mRadius * glm::sin(glm::radians(mPitch));
        mCameraEye.z = mCameraCenter.z + mRadius * glm::cos(glm::radians(mYaw)) * glm::cos(glm::radians(mPitch));

        mCameraFront = glm::normalize(mCameraCenter - mCameraEye);
    }

    GLvoid CCamera::Set()
    {
    }

    GLvoid CCamera::Set(const TMove& move)
    {
        glm::vec3 right = glm::cross(mCameraFront, mCameraUp);

        mCameraCenter +=               //
            move.x * right +       // движение влево/вправо
            move.z * mCameraFront; // движение вперед/назад

        Refresh();
    }

    GLvoid CCamera::Set(const TRotate& rotate)
    {
        GLfloat pitch = mPitch + rotate.pitch;
        GLfloat yaw = mYaw + rotate.yaw;

        if(-90 < pitch && pitch < 90.0f) {
            mPitch = pitch;
            mYaw = yaw;
            Refresh();
        }
    }

    GLvoid CCamera::Set(const TCentre& center)
    {
        mCameraCenter = glm::vec3(center.x, center.x, center.y);
        Refresh();
    }

    GLvoid CCamera::Set(const TRadius& radius)
    {
        mRadius = radius.value;
        Refresh();
    }

    GLuint CCamera::Get()
    {
        return 0;
    }

    GLvoid CCamera::Bind()
    {
    }

    GLvoid CCamera::UnBind()
    {
    }
}