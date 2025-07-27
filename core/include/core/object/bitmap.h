#pragma once

#include <iostream>

#pragma pack(push, 1)

struct TBMPHeader {
    uint16_t Signature; // [0:1]
    uint32_t FileSize; // [2:5]
    uint32_t reserved; // [6:9]
    int32_t DataOffset; // [10:13]

    uint32_t Size; // [14:17]
    int32_t Width; // [18:21]
    int32_t Height; // [22:25]
    uint16_t Planes; // [26:27]
    uint16_t Bits_Per_Pixel; // [28:29]
    uint32_t Compression; // [30:33]
    uint32_t ImageSize; // [34:37]
    uint32_t XpixelsPerM; // [38:41]
    uint32_t YpixelsPerM; // [42:45]
    uint32_t Colors_Used; // [46:49]
    uint32_t Important_Color; // [50:53]
};

#pragma pack(pop)

class CBitmap
{
public:
    static void print(TBMPHeader* bitmap, const std::string& filepath)
    {
        std::cout << "Path file: " << filepath << std::endl;
        std::cout << "[ 0:1 ] Signature: " << bitmap->Signature << std::endl;
        std::cout << "[ 2:5 ] FileSize: " << bitmap->FileSize << std::endl;
        std::cout << "[ 6:9 ] reserved: " << bitmap->reserved << std::endl;
        std::cout << "[10:13] DataOffset: " << bitmap->DataOffset << std::endl;
        std::cout << "[14:17] Size: " << bitmap->Size << std::endl;
        std::cout << "[18:21] Width: " << bitmap->Width << std::endl;
        std::cout << "[22:25] Height: " << bitmap->Height << std::endl;
        std::cout << "[26:27] Planes: " << bitmap->Planes << std::endl;
        std::cout << "[28:29] Bits_Per_Pixel: " << bitmap->Bits_Per_Pixel << std::endl;
        std::cout << "[30:33] Compression: " << bitmap->Compression << std::endl;
        std::cout << "[34:37] ImageSize: " << bitmap->ImageSize << std::endl;
        std::cout << "[38:41] XpixelsPerM: " << bitmap->XpixelsPerM << std::endl;
        std::cout << "[42:45] YpixelsPerM: " << bitmap->YpixelsPerM << std::endl;
        std::cout << "[46:49] Colors_Used: " << bitmap->Colors_Used << std::endl;
        std::cout << "[50:53] Important_Color: " << bitmap->Important_Color << std::endl;
    }
};