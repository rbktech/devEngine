#include "core/core.h"

namespace core
{
    Object::Object()
    {
        mMash = std::make_shared<CMash>();
    }

    Object::~Object()
    {
        mMash.reset();
    }

    std::shared_ptr<CMash> Object::Get()
    {
        return mMash;
    }

    Object& Object::VAO()
    {
        mMash->Set<core::CVAO>(core::VAO);

        return *this;
    }

    Object& Object::VBO(const std::string& path)
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

    Object& Object::VBO(const float* data, const int& count)
    {
        mMash->Set<CVBO>(core::VBO, data, count);

        return *this;
    }

    Object& Object::CBO(const std::string& path)
    {
        GLenum result = 0;
        std::shared_ptr<CResource> R;

        R = mResources.emplace_back(new CResource());

        result = R->Load(path, 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + R->GetPathFile());

        mMash->Set<CCBO>(core::CBO, R->GetData<GLfloat>(), R->GetCount());

        return *this;
    }

    Object& Object::CBO(const float* data, const int& count)
    {
        mMash->Set<CCBO>(core::CBO, data, count);

        return *this;
    }

    Object& Object::TBO(const std::string& path)
    {
        GLenum result = 0;
        std::shared_ptr<CResource> R;

        R = mResources.emplace_back(new CResource());

        result = R->Load(path, 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + R->GetPathFile());

        mMash->Set<CTBO>(core::TBO, R->GetData<GLfloat>(), R->GetCount());

        return *this;
    }

    Object& Object::TBO(const float* data, const int& count)
    {
        mMash->Set<CTBO>(core::TBO, data, count);

        return *this;
    }

    Object& Object::EBO(const std::string& path)
    {
        GLenum result = 0;
        std::shared_ptr<CResource> R;

        R = mResources.emplace_back(new CResource());

        result = R->Load(path, 1);
        if(result != 0)
            throw std::runtime_error("error: to load resource: " + R->GetPathFile());

        mMash->Set<CEBO>(core::EBO, R->GetData<GLint>(), R->GetCount());

        return *this;
    }

    Object& Object::EBO(const float* data, const int& count)
    {
        mMash->Set<CEBO>(core::EBO, data, count);

        return *this;
    }

    Object& Object::Buffer(const std::string& path)
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

        return *this;
    }

    Object& Object::Buffer(const float* data, const int& size, void (*func)())
    {
        mMash->Set<core::CBuffer>(core::Buffer, data, size, func);

        return *this;
    }

    Object& Object::Buffer(const float* data, const int& size)
    {
        mMash->Set<core::CBuffer>(core::Buffer, data, size);

        return *this;
    }

    Object& Object::Texture(const std::string& path)
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

        return *this;
    }

    Object& Object::Texture(const char* data, const int& size)
    {
        const TBMPHeader* bmp = nullptr;

        bmp = reinterpret_cast<const TBMPHeader*>(data);
        if(bmp == nullptr)
            throw std::runtime_error("error: bring bmp");

        mMash->Set<CTexture>(core::Texture, data, size, bmp->Width, bmp->Height, bmp->DataOffset, bmp->Bits_Per_Pixel);

        return *this;
    }

    Object& Object::Texture(const Object& object)
    {
        std::shared_ptr<CTexture> pTexture = object.mMash->Get<CTexture>(core::Texture);
        if(pTexture == nullptr)
            throw std::runtime_error("error: Object& Object::Texture(const Object& object)");

        mMash->Set<core::CTexture>(core::Texture, pTexture);

        return *this;
    }

    Object& Object::Shader(const std::string& path)
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

        mMash->Set<core::CShaderProgram>(core::Shader, R->GetRaw<GLchar>(), R->GetSize(), CShader::Type(item->second));

        return *this;
    }

    Object& Object::Shader(const char* data, const int& size, const int& shaderType)
    {
        mMash->Set<core::CShaderProgram>(core::Shader, data, size, CShader::Type(shaderType));

        return *this;
    }

    Object& Object::Shader(const Object& object)
    {
        std::shared_ptr<CShaderProgram> pShader = object.mMash->Get<CShaderProgram>(core::Shader);
        if(pShader == nullptr)
            throw std::runtime_error("error: Object& Shader(const Object& object)");

        mMash->Set<core::CShaderProgram>(core::Shader, pShader);

        return *this;
    }

    Object& Object::Perspective(const float& _fovy, const float& _aspect, const float& _near, const float& _far)
    {
        mMash->Set<core::CPerspective>(core::Perspective, _fovy, _aspect, _near, _far);

        return *this;
    }

    Object& Object::Perspective(const Object& object)
    {
        std::shared_ptr<CPerspective> pPerspective = object.mMash->Get<CPerspective>(core::Perspective);
        if(pPerspective == nullptr)
            throw std::runtime_error("error: Object& Perspective(const Object& object)");

        mMash->Set<core::CPerspective>(core::Perspective, pPerspective);

        return *this;
    }

    Object& Object::Orthographic(const GLfloat& left,
        const GLfloat& right,
        const GLfloat& bottom,
        const GLfloat& top,
        const GLfloat& near,
        const GLfloat& far)
    {
        mMash->Set<core::COrthographic>(core::Orthographic, left, right, bottom, top, near, far);

        return *this;
    }

    Object& Object::Orthographic(const Object& object)
    {
        std::shared_ptr<COrthographic> pOrthographic = object.mMash->Get<COrthographic>(core::Orthographic);
        if(pOrthographic == nullptr)
            throw std::runtime_error("error: Object& Perspective(const Object& object)");

        mMash->Set<core::COrthographic>(core::Orthographic, pOrthographic);

        return *this;
    }

    Object& Object::Orthographic(const COrthographic::TMoveXY& move)
    {
        mMash->Set<core::COrthographic>(core::Orthographic, move);

        return *this;
    }

    Object& Object::Orthographic(const COrthographic::TScale& scale)
    {
        mMash->Set<core::COrthographic>(core::Orthographic, scale);

        return *this;
    }

    Object& Object::Orthographic(const COrthographic::TSize& size)
    {
        mMash->Set<core::COrthographic>(core::Orthographic, size);

        return *this;
    }

    Object& Object::Camera()
    {
        mMash->Set<core::CCamera>(core::Camera);

        return *this;
    }

    Object& Object::Camera(const CCamera::TMoveXZ& move)
    {
        mMash->Set<core::CCamera>(core::Camera, move);

        return *this;
    }

    Object& Object::Camera(const CCamera::TMoveXY& move)
    {
        mMash->Set<core::CCamera>(core::Camera, move);

        return *this;
    }

    Object& Object::Camera(const CCamera::TRotate& rotate)
    {
        mMash->Set<core::CCamera>(core::Camera, rotate);

        return *this;
    }

    Object& Object::Camera(const CCamera::TRadius& radius)
    {
        mMash->Set<core::CCamera>(core::Camera, radius);

        return *this;
    }

    Object& Object::Camera(const CCamera::TCentre& centre)
    {
        mMash->Set<core::CCamera>(core::Camera, centre);

        return *this;
    }

    Object& Object::Camera(const Object& object)
    {
        std::shared_ptr<CCamera> pCamera = object.mMash->Get<CCamera>(core::Camera);
        if(pCamera == nullptr)
            throw std::runtime_error("error: Object& Camera(const Object& object)");

        mMash->Set<core::CCamera>(core::Camera, pCamera);

        return *this;
    }

    Object& Object::Matrix()
    {
        mMash->Set<core::CMatrix>(core::Matrix);

        return *this;
    }

    Object& Object::Rotate(const GLfloat& degrees, const GLfloat& x, const GLfloat& y, const GLfloat& z)
    {
        mMash->Set<core::CRotate>(core::Rotate, degrees, x, y, z);

        return *this;
    }

    Object& Object::Translate(const GLfloat& x, const GLfloat& y, const GLfloat& z)
    {
        mMash->Set<core::CTranslate>(core::Translate, x, y, z);

        return *this;
    }

    Object& Object::Update()
    {
        mMash->Update();

        return *this;
    }

    Object& Object::Scale(const GLfloat& scale)
    {
        mMash->Set<core::CScale>(core::Scale, scale);

        return *this;
    }

    Object& Object::Scale(const GLfloat& x, const GLfloat& y, const GLfloat& z)
    {
        mMash->Set<core::CScale>(core::Scale, x, y, z);

        return *this;
    }

    Object& Object::Elements(const int& type, const int& count)
    {
        mMash->Set<core::CDrawElements>(core::Elements, type, count);

        return *this;
    }

    Object& Object::Arrays(const int& mode, const int& first, const int& count)
    {
        mMash->Set<core::CDrawArrays>(core::Array, mode, first, count);

        return *this;
    }

    Object& Object::Arrays(const int& size)
    {
        mMash->Set<core::CDrawArrays>(core::Array, size);

        return *this;
    }

    void Object::Apply()
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

    void Object::Draw()
    {
        mMash->Draw();

        // Object::BindShader();
        // Object::BindTexture();

        // BO::DrawArray();
        // BO::DrawElement();

        // Object::UnBindTexture();
    }

    // int CreateBuffer([[maybe_unused]] const std::string& val)
    // {
    //     return 0;
    // }
    // int CreateVAO([[maybe_unused]] const std::string& val)
    // {
    //     return 0;
    // }
    // int CreateVBO([[maybe_unused]] const std::string& val)
    // {
    //     return 0;
    // }
    // int CreateEBO([[maybe_unused]] const std::string& val)
    // {
    //     return 0;
    // }
    // int CreateCBO([[maybe_unused]] const std::string& val)
    // {
    //     return 0;
    // }
    // int CreateTBO([[maybe_unused]] const std::string& val)
    // {
    //     return 0;
    // }
    // int CreateTexture([[maybe_unused]] const std::string& val)
    // {
    //     return 0;
    // }
    // int CreateShader([[maybe_unused]] const std::string& val)
    // {
    //     return 0;
    // }
    // int LinkShader([[maybe_unused]] const std::string& val)
    // {
    //     return 0;
    // }
    // int SetAttribute()
    // {
    //     return 0;
    // }
    // void Load([[maybe_unused]] const std::string& path)
    // {
    //     int result = R->Load(path);
    //     if(result != 0) {
    //         Object* obj = Get(R->GetType());
    //     }
    // }

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
}