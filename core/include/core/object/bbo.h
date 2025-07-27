#pragma once

// #include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_float4x4.hpp>

#include "core/type.h"

#include <iostream>
#include <map>
#include <typeinfo>

namespace core
{
    enum {
        Elements = 1,
        Array = 1,
        Translate,
        Rotate,
        Scale,
        Matrix,
        EBO,
        Buffer,
        TBO,
        CBO,
        VBO,
        VAO,
        RBO,
        FBO,
        Texture,
        Perspective = 20,
        Orthographic = 20,
        Camera,
        Shader, // ShaderProgram,
    }; // Снизу вверх идет обход объектов

    /*
     * Base buffer object
     */
    class CBBO
    {
    public:
        class Node
        {
        private:
            Node* m_node = nullptr;
            CBBO* m_object = nullptr;

        public:
            explicit Node(CBBO* object)
                : m_object(object)
            {
            }
            ~Node() = default;

            void Delete()
            {
                if(m_node != nullptr) {
                    m_node->Delete();
                    delete m_node;
                }
            }

            void SetNode(Node* node)
            {
                m_node = node;
            }

            void Init()
            {
                if(m_object != nullptr)
                    m_object->init(m_node);
            }

            void Init(const int& param)
            {
                if(m_object != nullptr)
                    m_object->init(param, m_node);
            }

            void Init(glm::mat4& transform)
            {
                if(m_object != nullptr)
                    m_object->init(transform, m_node);
            }

            void Draw(const GLuint& shader, const GLuint* array)
            {
                if(m_object != nullptr)
                    m_object->draw(shader, array, m_node);
            }

            void Draw(const GLuint* array)
            {
                if(m_object != nullptr)
                    m_object->draw(array, m_node);
            }

            void Draw(const GLuint& shader)
            {
                if(m_object != nullptr)
                    m_object->draw(shader, m_node);
            }

            void Draw()
            {
                if(m_object != nullptr)
                    m_object->draw(m_node);
            }

            void Update(glm::mat4& transform)
            {
                if(m_object != nullptr)
                    m_object->update(transform, m_node);
            }

            void Update()
            {
                if(m_object != nullptr)
                    m_object->update(m_node);
            }
        };

    private:
        // GLenum m_type = 0;

    protected:
        virtual GLvoid init(Node* node) = 0;
        virtual GLvoid init(const GLint& param, Node* node) = 0;
        virtual GLvoid init(glm::mat4& transform, Node* node) = 0;

        virtual GLvoid draw(Node* node) = 0;
        virtual GLvoid draw(const GLuint* array, Node* node) = 0;
        virtual GLvoid draw(const GLuint& shader_program, Node* node) = 0;
        virtual GLvoid draw(const GLuint& shader_program, const GLuint* array, Node* node) = 0;

        virtual GLvoid update(Node* node) = 0;
        virtual GLvoid update(glm::mat4& transform, Node* node) = 0;

    public:
        CBBO();
        virtual ~CBBO() = default;

        virtual GLvoid Bind() = 0;
        virtual GLvoid UnBind() = 0;
        virtual GLuint Get() = 0;
        virtual GLvoid Reset();

        GLvoid SetDrawCoordinate(const GLfloat& x, const GLfloat& y, const GLfloat& z = 0);

        GLvoid SetDrawArray(const GLenum& type, const GLsizei& size, const GLsizei& first);

        GLvoid SetDrawElement(const GLenum& type, const GLsizei& size);

        GLvoid DrawArray();

        GLvoid DrawElement(const void* indices = nullptr);
    };
}