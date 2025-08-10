#pragma once

#include <filesystem>

#include "core/initialization.h"
#include "core/mash.h"
#include "core/resources.h"

#include "core/object/bitmap.h"

#include "core/object/buffer.h"
#include "core/object/camera.h"
#include "core/object/cbo.h"
#include "core/object/draw.h"
#include "core/object/ebo.h"
#include "core/object/fbo.h"
#include "core/object/matrix.h"
#include "core/object/orthographic.h"
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

#include "core/error.h"
#include "core/matrixglm.h"

namespace core
{
    static std::map<std::string, int> getShaderType();

    static std::map<std::string, void (*)()> getVertexType();

    class Object
    {
    private:
        std::shared_ptr<CMash> mMash;
        std::vector<std::shared_ptr<CResource>> mResources;

    public:
        Object();
        ~Object();

        Object& VAO();
        Object& VBO(const std::string& path);
        Object& VBO(const float* data, const int& count);
        Object& CBO(const std::string& path);
        Object& CBO(const float* data, const int& count);
        Object& TBO(const std::string& path);
        Object& TBO(const float* data, const int& count);
        Object& EBO(const std::string& path);
        Object& EBO(const float* data, const int& count);
        Object& Buffer(const std::string& path);
        Object& Buffer(const float* data, const int& size, void (*func)());
        Object& Buffer(const float* data, const int& size);
        Object& Texture(const std::string& path);
        Object& Texture(const char* data, const int& size);
        Object& Texture(const Object& object);
        Object& Shader(const std::string& path);
        Object& Shader(const char* data, const int& size, const int& shaderType);
        Object& Shader(const Object& object);
        Object& Perspective(const float& _fovy, const float& _aspect, const float& _near, const float& _far);
        Object& Perspective(const Object& object);
        Object& Orthographic(const GLfloat& left,
            const GLfloat& right,
            const GLfloat& bottom,
            const GLfloat& top,
            const GLfloat& near = -1.0f,
            const GLfloat& far = -1.0f);
        Object& Orthographic(const Object& object);
        Object& Orthographic(const COrthographic::TMoveXY& move);
        Object& Orthographic(const COrthographic::TScale& scale);
        Object& Orthographic(const COrthographic::TSize& size);
        Object& Camera();
        Object& Camera(const CCamera::TMoveXZ& move);
        Object& Camera(const CCamera::TMoveXY& move);
        Object& Camera(const CCamera::TRotate& rotate);
        Object& Camera(const CCamera::TRadius& radius);
        Object& Camera(const CCamera::TCentre& centre);
        Object& Camera(const Object& object);
        Object& Matrix();
        Object& Rotate(const GLfloat& degrees = 0.0f,
            const GLfloat& x = 0.0f,
            const GLfloat& y = 0.0f,
            const GLfloat& z = 1.0f);
        Object& Translate(const GLfloat& x = 0.0f, const GLfloat& y = 0.0f, const GLfloat& z = 0.0f);
        Object& Scale(const GLfloat& scale = 1.0f);
        Object& Scale(const GLfloat& x, const GLfloat& y, const GLfloat& z);
        Object& Elements(const int& type, const int& count);
        Object& Arrays(const int& mode, const int& first, const int& count);
        Object& Arrays(const int& size);

        Object& Update();

        void Apply();

        void Draw();

        std::shared_ptr<CMash> Get();
    };

    class CControl
    {
    private:
        std::map<std::string, int> mShaderType;
        std::map<std::string, void (*)()> mVertexType;

        std::vector<std::pair<std::string, Object*>> mList;

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

            mShaderType.insert({ ".vert", core::CShader::Vertex });
            mShaderType.insert({ ".frag", core::CShader::Fragment });
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

    static std::map<std::string, int> getShaderType()
    {
        return CControl::getInstance().GetShaderType();
    }

    static std::map<std::string, void (*)()> getVertexType()
    {
        return CControl::getInstance().GetVertexType();
    }
}