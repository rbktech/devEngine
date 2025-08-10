#pragma once

#include "core/object/bbo.h"

namespace core
{
    class CCamera : public CBBO
    {
    public:
        struct TMoveXZ {
            GLfloat x;
            GLfloat z;
        };

        struct TMoveXY {
            GLfloat x;
            GLfloat y;
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

    private:
        glm::mat4 m_view;

        GLfloat mRadius;

        glm::vec3 mCameraEye;
        glm::vec3 mCameraFront;
        glm::vec3 mCameraCenter;
        glm::vec3 mCameraUp;

        GLfloat mPitch; // Угол тангаж (в градусах)
        GLfloat mYaw;   // Угол рыскание (в градусах)

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

        GLvoid Update();

    public:
        CCamera();
        ~CCamera() override = default;

        GLvoid Set();

        GLvoid Set(const TMoveXZ& move);

        GLvoid Set(const TMoveXY& move);

        GLvoid Set(const TRotate& rotate);

        GLvoid Set(const TCentre& center);

        GLvoid Set(const TRadius& radius);

        glm::mat4 GetMatrix();
    };
}