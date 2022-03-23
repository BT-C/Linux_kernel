// FileOperate.h
#ifndef FILEOPERATE_H
#define FILEOPERATE_H

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <unistd.h>

using namespace std;

class FileOperate
{
public:
    FileOperate();
    FileOperate(const std::string& file);
    ~FileOperate();

    // 创建文件
    static bool create(const std::string &file);

    // 删除文件
    static bool remove(const std::string &file);

    // 文件是否存在
    static bool exist(const std::string &file);

    // 打开文件
    bool open(ios_base::openmode __mode = std::fstream::in | std::fstream::out);
    bool open(const std::string &file, ios_base::openmode __mode = std::fstream::in | std::fstream::out);

    // 关闭文件
    void close();

    // 重命名文件
    bool rename(const std::string &newName);

    // 文件是否存在
    bool isExist();

    // 获取文件名
    const std::string fileName();

    // 获取文件所在目录
    const std::string fileDir();

    // 获取文件大小(总字节数)
    std::size_t fileSize();

    // 判断当前字符是否在最后
    bool atEnd();

    // 读取文件内容
    void read(std::string &buffer, size_t bufferSize);
    const std::string readLine();
    const std::string readAll();

    // 写数据到文件
    void write(const std::string &data);

private:
    std::string mFile;
    std::fstream mFileStream;
};

#endif // FILEOPERATE_H

