#include "core/object/texture.h"

#include <GL/glew.h>

#include "core/error.h"

namespace core
{
    CTexture::CTexture()
    {
        e(glGenTextures(1, &m_texture));
    }

    CTexture::CTexture(const GLvoid* data,
        const GLsizei& size,
        const GLint& width,
        const GLint& height,
        const GLint& offset,
        const GLint& bits,
        GLvoid (CTexture::*param)())
    {
        m_data = data;
        m_size = size;
        m_width = width;
        m_height = height;
        m_offset = offset;
        m_bits = bits;
        Param = param;
    }

    CTexture::~CTexture()
    {
        e(glDeleteTextures(1, &m_texture));
    }

    GLvoid CTexture::Create(const GLubyte* data, const GLint& w, const GLint& h, const GLint& offset, const GLint& bits)
    {
        if(bits == 32)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, data + offset);
        else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, data + offset);
    }

    GLvoid CTexture::CreateBuffer(const GLchar* img, const GLint& w, const GLint& h)
    {
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, w, h, 0, GL_RGB,  GL_UNSIGNED_BYTE, img + 54);
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img + 54);
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,  w, h, 0, GL_RGB,  GL_UNSIGNED_BYTE, img + 54);
    }

    GLvoid CTexture::ParamBase()
    {
        // glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); // Legacy

        // glPixelStore устанавливает режимы хранения пикселей,
        // которые влияют на работу последующего glReadPixels,
        // а также на распаковку текстурных шаблонов.

        // glPixelStorei Указывает требования к выравниванию начала каждой строки пикселей в памяти.
        // Допустимые значения: 1 (выравнивание по байтам), 2, 3, 4

        // glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Выравнивание по одному байту.

        // GL_REPEAT - метод обтекания по умолчанию.

        // GL_TEXTURE_WRAP_S - координаты по s
        // GL_TEXTURE_WRAP_T - координаты по t
        // GL_TEXTURE_WRAP_R - координаты по r для 3D

        // Установка параметров наложения текстуры.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // Установка параметров фильтрации текстуры.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Уменьшающий фильтр.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Увеличивающий фильтр.
    }

    GLvoid CTexture::ParamRepeatNearest()
    {
        // Установка параметров наложения текстуры.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // Установка параметров фильтрации текстуры.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    GLvoid CTexture::ParamRepeatLinear()
    {
        // Установка параметров наложения текстуры.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // Установка параметров фильтрации текстуры.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    GLvoid CTexture::ParamMipMap()
    {
        // Установить параметры наложения текстуры.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Повторяет текстуру.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Повторяет текстуру.
        // Установить параметры фильтрации текстур.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Мипмап нельзя устанавливать в увеличивающий фильтр !!!
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR); !!!

        glGenerateMipmap(GL_TEXTURE_2D);
    }

    GLvoid CTexture::Bind()
    {
        e(glBindTexture(GL_TEXTURE_2D, m_texture));
    }

    GLvoid CTexture::UnBind()
    {
        e(glBindTexture(GL_TEXTURE_2D, 0));
    }

    GLvoid CTexture::Enable()
    {
        e(glEnable(GL_TEXTURE_2D));
    }

    GLvoid CTexture::Disable()
    {
        e(glDisable(GL_TEXTURE_2D));
    }

    GLvoid CTexture::init(Node* node)
    {
        if(m_data != nullptr && m_size > 0) {

            CTexture::Bind();
            CTexture::Create((GLubyte*)m_data, m_width, m_height, m_offset, m_bits);
            (this->*Param)();
            CTexture::UnBind();
        }

        if(node != nullptr)
            node->Init();
    }

    GLvoid CTexture::init(const GLint& param, Node* node)
    {
        if(m_data != nullptr && m_size > 0) {

            CTexture::Bind();
            CTexture::Create((GLubyte*)m_data, m_width, m_height, m_offset, m_bits);
            (this->*Param)();
            CTexture::UnBind();
        }

        if(node != nullptr)
            node->Init(param);
    }

    GLvoid CTexture::init(glm::mat4& transform, Node* node)
    {
        if(m_data != nullptr && m_size > 0) {

            CTexture::Bind();
            CTexture::Create((GLubyte*)m_data, m_width, m_height, m_offset, m_bits);
            (this->*Param)();
            CTexture::UnBind();
        }

        if(node != nullptr)
            node->Init(transform);
    }

    GLvoid CTexture::draw(Node* node)
    {
        CTexture::Bind();

        if(node != nullptr)
            node->Draw();

        CTexture::UnBind();
    }

    GLvoid CTexture::draw(const GLuint* array, Node* node)
    {
        CTexture::Bind();

        if(node != nullptr)
            node->Draw(array);

        CTexture::UnBind();
    }

    GLvoid CTexture::draw(const GLuint& shader_program, Node* node)
    {
        CTexture::Bind();

        if(node != nullptr)
            node->Draw(shader_program);

        CTexture::UnBind();
    }

    GLvoid CTexture::draw(const GLuint& shader_program, const GLuint* array, Node* node)
    {
        CTexture::Bind();

        if(node != nullptr)
            node->Draw(shader_program, array);

        CTexture::UnBind();
    }

    GLvoid CTexture::update(Node* node)
    {
        if(node != nullptr)
            node->Update();
    }

    GLvoid CTexture::update(glm::mat4& transform, Node* node)
    {
        if(node != nullptr)
            node->Update(transform);
    }

    GLuint CTexture::Get()
    {
        return m_texture;
    }

    GLvoid CTexture::Set(const GLvoid* data,
        const GLsizei& size,
        const GLint& width,
        const GLint& height,
        const GLint& offset,
        const GLint& bits,
        GLvoid (CTexture::*param)())
    {
        m_data = data;
        m_size = size;
        m_width = width;
        m_height = height;
        m_offset = offset;
        m_bits = bits;
        Param = param;
    }
}