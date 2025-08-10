#pragma once

#include <vector>

#include "core/object/buffer.h"
#include "core/type.h"

namespace core
{
    class CShader : public CData
    {
    private:
        GLuint m_type;
        GLuint m_shader;

        GLvoid init(Node*) final {};
        GLvoid init(const GLint&, Node*) final {};
        GLvoid init(glm::mat4&, Node*) final {};

        GLvoid draw(Node*) final {};
        GLvoid draw(const GLuint*, Node*) final {};
        GLvoid draw(const GLuint&, Node*) final {};
        GLvoid draw(const GLuint&, const GLuint*, Node*) final {};

        GLvoid update(Node*) final {};
        GLvoid update(glm::mat4&, Node*) final {};

        GLvoid Bind() final {};
        GLvoid UnBind() final {};

    public:
        CShader(const GLchar* shader, const GLint& size, const GLint& type);
        ~CShader() override;

        enum {
            Vertex,
            Fragment,
        };

        GLint Create();

        GLuint Get() final;

        static const GLchar* GetType(const GLint& type);

        static GLint Type(const GLint& type);
    };
}

namespace core
{
    class CShaderProgram : public CBBO
    {
    private:
        GLuint m_shader_program;

        std::vector<CShader*> m_list_shaders;

        GLvoid CLear();

        GLvoid init(Node* node) final;
        GLvoid init(const GLint& param, Node* node) final;
        GLvoid init(glm::mat4& transform, Node* node) final;

        GLvoid draw(Node* node) final;
        GLvoid draw(const GLuint* array, Node* node) final;
        GLvoid draw(const GLuint& shader_program, Node* node) final;
        GLvoid draw(const GLuint& shader_program, const GLuint* array, Node* node) final;

        GLvoid update(Node* node) final;
        GLvoid update(glm::mat4& transform, Node* node) final;

        GLvoid Bind() final {};
        GLvoid UnBind() final {};

        GLint Create();

    public:
        CShaderProgram();
        ~CShaderProgram() override;

        GLuint Get() final;

        GLvoid Set(const GLchar* shader, const GLint& size, const GLint& type);

        GLint GetLocation(const GLchar* name);

        GLvoid Update(const GLchar* name, const GLfloat* value);

        static GLint GetLocation(const GLuint& shader_program, const GLchar* name);

        static GLvoid Update(const GLuint& shader_program, const GLchar* name, const GLfloat* value);

        GLvoid Use();

        GLvoid SetTexture(const GLchar* name, const GLint& value);
    };
}