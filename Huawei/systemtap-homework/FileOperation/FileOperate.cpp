// FileOperate.cpp
#include "FileOperate.h"

#include <stdio.h>

FileOperate::FileOperate()
{}

FileOperate::FileOperate(const std::string &file) : mFile(file)
{}

FileOperate::~FileOperate()
{
    if (mFileStream.is_open()) {
        close();
    }
}

/*
 * 创建文件
 */
bool FileOperate::create(const std::string &file)
{
    std::fstream out_file;
    out_file.open(file.c_str(), std::ios::out);
    if (!out_file) {
        return false;
    }
    out_file.close();

    return true;
}

/*
 * 删除文件
 */
bool FileOperate::remove(const std::string &file)
{
    // 删除文件，成功返回0，否则返回-1
    if (-1 == std::remove(file.c_str())) {
        return false;
    }

    return true;
}

bool FileOperate::exist(const string &file)
{
    if (access(file.c_str(), F_OK) == 0)
        return true;

    return false;
}

bool FileOperate::open(ios_base::openmode __mode)
{
    mFileStream.open(mFile.c_str(), __mode);

    return mFileStream.is_open();
}

bool FileOperate::open(const string &file, ios_base::openmode __mode)
{
    mFile = file;
    return open(__mode);
}

void FileOperate::close()
{
    mFileStream.close();
    mFileStream.clear();
}

/*
 * 文件重命名
 */
bool FileOperate::rename(const std::string &newName)
{
    std::string newFile = fileDir() + newName;

    int result = std::rename(mFile.c_str(), newFile.c_str());
    if ( result == 0 )
        return true;

    return false;
}

/*
 * 判断文件是否存在
 */
bool FileOperate::isExist()
{
    return FileOperate::exist(mFile);
}

/*
 * 获取文件名
 * 文件绝对路径： /home/root/.../Test/test1.txt
 * 返回值     ： test1.txt
 */
const string FileOperate::fileName()
{
    string name = mFile;

    std::size_t pos = mFile.rfind('/');
    if (pos != std::string::npos) {
        name = mFile.substr(pos+1);
    }

    return name;
}

/*
 * 获取文件所在目录
 * 文件绝对路径： /home/root/.../Test/test1.txt
 * 返回值     ： /home/root/.../Test/
 */
const string FileOperate::fileDir()
{
    string dir = "";

    std::size_t pos = mFile.rfind('/');
    if (pos != std::string::npos) {
        dir = mFile.substr(0, pos+1);
    }

    return dir;
}

/*
 * 获取文件大小(总字节数)
 */
size_t FileOperate::fileSize()
{
#if 0
    // 方式一
    mFileStream.seekg(0, mFileStream.end);
    int length = mFileStream.tellg();
    mFileStream.seekg(0, mFileStream.beg);

    return length;
#endif

    // 方式二
    struct stat info;
    stat(mFile.c_str(), &info);

    return static_cast<std::size_t>(info.st_size);
}

bool FileOperate::atEnd()
{
    // peek函数的作用是获取下一个字符，但是指针不会移动
    return mFileStream.peek() == EOF;
}

void FileOperate::read(string &buffer, size_t bufferSize)
{
    buffer.resize(bufferSize);
    mFileStream.read(&buffer[0], bufferSize);
}

const string FileOperate::readLine()
{
    // 文件存在 读取数据
    std::string dataStr = "";
    getline(mFileStream, dataStr);
    return dataStr;
}

const string FileOperate::readAll()
{
    std::string buffer;
    size_t length = fileSize();
    FileOperate::read(buffer, length);

    return buffer;
}

void FileOperate::write(const string &data)
{
    mFileStream << data << '\n';
}

