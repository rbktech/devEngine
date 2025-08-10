#pragma once

#include <string>
#include <vector>

enum EFileType : uint16_t {
    non = 0,
    xy = 0x00F1,        // xy
    xyz = 0x016B,       // xy z
    xyrgb = 0x022C,     // xy   rgb
    xyzrgb = 0x02A6,    // xy z rgb
    xyrgba = 0x028D,    // xy   rgb a
    xyzrgba = 0x0307,   // xy z rgb a
    xyst = 0x01D8,      // xy         st
    xyzst = 0x0252,     // xy z       st
    xyrgbst = 0x0313,   // xy   rgb   st
    xyzrgbst = 0x038D,  // xy z rgb   st
    xyrgbast = 0x0374,  // xy   rgb a st
    xyzrgbast = 0x03EE, // xy z rgb a st

    xye = 0x0,        // xy            e
    xyze = 0x0,       // xy z          e
    xyrgbe = 0x0,     // xy   rgb      e
    xyzrgbe = 0x0,    // xy z rgb      e
    xyrgbae = 0x0,    // xy   rgb a    e
    xyzrgbae = 0x0,   // xy z rgb a    e
    xyste = 0x0,      // xy         st e
    xyzste = 0x0,     // xy z       st e
    xyrgbste = 0x0,   // xy   rgb   st e
    xyzrgbste = 0x0,  // xy z rgb   st e
    xyrgbaste = 0x0,  // xy   rgb a st e
    xyzrgbaste = 0x0, // xy z rgb a st e

    rgb = 0x013B,   // rgb
    rgba = 0x019C,  // rgba
    st = 0x00E7,    // st
    index = 0x0218, // index
    vert = 0x01C1,  // vert
    frag = 0x01A0,  // frag
    dxyz = 0x01CF,  // dxyz

    bmp = 0x013F // bmp
};

struct CValue {

    union
    {
        int i;
        float f;
    };

    CValue(const int& value)
    {
        i = value;
    }

    CValue(const float& value)
    {
        f = value;
    }
};

class CResource
{
private:
    char* m_root;
    unsigned int m_size;
    EFileType m_type;
    std::vector<CValue> m_data;
    std::string m_filepath;

    void Clear();

protected:
    void SetData(const std::initializer_list<CValue>& data);

    void ReadArray(std::basic_istream<char>& stream);
    void ReadStream(std::basic_istream<char>& stream);

    EFileType IsType(const std::string& filepath);

public:
    CResource();
    ~CResource();

    int Load(const std::string& filepath, const uint8_t& debug = 0);
    int Save(const std::string& filepath);

    EFileType GetType();

    /**
     * @brief Возвращает размер файла
     * @return size_t - размер файла
     */
    size_t GetSize();

    /**
     * @brief Возвращает размер массива
     * @return size_t - размер массива
     */
    size_t GetCount();

    /**
     * @brief Возвращает указатель на сырые данные файла
     * @tparam T - тип возвращаемого указателя
     * @return T* - указатель на сырые данные файла
     */
    template <class T> T* GetRaw()
    {
        return reinterpret_cast<T*>(m_root);
    }

    /**
     * @brief Возвращает указатель на данные массива
     * @tparam T - тип возвращаемого указателя
     * @return T* - указатель на данные массива
     */
    template <class T> T* GetData()
    {
        return reinterpret_cast<T*>(&m_data[0]);
    }

    std::string GetPathFile();
};