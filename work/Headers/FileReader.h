#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class FileReader
{
public:
    FileReader() = default;
    virtual ~FileReader() = default;

    static std::string  LoadShader(const std::string & path)
    {
        std::string result;
        std::ifstream file(path,std::ios::in | std::ios::binary);
        if (file)
        {
            file.seekg(0,std::ios::end);   ///< 移动文件指针到文件末尾
            result.resize(file.tellg());    ///< 获取文件的大小
            file.seekg(0,std::ios::beg);   ///< 定位到文件开始

            const auto count = static_cast<std::streamsize>(result.size());
            file.read(result.data(),count);
            file.close();
        }
        else
        {
            throw std::runtime_error("Open file error");
        }

        return std::move(result);
    }

};

#endif 