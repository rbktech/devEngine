#pragma once

#include "core/object/bbo.h"

namespace core
{
    struct TMove {
        GLfloat x;
        GLfloat z;
    };

    struct TRotate {
        GLfloat pitch;
        GLfloat yaw;
    };

    struct TCentre {
        GLfloat x;
        GLfloat y;
        GLfloat z;
    };

    struct TRadius {
        GLfloat value;
    };

    class CCamera : public CBBO
    {
    private:
        glm::mat4 m_view = glm::mat4(1.0f);

        GLfloat mRadius = 3.0f;

        glm::vec3 mCameraEye = { 0.0f, 0.0f, mRadius };
        glm::vec3 mCameraFront = { 0.0f, 0.0f, 1.0f };
        glm::vec3 mCameraCenter = { 0.0f, 0.0f, 0.0f };
        glm::vec3 mCameraUp = { 0.0f, 1.0f, 0.0f };

        GLfloat mPitch = 0.0f; // Угол тангаж (в градусах)
        GLfloat mYaw = 0.0f;   // Угол рыскание (в градусах)

        GLvoid init(Node* node) final;
        GLvoid init(const GLint& param, Node* node) final;
        GLvoid init(glm::mat4& transform, Node* node) final;

        GLvoid draw(Node* node) final;
        GLvoid draw(const GLuint* array, Node* node) final;
        GLvoid draw(const GLuint& shader_program, Node* node) final;
        GLvoid draw(const GLuint& shader_program, const GLuint* array, Node* node) final;

        GLvoid update(Node* node) final;
        GLvoid update(glm::mat4& transform, Node* node) final;

        GLvoid Bind() final;
        GLvoid UnBind() final;
        GLuint Get() final;

        void Refresh();

    public:
        CCamera();
        ~CCamera() override = default;

        GLvoid Set();

        GLvoid Set(const TMove& move);

        GLvoid Set(const TRotate& rotate);

        GLvoid Set(const TCentre& center);

        GLvoid Set(const TRadius& radius);

        GLvoid Update();
    };
}