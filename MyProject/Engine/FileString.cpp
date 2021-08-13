#include "FileString.h"

#include <fstream>
#include <vector>

#include "Director.h"

using namespace std;

static const string fileName{"stringFile.txt"};

FileString *FileString::instance = new FileString{fileName};

FileString::FileString(const string &file) {
    ifstream fileStream(file);
    if (!fileStream.is_open()) return;

    vector<string> readFromFile;
    //从文件读取所有字符串
    while (!fileStream.eof()) {
        string temp;
        fileStream >> temp;
        readFromFile.push_back(temp);
    }

    auto getStrKey = [](const string &str) -> int {
        //开始寻找字符串的key值
        //前" - "的位置,数字就在这之后
        auto pos = str.find_first_of('-');
        size_t posEnd = 0;
        for (auto x = pos + 1; x < str.size(); ++x) {
            //找到的后" - ",
            if (str[x] == '-') posEnd = x;
        }
        string numberStr;
        numberStr = str.substr(pos + 1, posEnd - pos);
        //获得字符串的key值
        int key = stoi(numberStr);
        return key;
    };

    auto getStrText = [](const string &str) -> string {
        auto pos = str.find_first_of('[');
        auto posEnd = str.find_last_of(']');

        return str.substr(pos + 1, posEnd - pos);
    };

    //解析字符串
    for (auto &it : readFromFile) {
        //开头是str,表明是一个字符串
        if (it.compare(0, sizeof("str"), "str")) {
            int key = getStrKey(it);
            string text = getStrText(it);

            stringPool.insert({key, text});
        }
    }
}

string FileString::getString(int key) {
    auto iter = stringPool.find(key);
    if (iter != stringPool.end()) return iter->second;
    return string{};
}
