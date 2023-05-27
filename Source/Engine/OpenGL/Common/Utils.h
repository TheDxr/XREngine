#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>


class Utils
{
public:
    static void print(glm::vec3 vec)
    {
        printf("=====================\n");
        printf("(%.2f %6.2f %6.2f)\n", vec.x, vec.y, vec.z);
    }

    static void print(glm::vec4 vec)
    {
        printf("=====================\n");
        printf("(%.2f %6.2f %6.2f %6.2f)\n", vec.x, vec.y, vec.z, vec.w);
    }

    static void print(glm::mat4 mat)
    {
        mat = glm::transpose(mat);

        printf("┌%4.2f %6.2f %6.2f %6.2f┐\n", mat[0][0], mat[0][1], mat[0][2], mat[0][3]);
        printf("│%4.2f %6.2f %6.2f %6.2f│\n", mat[1][0], mat[1][1], mat[1][2], mat[1][3]);
        printf("│%4.2f %6.2f %6.2f %6.2f│\n", mat[2][0], mat[2][1], mat[2][2], mat[2][3]);
        printf("└%4.2f %6.2f %6.2f %6.2f┘\n", mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
    }

    static std::string vec3ToString(glm::vec3 vec)
    {
        std::stringstream ss;
        ss << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";
        return ss.str();
    }
    // inline std::string GbkToUtf8(const char *src_str)
// {
//     int len       = MultiByteToWideChar(CP_ACP, 0, src_str, -1, NULL, 0);
//     wchar_t *wstr = new wchar_t[len + 1];
//     memset(wstr, 0, len + 1);
//     MultiByteToWideChar(CP_ACP, 0, src_str, -1, wstr, len);
//     len       = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
//     char *str = new char[len + 1];
//     memset(str, 0, len + 1);
//     WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
//     std::string strTemp = str;
//     if(wstr)
//         delete[] wstr;
//     if(str)
//         delete[] str;
//     return strTemp;
// }
//
// inline std::string Utf8ToGbk(const char *src_str)
// {
//     int len         = MultiByteToWideChar(CP_UTF8, 0, src_str, -1, NULL, 0);
//     wchar_t *wszGBK = new wchar_t[len + 1];
//     memset(wszGBK, 0, len * 2 + 2);
//     MultiByteToWideChar(CP_UTF8, 0, src_str, -1, wszGBK, len);
//     len         = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
//     char *szGBK = new char[len + 1];
//     memset(szGBK, 0, len + 1);
//     WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
//     std::string strTemp(szGBK);
//     if(wszGBK)
//         delete[] wszGBK;
//     if(szGBK)
//         delete[] szGBK;
//     return strTemp;
// }
//    inline std::wstring wParamToWString(WPARAM &wParam)
//    {
//        wchar_t wt[2];
//        wt[0] = (wchar_t)wParam;
//        wt[1] = L'\0';
//        return std::wstring(wt);
//    }
//
//    inline std::string wParamToString(WPARAM &wParam)
//    {
//        char wt[2];
//        wt[0] = (wchar_t)wParam;
//        wt[1] = '\0';
//        return std::string(wt);
//    }
//
//    inline std::wstring AnsiToWString(const std::string &str)
//    {
//        wchar_t buffer[512];
//        MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, buffer, 512);
//        return std::wstring(buffer);
//    }
//
//
//    inline std::wstring A2W(const std::string &str, unsigned int uCodePage)
//    {
//        int nLength = ::MultiByteToWideChar(uCodePage, 0, str.c_str(), -1, NULL, 0);
//        if(0 == nLength) {
//            throw "A2W Error";
//        }
//        std::wstring strW(nLength, L'\0');
//        int nResult = ::MultiByteToWideChar(uCodePage, 0, str.c_str(), -1, &strW[0], nLength);
//        if(nResult != nLength) {
//            throw "A2W Error";
//        }
//        strW.resize(nLength - 1);
//        return strW;
//    }
//
//
//    inline std::string W2A(const std::wstring &str, UINT uCodePage)
//    {
//        int nLength = ::WideCharToMultiByte(uCodePage, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
//        if(0 == nLength) {
//            throw "W2A Error";
//        }
//        std::string strA(nLength, '\0');
//        int nResult = ::WideCharToMultiByte(uCodePage, 0, str.c_str(), -1, &strA[0], nLength, NULL, NULL);
//        if(nResult != nLength) {
//            throw "W2A Error";
//        }
//        strA.resize(nLength - 1);
//        return strA;
//    }
//
//
//    inline std::string A2A(const std::string &str, UINT uCodePageFrom, UINT uCodePageTo)
//    {
//        return W2A(A2W(str, uCodePageFrom), uCodePageTo);
//    }
//
//    inline bool IsUTF8(const void *pBuffer, size_t size)
//    {
//        // �ο� http://blog.csdn.net/bladeandmaster88/article/details/54767487
//        bool bIsUTF8         = true;
//        unsigned char *start = (unsigned char *)pBuffer;
//        unsigned char *end   = (unsigned char *)pBuffer + size;
//
//        while(start < end) {
//            if(*start < 0x80) // (10000000): ֵС��0x80��ΪASCII�ַ�
//            {
//                start++;
//            }
//            else if(*start < (0xC0)) // (11000000): ֵ����0x80��0xC0֮���Ϊ��ЧUTF-8�ַ�
//            {
//                bIsUTF8 = false;
//                break;
//            }
//            else if(*start < (0xE0)) // (11100000): �˷�Χ��Ϊ2�ֽ�UTF-8�ַ�
//            {
//                if(start >= end - 1)
//                    break;
//
//                if((start[1] & (0xC0)) != 0x80) {
//                    bIsUTF8 = false;
//                    break;
//                }
//                start += 2;
//            }
//            else if(*start < (0xF0)) // (11110000): �˷�Χ��Ϊ3�ֽ�UTF-8�ַ�
//            {
//                if(start >= end - 2)
//                    break;
//
//                if((start[1] & (0xC0)) != 0x80 || (start[2] & (0xC0)) != 0x80) {
//                    bIsUTF8 = false;
//                    break;
//                }
//                start += 3;
//            }
//            else {
//                bIsUTF8 = false;
//                break;
//            }
//        }
//        return bIsUTF8;
//    }
//
//    inline bool IsUTF8(const std::string &str) { return IsUTF8(str.c_str(), str.size()); }
//} // namespace Utils
// #ifndef USE_ENCODER
// #define USE_ENCODER
// #define ANSI_TO_WCHAR(str) (Utils::A2W(str, CP_ACP))
// #define ANSI_TO_UTF8(str) (Utils::A2A(str, CP_ACP, CP_UTF8))
// #define UTF8_TO_ANSI(str) (Utils::A2A(str, CP_UTF8, CP_ACP))
// #define UTF8_TO_WCHAR(str) (Utils::A2W(str, CP_UTF8))
// #define WCHAR_TO_ANSI(str) (Utils::W2A(str, CP_ACP))
// #define WCHAR_TO_UTF8(str) (Utils::W2A(str, CP_UTF8))
// #endif
};