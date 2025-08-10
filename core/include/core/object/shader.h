#pragma once

#include <vector>

#include "core/object/buffer.h"
#include "core/type.h"

namespace core
{
    enum {
        ShaderVertex,
        ShaderFragment,
    };

    class CShader : public CData
    {
    private:
        GLuint m_type;
        GLuint m_shader;

        GLvoid init(Node* node) final {};
        GLvoid init(const GLint& param, Node* node) final {};
        GLvoid init(glm::mat4& transform, Node* node) final {};

        GLvoid draw(Node* node) final {};
        GLvoid draw(const GLuint* array, Node* node) final {}
        GLvoid draw(const GLuint& shader_program, Node* node) final {}
        GLvoid draw(const GLuint& shader_program, const GLuint* array, Node* node) final {}

        GLvoid update(Node* node) final {};
        GLvoid update(glm::mat4& transform, Node* node) final {};

        GLvoid Bind() final {};
        GLvoid UnBind() final {};

    public:
        CShader(const GLchar* shader, const GLint& size, const GLint& type);
        ~CShader() override;

        GLint Create();

        GLuint Get() final;

        GLvoid Set() {};

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

        GLint Add(const GLchar* shader, const GLint& size, const GLint& type);

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

    public:
        CShaderProgram();
        ~CShaderProgram() override;

        GLint Create();

        GLvoid Use();

        GLvoid Set(const GLchar* shader, const GLint& size, const GLint& type);

        GLuint Get() final;

        GLint GetLocation(const GLchar* name);

        GLvoid SetTexture(const GLchar* name, const GLint& value);

        GLvoid Update(const GLchar* name, const GLfloat* value);

        static GLint GetLocation(const GLuint& shader_program, const GLchar* name);

        static GLvoid Update(const GLuint& shader_program, const GLchar* name, const GLfloat* value);
    };
}