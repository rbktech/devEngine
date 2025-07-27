#include "core/resources.h"

#include <fstream>

CResource::CResource()
    : m_root(nullptr)
    , m_size(0)
    , m_type(non)
{
}

CResource::~CResource()
{
    Clear();
}

void CResource::Clear()
{
    if(m_root != nullptr) {
        delete[] m_root;
        m_root = nullptr;
    }

    m_type = non;

    m_data.clear();
}

EFileType CResource::IsType(const std::string& filepath)
{
    uint16_t type = 0;
    size_t position = 0;
    std::string filetype;

    position = filepath.find_last_of('.');
    if(position != std::string::npos) {
        filetype = filepath.substr(position + 1);
        for(const auto& p : filetype)
            type += p;

        switch(type) {
            case EFileType::xy:
            case EFileType::xyz:
            case EFileType::xyrgb:
            case EFileType::xyzrgb:
            case EFileType::xyrgba:
            case EFileType::xyzrgba:
            case EFileType::xyst:
            case EFileType::xyzst:
            case EFileType::xyrgbst:
            case EFileType::xyzrgbst:
            case EFileType::xyrgbast:
            case EFileType::xyzrgbast:
            /*case EFileType::xye:
            case EFileType::xyze:
            case EFileType::xyrgbe:
            case EFileType::xyzrgbe:
            case EFileType::xyrgbae:
            case EFileType::xyzrgbae:
            case EFileType::xyste:
            case EFileType::xyzste:
            case EFileType::xyrgbste:
            case EFileType::xyzrgbste:
            case EFileType::xyrgbaste:
            case EFileType::xyzrgbaste:*/
            case EFileType::rgb:
            case EFileType::rgba:
            case EFileType::st:
            case EFileType::index:
            case EFileType::vert:
            case EFileType::frag:
            case EFileType::bmp:
            case EFileType::dxyz:
                m_type = EFileType(type);
                break;
            default:
                m_type = EFileType::non;
        }
    }

    return m_type;
}

void CResource::SetData(const std::initializer_list<CValue>& data)
{
    m_data.insert(m_data.begin(), data.begin(), data.end());
}

void CResource::ReadStream(std::basic_istream<char>& stream)
{
    std::string line;
    std::string value;

    m_size = stream.tellg();
    stream.seekg(0, std::ios::beg); // std::ios::beg - От начала файла

    while(stream.eof() == false) {

        std::getline(stream, line);
        for(const auto ch : line) {

            if(ch >= '0' && ch <= '9' || ch == '.' || ch == '-') {
                value.push_back(ch);
            } else {
                if(value.empty() == false) {
                    if(m_type == EFileType::index)
                        m_data.emplace_back(std::stoi(value));
                    else
                        m_data.emplace_back(std::stof(value));
                }
                value.clear();
            }
        }
        if(value.empty() == false) {
            if(m_type == EFileType::index)
                m_data.emplace_back(std::stoi(value));
            else
                m_data.emplace_back(std::stof(value));
        }
        value.clear();
    }
}

void CResource::ReadArray(std::basic_istream<char>& stream)
{
    float* number = nullptr;

    m_size = stream.tellg();
    stream.seekg(0, std::ios::beg); // std::ios::beg - От начала файла

    m_root = new char[m_size];

    stream.read(m_root, m_size);

    for(int i = 0; i < m_size; i += sizeof(float)) {
        number = reinterpret_cast<float*>(&m_root[i]);
        if(number != nullptr)
            m_data.emplace_back(*number);
    }
}

int CResource::Load(const std::string& filepath, const uint8_t& debug)
{
    int error = 1;

    // std::ios::in - Режим чтения, если файл не существует, попытка открытия завершится ошибкой.
    // std::ios::binary - Открывает файл в бинарном режиме.
    // std::ios::ate - Устанавливает каретку в конец файла сразу после открытия.

    Clear();

    m_filepath = filepath;

    std::ifstream file(filepath, std::ios::in | std::ios::binary | std::ios::ate);
    if(file.is_open()) {

        try {

            if(IsType(filepath) != non) {

                if(debug == 1)
                    ReadStream(file);
                else
                    ReadArray(file);

                error = 0;
            }

        } catch(const std::exception& e) {
            e.what();
        }

        file.close();
    }

    return error;
}

int CResource::Save(const std::string& filepath)
{
    int error = 1;

    char* ch = nullptr;

    std::ofstream file(filepath, std::ios::out | std::ios::binary);
    if(file.is_open()) {

        for(auto& p : m_data) {
            ch = reinterpret_cast<char*>(&p);
            for(int i = 0; i < sizeof(float); i++)
                file << ch[i];
        }

        error = 0;

        file.close();
    }

    return error;
}

EFileType CResource::GetType()
{
    return m_type;
}

size_t CResource::GetSize()
{
    return m_size;
}

size_t CResource::GetCount()
{
    return m_data.size();
}

std::string CResource::GetPathFile()
{
    return m_filepath;
}