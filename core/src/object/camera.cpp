#include "core/object/camera.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/object/shader.h"

namespace core
{
    CCamera::CCamera()
        : m_view(glm::mat4(1.0f))
        , mRadius(3.0f)
        , mCameraEye(0.0f, 0.0f, mRadius)
        , mCameraFront(0.0f, 0.0f, 1.0f)
        , mCameraCenter(0.0f, 0.0f, 0.0f)
        , mCameraUp(0.0f, 1.0f, 0.0f)
        , mPitch(0.0f)
        , mYaw(0.0f)
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

    GLvoid CCamera::Set(const TMoveXZ& move)
    {
        glm::vec3 right = glm::cross(mCameraFront, mCameraUp);

        mCameraCenter +=           //
            move.x * right +       // движение влево/вправо
            move.z * mCameraFront; // движение вперед/назад

        Refresh();
    }

    GLvoid CCamera::Set(const TMoveXY& move)
    {
        glm::vec3 right = glm::cross(mCameraFront, mCameraUp);

        mCameraCenter +=        //
            move.x * right +    // движение влево/вправо
            move.y * mCameraUp; // движение вверх/вниз

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

    glm::mat4 CCamera::GetMatrix()
    {
        return m_view;
    }
}