#include "core/mash.h"

namespace core
{
    CMash::CMash()
        : m_root(nullptr)
    {
    }

    CMash::~CMash()
    {
        m_mashes.clear();
        if(m_root != nullptr) {
            m_root->Delete();
            delete m_root;
        }
    }

    GLvoid CMash::Reset()
    {
        for(const auto& item : m_mashes)
            item.second->Reset();
    }

    GLvoid CMash::Apply()
    {
        for(const auto& item : m_mashes) {
            [[maybe_unused]] const int& type = item.first;
            CBBO* object = item.second.get();
            if(object != nullptr) {

                auto node = new core::CBBO::Node(object);
                node->SetNode(m_root);
                m_root = node;
            }
        }

        if(m_root != nullptr)
            m_root->Init(0);

        Reset();
    }

    GLvoid CMash::Draw()
    {
        if(m_root != nullptr)
            m_root->Draw();
    }

    GLvoid CMash::Draw(const GLuint* array)
    {
        if(m_root != nullptr)
            m_root->Draw(array);
    }

    GLvoid CMash::Draw(const GLuint& shader_program)
    {
        if(m_root != nullptr)
            m_root->Draw(shader_program);
    }

    GLvoid CMash::Draw(const GLuint& shader_program, const GLuint* array)
    {
        if(m_root != nullptr)
            m_root->Draw(shader_program, array);
    }

    GLvoid CMash::Update()
    {
        if(m_root != nullptr)
            m_root->Update();

        Reset();
    }

    GLvoid CMash::Set(const CMash* mash)
    {
        for(auto& item : mash->m_mashes) {

            auto index = item.first;
            auto object = item.second;

            try {
                m_mashes.at(index) = object;
            } catch(const std::exception& e) {
                m_mashes.insert({ index, object });
            }
        }
    }
}