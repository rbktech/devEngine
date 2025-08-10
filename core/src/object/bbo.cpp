#include "core/object/bbo.h"

namespace core
{
    CBBO::CBBO()
        : m_type(0)
        , m_show(true)
    {
    }

    GLvoid CBBO::Reset()
    {
    }

    GLboolean CBBO::IsShow()
    {
        return m_show;
    }

    GLvoid CBBO::IsShow(const GLboolean& show)
    {
        m_show = show;
    }
}