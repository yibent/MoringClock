#ifndef __FILE_STRING_H__
#define __FILE_STRING_H__

#include <string>
#include <map>

class FileString
{
public:
    static FileString *instance;

    FileString(const std::string &file);
    ~FileString();

    std::string getString(int key);

private:
    std::map<int, std::string> stringPool;
};

#endif