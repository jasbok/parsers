#ifndef FILE_UTIL_H
#define FILE_UTIL_H

#include <functional>
#include <string>
#include <vector>

class file_util
{
public:
    static  void read_all(const std::string& path, std::vector<std::string>& out);
    static  void read_all(const std::string& path, std::string& out);
    static  void read_lines(const std::string& path, std::function<bool(const std::string&)> func);
};

#endif // FILE_UTIL_H
