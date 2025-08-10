#pragma once

#include <memory>

#include "core/object/bbo.h"

namespace core
{
    class CMash
    {
    private:
        core::CBBO::Node* m_root = nullptr;

        std::map<GLint, std::shared_ptr<core::CBBO>> m_mashes;

        GLvoid Reset();

    public:
        CMash();
        ~CMash();

        GLvoid Apply();

        GLvoid Draw();
        GLvoid Draw(const GLuint* array);
        GLvoid Draw(const GLuint& shader_program);
        GLvoid Draw(const GLuint& shader_program, const GLuint* array);

        GLvoid Update();

        GLvoid Set(const CMash* mash);

        template <typename T> T* Set(const int& index, std::shared_ptr<T> item)
        {
            try {
                m_mashes.at(index) = item;
            } catch(const std::exception& e) {
                m_mashes.insert({ index, item });
            }

            return item.get();
        }

        template <typename T, typename... Args> T* Set(const int& index, const Args&... args)
        {
            T* item = nullptr;

            try {
                item = dynamic_cast<T*>(m_mashes.at(index).get());
            } catch(const std::exception& e) {
                item = dynamic_cast<T*>((*m_mashes.insert({ index, std::make_shared<T>() }).first).second.get());
            }

            item->Set(args...);

            return item;
        }

        template <typename T> std::shared_ptr<T> Get(const int& index)
        {
            try {
                return std::dynamic_pointer_cast<T>(m_mashes.at(index));
            } catch(...) {
                return nullptr;
            }
        }

        /*
        template <typename T> T* Get(const int& index)
        {
            try {
                return dynamic_cast<T*>(m_mashes.at(index).get());
            } catch(...) {
                return nullptr;
            }
        }
         */

        /*
        template <typename T, typename... Args> GLvoid Update(const int& index, const Args&... args)
        {
            Set<T>(index, args...)->Update(args...);
        }
         */
    };
}