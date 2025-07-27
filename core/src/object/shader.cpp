#include "core/object/shader.h"

#include <iostream>

#include <GL/glew.h>

#include <core/resources.h>

#define SIZE_LOG 1024

namespace core
{
    CShader::CShader(const GLchar* shader, const GLint& size, const GLint& type)
        : CData(shader, size)
        , m_type(type)
        , m_shader(0)
    {
    }

    CShader::~CShader()
    {
        glDeleteShader(m_shader);
    }

    GLuint CShader::Get()
    {
        return m_shader;
    }

    GLint CShader::Type(const GLint& type)
    {
        switch(type) {
            case core::ShaderVertex:
                return GL_VERTEX_SHADER;
            case core::ShaderFragment:
                return GL_FRAGMENT_SHADER;
            default:
                return 0;
        }
    }

    const GLchar* CShader::GetType(const GLint& type)
    {
        switch(type) {
            case GL_VERTEX_SHADER:
                return "GL_VERTEX_SHADER";
            case GL_FRAGMENT_SHADER:
                return "GL_FRAGMENT_SHADER";
            default:
                return "GL_UNKNOWN_SHADER";
        }
    }

    // GLint CShader::Create(const GLchar* shader, const GLint& size, const GLint& type)
    GLint CShader::Create()
    {
        GLint compiled = 0;
        GLchar message[SIZE_LOG];

        const GLchar* shader = static_cast<const GLchar*>(m_data);

        m_shader = glCreateShader(m_type);

        glShaderSource(m_shader, 1, &shader, &m_size);

        glCompileShader(m_shader);

        glGetShaderiv(m_shader, GL_COMPILE_STATUS, &compiled);
        if(compiled != GL_TRUE) {
            glGetShaderInfoLog(m_shader, SIZE_LOG, nullptr, message);

            std::cout << "ERROR::COMPILATION_FAILED::" << GetType(m_type) << std::endl << message << std::endl;

            return 1;
        }

        return 0;
    }
}

// -----------------------------------------------------------------------

namespace core
{
    CShaderProgram::CShaderProgram()
        : m_shader_program(0)
    {
    }

    CShaderProgram::~CShaderProgram()
    {
        CLear();

        glDeleteProgram(m_shader_program);
    }

    GLvoid CShaderProgram::CLear()
    {
        for(const auto& shader : m_list_shaders)
            delete shader;

        m_list_shaders.clear();
    }

    /*GLint CShaderProgram::Add(const GLchar* shader, const GLint& size, const GLint& type)
    {
        GLint result = 0;
        CShader* objShader = new CShader();

        result = objShader->Create(shader, size, type);
        if(result == 0)
            m_list_shaders.push_back(objShader);
        else
            delete objShader;

        return result;
    }*/

    GLint CShaderProgram::Create()
    {
        GLint linked;
        GLint compiled;
        GLchar message[SIZE_LOG];

        for(auto& shader : m_list_shaders) {
            compiled = shader->Create();
            if(compiled != 0) {
                delete shader;
                throw std::runtime_error(std::string("error: compiled shader: ") + core::CShader::GetType(0));
            }
        }

        m_shader_program = glCreateProgram();

        for(auto& shader : m_list_shaders)
            glAttachShader(m_shader_program, shader->Get());

        glLinkProgram(m_shader_program);

        glGetProgramiv(m_shader_program, GL_LINK_STATUS, &linked);

        CLear();

        if(linked != GL_TRUE) {
            glGetProgramInfoLog(m_shader_program, SIZE_LOG, nullptr, message);

            std::cout << "ERROR::LINKING_FAILED::GL_PROGRAM_SHADER" << std::endl << message << std::endl;

            return 1;
        }

        return 0;
    }

    GLvoid CShaderProgram::Use()
    {
        glUseProgram(m_shader_program);
    }

    GLvoid CShaderProgram::Set(const GLchar* shader, const GLint& size, const GLint& type)
    {
        m_list_shaders.emplace_back(new CShader(shader, size, type));
    }

    GLvoid CShaderProgram::init(Node* node)
    {
        if(m_list_shaders.empty() == false)
            CShaderProgram::Create();

        if(node != nullptr)
            node->Init();
    }

    GLvoid CShaderProgram::init(const GLint& param, Node* node)
    {
        if(m_list_shaders.empty() == false)
            CShaderProgram::Create();

        if(node != nullptr)
            node->Init(param);
    }

    GLvoid CShaderProgram::init(glm::mat4& transform, Node* node)
    {
        if(m_list_shaders.empty() == false)
            CShaderProgram::Create();

        if(node != nullptr)
            node->Init(transform);
    }

    GLuint CShaderProgram::Get()
    {
        return m_shader_program;
    }

    GLint CShaderProgram::GetLocation(const GLchar* name)
    {
        GLint location = glGetUniformLocation(m_shader_program, name);
        if(location == -1)
            throw std::runtime_error(std::string("Shader does not contain variable ") + name);

        return location;
    }

    GLvoid CShaderProgram::SetTexture(const GLchar* name, const GLint& value)
    {
        glUniform1i(GetLocation(m_shader_program, name), value);
    }

    GLvoid CShaderProgram::Update(const GLchar* name, const GLfloat* value)
    {
        glUniformMatrix4fv(GetLocation(m_shader_program, name), 1, GL_FALSE, value);
    }

    // --------------------------------------------

    GLint CShaderProgram::GetLocation(const GLuint& shader_program, const GLchar* name)
    {
        GLint location = glGetUniformLocation(shader_program, name);
        if(location == -1)
            throw std::runtime_error(std::string("Shader does not contain variable ") + name);

        return location;
    }

    GLvoid CShaderProgram::Update(const GLuint& shader_program, const GLchar* name, const GLfloat* value)
    {
        glUniformMatrix4fv(GetLocation(shader_program, name), 1, GL_FALSE, value);
    }

    // --------------------

    GLvoid CShaderProgram::draw(const GLuint* array, Node* node)
    {
        CShaderProgram::Use();

        if(node != nullptr)
            node->Draw(m_shader_program, array);
    }

    GLvoid CShaderProgram::draw(const GLuint& shader_program, const GLuint* array, Node* node)
    {
        CShaderProgram::Use();

        if(node != nullptr)
            node->Draw(m_shader_program, array);
    }

    GLvoid CShaderProgram::draw(const GLuint& shader_program, Node* node)
    {
        if(m_shader_program != shader_program)
            throw std::runtime_error("error: conflict shader program");

        CShaderProgram::Use();

        if(node != nullptr)
            node->Draw(shader_program);
    }

    GLvoid CShaderProgram::draw(Node* node)
    {
        CShaderProgram::Use();

        if(node != nullptr)
            node->Draw(m_shader_program);
    }

    GLvoid CShaderProgram::update(Node* node)
    {
        if(node != nullptr)
            node->Update();
    }

    GLvoid CShaderProgram::update(glm::mat4& transform, Node* node)
    {
        if(node != nullptr)
            node->Update(transform);
    }
}