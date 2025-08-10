#include "core/object/buffer.h"

#include <GL/glew.h>

#include "core/error.h"

namespace core
{
    CData::CData()
        : m_size(0)
        , m_data(nullptr)
    {
    }

    CData::CData(const GLvoid* data, const GLsizei& size)
        : m_size(size)
        , m_data(data)
    {
    }

    GLvoid CData::Set(const GLvoid* data, const GLsizei& size)
    {
        m_data = data;
        m_size = size;
    }

    GLvoid CData::Reset()
    {
        CData::Set(nullptr, 0);
    }
}

namespace core
{
    CBuffer::CBuffer()
        : m_buffer_object(0)
    {
        e(glGenBuffers(1, &m_buffer_object));
    }

    CBuffer::CBuffer(const GLvoid* data, const GLsizei& size)
        : CData(data, size)
        , m_buffer_object(0)
    {
        e(glGenBuffers(1, &m_buffer_object));
    }

    CBuffer::~CBuffer()
    {
        e(glDeleteBuffers(1, &m_buffer_object));
    }

    GLvoid CBuffer::init(Node* node)
    {
        CBuffer::Bind();

        e(glBufferData(GL_ARRAY_BUFFER, m_size * sizefloat, m_data, GL_STATIC_DRAW));

        CBuffer::Attribute();

        if(node != nullptr)
            node->Init();

        CBuffer::UnBind();
    }

    GLvoid CBuffer::init(const GLint& param, Node* node)
    {
        CBuffer::Bind();

        e(glBufferData(GL_ARRAY_BUFFER, m_size * sizefloat, m_data, GL_STATIC_DRAW));

        CBuffer::Attribute();

        if(node != nullptr)
            node->Init(param);

        CBuffer::UnBind();
    }

    GLvoid CBuffer::init(glm::mat4& transform, Node* node)
    {
        CBuffer::Bind();

        e(glBufferData(GL_ARRAY_BUFFER, m_size * sizefloat, m_data, GL_STATIC_DRAW));

        CBuffer::Attribute();

        if(node != nullptr)
            node->Init(transform);

        CBuffer::UnBind();
    }

    GLvoid CBuffer::draw(Node* node)
    {
        if(node != nullptr)
            node->Draw();
    }

    GLvoid CBuffer::draw(const GLuint* array, Node* node)
    {
        if(node != nullptr)
            node->Draw(array);
    }

    GLvoid CBuffer::draw(const GLuint& shader_program, Node* node)
    {
        if(node != nullptr)
            node->Draw(shader_program);
    }

    GLvoid CBuffer::draw(const GLuint& shader_program, const GLuint* array, Node* node)
    {
        if(node != nullptr)
            node->Draw(shader_program, array);
    }

    GLvoid CBuffer::update(Node* node)
    {
        if(node != nullptr)
            node->Update();

        CBuffer::Update();
    }

    GLvoid CBuffer::update(glm::mat4& transform, Node* node)
    {
        if(node != nullptr)
            node->Update(transform);

        CBuffer::Update();
    }

    GLvoid CBuffer::Bind()
    {
        e(glBindBuffer(GL_ARRAY_BUFFER, m_buffer_object));
    }

    GLvoid CBuffer::UnBind()
    {
        e(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    GLuint CBuffer::Get()
    {
        return m_buffer_object;
    }

    GLvoid CBuffer::Set(const GLvoid* data, const GLsizei& size, GLvoid (*attribute)())
    {
        m_data = data;
        m_size = size;
        Attribute = attribute;
    }

    GLvoid CBuffer::Set(const GLvoid* data, const GLsizei& size)
    {
        CData::Set(data, size);
    }

    GLvoid CBuffer::Update()
    {
        if(m_data != nullptr && m_size > 0) {

            CBuffer::Bind();

            e(glBufferData(GL_ARRAY_BUFFER, m_size * sizefloat, m_data, GL_STATIC_DRAW));

            CBuffer::UnBind();
        }
    }

    GLvoid CBuffer::Update(const GLuint& offset)
    {
        if(m_data != nullptr && m_size > 0) {

            CBuffer::Bind();

            e(glBufferSubData(GL_ARRAY_BUFFER, offset, m_size * sizefloat, m_data));

            CBuffer::UnBind();
        }
    }

    // -----------------------------------------------------------------------

    GLvoid CBuffer::DefineVertex(const GLint& nCoord, const GLsizei& stride, const GLint& beginByte)
    {
        e(glVertexPointer(nCoord, GL_FLOAT, (GLsizei)(stride * sizefloat), (GLvoid*)(beginByte * sizefloat)));
    }

    GLvoid CBuffer::DefineColor(const GLint& nColor, const GLsizei& stride, const GLint& beginByte)
    {
        e(glColorPointer(nColor, GL_FLOAT, (GLsizei)(stride * sizefloat), (GLvoid*)(beginByte * sizefloat)));
    }

    GLvoid CBuffer::DefineTexCoord(const GLint& nTexCoord, const GLsizei& stride, const GLint& beginByte)
    {
        e(glTexCoordPointer(nTexCoord, GL_FLOAT, (GLsizei)(stride * sizefloat), (GLvoid*)(beginByte * sizefloat)));
    }

    GLvoid CBuffer::EnableVertex()
    {
        e(glEnableClientState(GL_VERTEX_ARRAY));
    }

    GLvoid CBuffer::EnableColor()
    {
        e(glEnableClientState(GL_COLOR_ARRAY));
    }

    GLvoid CBuffer::EnableTexCoord()
    {
        e(glEnableClientState(GL_TEXTURE_COORD_ARRAY));
    }

    GLvoid CBuffer::DisableVertex()
    {
        e(glDisableClientState(GL_VERTEX_ARRAY));
    }

    GLvoid CBuffer::DisableColor()
    {
        e(glDisableClientState(GL_COLOR_ARRAY));
    }

    GLvoid CBuffer::DisableTexCoord()
    {
        e(glDisableClientState(GL_TEXTURE_COORD_ARRAY));
    }
}