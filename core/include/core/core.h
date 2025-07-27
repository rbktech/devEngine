#pragma once

#include <filesystem>

#include "core/initialization.h"
#include "core/resources.h"
#include "core/mash.h"

#include "core/object/bitmap.h"

#include "core/object/buffer.h"
#include "core/object/camera.h"
#include "core/object/cbo.h"
#include "core/object/draw.h"
#include "core/object/ebo.h"
#include "core/object/fbo.h"

#include "core/object/matrix.h"
#include "core/object/perspective.h"
#include "core/object/rbo.h"
#include "core/object/rotate.h"
#include "core/object/scale.h"
#include "core/object/shader.h"
#include "core/object/tbo.h"
#include "core/object/texture.h"
#include "core/object/translate.h"
#include "core/object/vao.h"
#include "core/object/vbo.h"

namespace core
{
    static std::map<std::string, void (*)()> getVertexType();
    static std::map<std::string, int> getShaderType();

    class RBBO : public CResource
    {
    public:
        RBBO() = default;

        RBBO(const std::string& filepath)
        {
        }

        RBBO(const float* data, const int& count)
        {
        }

        ~RBBO() = default;

        void Release()
        {
        }
    };

    class RVAO : public RBBO
    {
    };
    class RVBO : public RBBO
    {
    };
    class RCBO : public RBBO
    {
    };
    class RTBO : public RBBO
    {
    };
    class RFBO : public RBBO
    {
    };
    class RRBO : public RBBO
    {
    };
    class REBO : public RBBO
    {
    };
    class RBuffer : public RBBO
    {
    };
    class RTexture : public RBBO
    {
    };
    class RShader : public RBBO
    {
    };
    class RPerspective : public RBBO
    {
    };
    class RCamera : public RBBO
    {
    };
    class RMatrix : public RBBO
    {
    };
    class RRotate : public RBBO
    {
    };
    class RTranslate : public RBBO
    {
    };
    class RScale : public RBBO
    {
    };
    class RElements : public RBBO
    {
    };
    class RArrays : public RBBO
    {
    };

    class Object
    {
    private:
        // typedef int (Object::*fcreate)(const std::string&);

        std::shared_ptr<CMash> mMash;

        std::vector<std::shared_ptr<CResource>> mResources;

        // Object* m_draw = nullptr;

        // std::vector<fcreate> m_create;

    public:
        Object()
        {
            mMash = std::make_shared<CMash>();
        }

        ~Object()
        {
            // delete mMash;
            /*for(auto& obj : mMashes)
                delete obj;*/
        }

        Object& VAO()
        {
            mMash->Set<core::CVAO>(core::VAO);
            // m_bob.push_back(new CVAO());
            // m_create.push_back(&Object::CreateVBO);
            return *this;
        }

        Object& VBO(const std::string& path)
        {
            GLenum result = 0;
            std::shared_ptr<CResource> R;

            R = mResources.emplace_back(new CResource());

            result = R->Load(path, 1);
            if(result != 0)
                throw std::runtime_error("error: to load resource: " + R->GetPathFile());

            mMash->Set<CVBO>(core::VBO, R->GetData<GLfloat>(), R->GetCount());

            return *this;
        }

        Object& VBO(const float* data, const int& count)
        {
            mMash->Set<CVBO>(core::VBO, data, count);

            return *this;
        }

        Object& CBO(const std::string& path)
        {
            GLenum result = 0;
            std::shared_ptr<CResource> R;

            R = mResources.emplace_back(new CResource());

            result = R->Load(path, 1);
            if(result != 0)
                throw std::runtime_error("error: to load resource: " + R->GetPathFile());

            mMash->Set<CCBO>(core::CBO, R->GetData<GLfloat>(), R->GetCount());

            // m_bob.push_back(new CCBO());
            // m_create.push_back(&Object::CreateCBO);
            return *this;
        }

        Object& CBO(const float* data, const int& count)
        {
            mMash->Set<CCBO>(core::CBO, data, count);

            return *this;
        }

        Object& TBO(const std::string& path)
        {
            GLenum result = 0;
            std::shared_ptr<CResource> R;

            R = mResources.emplace_back(new CResource());

            result = R->Load(path, 1);
            if(result != 0)
                throw std::runtime_error("error: to load resource: " + R->GetPathFile());

            mMash->Set<CTBO>(core::TBO, R->GetData<GLfloat>(), R->GetCount());

            // m_bob.push_back(new CTBO());
            // m_create.push_back(&Object::CreateTBO);
            return *this;
        }

        Object& TBO(const float* data, const int& count)
        {
            mMash->Set<CTBO>(core::TBO, data, count);

            return *this;
        }

        Object& EBO(const std::string& path)
        {
            GLenum result = 0;
            std::shared_ptr<CResource> R;

            R = mResources.emplace_back(new CResource());

            result = R->Load(path, 1);
            if(result != 0)
                throw std::runtime_error("error: to load resource: " + R->GetPathFile());

            mMash->Set<CEBO>(core::EBO, R->GetData<GLint>(), R->GetCount());

            // m_bob.push_back(new CEBO());
            // m_create.push_back(&Object::CreateEBO);
            return *this;
        }

        Object& EBO(const float* data, const int& count)
        {
            mMash->Set<CEBO>(core::EBO, data, count);

            return *this;
        }

        Object& Buffer(const std::string& path)
        {
            GLenum result = 0;
            std::shared_ptr<CResource> R;

            R = mResources.emplace_back(new CResource());

            result = R->Load(path, 1);
            if(result != 0)
                throw std::runtime_error("error: to load resource: " + R->GetPathFile());

            auto VertexType = core::getVertexType();
            auto item = VertexType.find(std::filesystem::path(path).extension().string());
            if(item == VertexType.end())
                throw std::runtime_error("error: type resource not found: " + R->GetPathFile());

            mMash->Set<CBuffer>(core::Buffer, R->GetData<GLfloat>(), R->GetCount(), item->second);

            // m_bob.push_back(new CBuffer());
            // m_create.push_back(&Object::CreateBuffer);
            return *this;
        }

        Object& Buffer(const float* data, const int& size, void (*func)())
        {
            mMash->Set<core::CBuffer>(core::Buffer, data, size, func);

            return *this;
        }

        Object& Texture(const std::string& path)
        {
            GLenum result = 0;
            TBMPHeader* bmp = nullptr;
            std::shared_ptr<CResource> R;

            R = mResources.emplace_back(new CResource());

            result = R->Load(path);
            if(result != 0)
                throw std::runtime_error("error: to load texture: " + R->GetPathFile());

            bmp = R->GetRaw<TBMPHeader>();
            if(bmp == nullptr)
                throw std::runtime_error("error: bring bmp");

            mMash->Set<CTexture>(core::Texture, R->GetRaw<GLfloat>(), R->GetSize(), bmp->Width, bmp->Height,
                bmp->DataOffset, bmp->Bits_Per_Pixel);

            // m_bob.push_back(new CTexture());
            // m_create.push_back(&Object::CreateTexture);
            return *this;
        }

        Object& Texture(const char* data, const int& size)
        {
            const TBMPHeader* bmp = nullptr;

            bmp = reinterpret_cast<const TBMPHeader*>(data);
            if(bmp == nullptr)
                throw std::runtime_error("error: bring bmp");

            mMash->Set<CTexture>(
                core::Texture, data, size, bmp->Width, bmp->Height, bmp->DataOffset, bmp->Bits_Per_Pixel);

            return *this;
        }

        Object& Shader(const std::string& path)
        {
            GLenum result = 0;

            std::shared_ptr<CResource> R;

            R = mResources.emplace_back(new CResource());

            result = R->Load(path);
            if(result != 0)
                throw std::runtime_error("error: to load shader: " + R->GetPathFile());

            auto shaderType = core::getShaderType();
            auto str = std::filesystem::path(path).extension().string();
            auto item = shaderType.find(str);
            if(item == shaderType.end())
                throw std::runtime_error("error: type shader not found: " + R->GetPathFile());

            mMash->Set<core::CShaderProgram>(
                core::Shader, R->GetRaw<GLchar>(), R->GetSize(), CShader::Type(item->second));

            // m_bob.push_back(new CShaderProgram());
            // m_create.push_back(&Object::CreateShader);
            return *this;
        }

        Object& Shader(const char* data, const int& size, const int& shaderType)
        {
            mMash->Set<core::CShaderProgram>(core::Shader, data, size, CShader::Type(shaderType));

            return *this;
        }

        Object& Shader(const Object& object)
        {
            std::shared_ptr<CShaderProgram> pShader = object.mMash->Get<CShaderProgram>(core::Shader);
            if(pShader == nullptr)
                throw std::runtime_error("error: Object& Shader(const Object& object)");

            mMash->Set<core::CShaderProgram>(core::Shader, pShader);
            return *this;
        }

        Object& Perspective(const float& fovy, const float& aspect, const float& near, const float& far)
        {
            mMash->Set<core::CPerspective>(core::Perspective, fovy, aspect, near, far);

            return *this;
        }

        Object& Perspective(const Object& object)
        {
            std::shared_ptr<CPerspective> pPerspective = object.mMash->Get<CPerspective>(core::Perspective);
            if(pPerspective == nullptr)
                throw std::runtime_error("error: Object& Perspective(const Object& object)");

            mMash->Set<core::CPerspective>(core::Perspective, pPerspective);
            return *this;
        }

        Object& Camera()
        {
            mMash->Set<core::CCamera>(core::Camera);

            return *this;
        }

        Object& Camera(const TMove& move)
        {
            mMash->Set<core::CCamera>(core::Camera, move);

            return *this;
        }

        Object& Camera(const TRotate& rotate)
        {
            mMash->Set<core::CCamera>(core::Camera, rotate);

            return *this;
        }

        Object& Camera(const TRadius& radius)
        {
            mMash->Set<core::CCamera>(core::Camera, radius);

            return *this;
        }

        Object& Camera(const TCentre& centre)
        {
            mMash->Set<core::CCamera>(core::Camera, centre);

            return *this;
        }

        Object& Camera(const Object& object)
        {
            std::shared_ptr<CCamera> pCamera = object.mMash->Get<CCamera>(core::Camera);
            if(pCamera == nullptr)
                throw std::runtime_error("error: Object& Camera(const Object& object)");

            mMash->Set<core::CCamera>(core::Camera, pCamera);
            return *this;
        }

        Object& Matrix()
        {
            mMash->Set<core::CMatrix>(core::Matrix);

            return *this;
        }

        Object& Rotate(const GLfloat& degrees = 0.0f, const GLfloat& x = 0.0f, const GLfloat& y = 0.0f, const GLfloat& z = 1.0f)
        {
            mMash->Set<core::CRotate>(core::Rotate, degrees, x, y, z);

            return *this;
        }

        Object& Translate(const GLfloat& x = 0.0f, const GLfloat& y = 0.0f, const GLfloat& z = 0.0f)
        {
            mMash->Set<core::CTranslate>(core::Translate, x, y, z);

            return *this;
        }

        Object& Update()
        {
            mMash->Update();

            return *this;
        }

        Object& Scale(const GLfloat& scale = 1.0f)
        {
            mMash->Set<core::CScale>(core::Scale, scale);

            return *this;
        }

        Object& Scale(const GLfloat& x, const GLfloat& y, const GLfloat& z)
        {
            mMash->Set<core::CScale>(core::Scale, x, y, z);

            return *this;
        }

        Object& Elements(const int& type, const int& count)
        {
            mMash->Set<core::CDrawElements>(core::Elements, type, count);

            return *this;
        }

        Object& Arrays(const int& mode, const int& first, const int& count)
        {
            mMash->Set<core::CDrawArrays>(core::Array, mode, first, count);

            return *this;
        }

        void Apply()
        {
            mMash->Apply();
            mResources.clear();

            // Load("path/vertex.xyz");
            // Load("path/vertex.rgba");
            // Load("path/texture.st");
            // Load("path/element.index");
            // Load("path/picture.bmp");
            // Load("path/shader.frag");
            // Load("path/shader.vert");

            // Object::CreateVAO("");
            // Object::CreateVBO("");
            // Object::CreateTBO("");
            // Object::CreateEBO("");
            // Object::CreateTexture("");
            // Object::CreateShader("");
            // Object::CreateShader("");
            // Object::LinkShader("");

            // Object::EnableVertices();
            // Object::EnableColor();
            // Object::EnableTextureCoord();

            // int SetAttribute();
        };

        void Draw()
        {
            // Object::BindShader();

            // Object::BindTexture();

            // BO::DrawArray();
            // BO::DrawElement();
            mMash->Draw();

            // Object::UnBindTexture();
        }

    private:
        int CreateBuffer(const std::string& val)
        {
            return 0;
        }
        int CreateVAO(const std::string& val)
        {
            return 0;
        }
        int CreateVBO(const std::string& val)
        {
            return 0;
        }
        int CreateEBO(const std::string& val)
        {
            return 0;
        }
        int CreateCBO(const std::string& val)
        {
            return 0;
        }
        int CreateTBO(const std::string& val)
        {
            return 0;
        }
        int CreateTexture(const std::string& val)
        {
            return 0;
        }
        int CreateShader(const std::string& val)
        {
            return 0;
        }
        int LinkShader(const std::string& val)
        {
            return 0;
        }

        int SetAttribute()
        {
            return 0;
        }

        void Load(const std::string& path)
        {
            /*int result = R->Load(path);
            if(result != 0) {
                Object* obj = Get(R->GetType());
            }*/
        }
    };

    class CControl
    {
    private:
        std::vector<std::pair<std::string, Object*>> mList;
        std::map<std::string, void (*)()> mVertexType;
        std::map<std::string, int> mShaderType;

    public:
        CControl(const CControl&) = delete;
        CControl& operator=(const CControl&) = delete;

        static CControl& getInstance()
        {
            static CControl instance;
            return instance;
        }

        void Draw()
        {
            for(auto& item : mList)
                item.second->Draw();
        }

        Object* Add(const std::string& name)
        {
            return mList.emplace_back(name, new Object()).second;
        }

        void Delete()
        {
            for(auto& item : mList)
                delete item.second;
            mList.clear();
        }

        Object* Find(const std::string& name)
        {
            for(auto& item : mList)
                if(item.first == name)
                    return item.second;
            return nullptr;
        }

        std::map<std::string, void (*)()> GetVertexType()
        {
            return mVertexType;
        }

        std::map<std::string, int> GetShaderType()
        {
            return mShaderType;
        }

    private:
        CControl()
        {
            mVertexType.insert({ ".xy", &core::xy });
            mVertexType.insert({ ".xyz", &core::xyz });
            mVertexType.insert({ ".xyrgb", &core::xyrgb });
            mVertexType.insert({ ".xyzrgb", &core::xyzrgb });
            mVertexType.insert({ ".xyrgba", &core::xyrgba });
            mVertexType.insert({ ".xyzrgba", &core::xyzrgba });
            mVertexType.insert({ ".xyrgbi", &core::xyrgbi });
            mVertexType.insert({ ".xyzrgbi", &core::xyzrgbi });
            mVertexType.insert({ ".xyrgbai", &core::xyrgbai });
            mVertexType.insert({ ".xyzrgbai", &core::xyzrgbai });
            mVertexType.insert({ ".xyst", &core::xyst });
            mVertexType.insert({ ".xyzst", &core::xyzst });
            mVertexType.insert({ ".xyrgbst", &core::xyrgbst });
            mVertexType.insert({ ".xyzrgbst", &core::xyzrgbst });
            mVertexType.insert({ ".xyrgbast", &core::xyrgbast });
            mVertexType.insert({ ".xyzrgbast", &core::xyzrgbast });
            mVertexType.insert({ ".xyrgbist", &core::xyrgbist });
            mVertexType.insert({ ".xyzrgbist", &core::xyzrgbist });
            mVertexType.insert({ ".xyrgbaist", &core::xyrgbaist });
            mVertexType.insert({ ".xyzrgbaist", &core::xyzrgbaist });

            mShaderType.insert({ ".vert", core::ShaderVertex });
            mShaderType.insert({ ".frag", core::ShaderFragment });
        }

        ~CControl()
        {
            Delete();
        }
    };

    static void release()
    {
        CControl::getInstance().Delete();
    }

    static Object& object(const std::string& name)
    {
        Object* object = nullptr;

        object = CControl::getInstance().Find(name);
        if(object == nullptr)
            object = CControl::getInstance().Add(name);

        return *(object);
    }

    static void draw()
    {
        CControl::getInstance().Draw();
    }

    static std::map<std::string, void (*)()> getVertexType()
    {
        return CControl::getInstance().GetVertexType();
    }

    static std::map<std::string, int> getShaderType()
    {
        return CControl::getInstance().GetShaderType();
    }
}