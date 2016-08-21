#include "fileutil.h"
#include <fstream>

using namespace std;

void file_util::read_all(const string &path, std::vector<string> &out)
{
    ifstream in(path);
    if(in.is_open()){
        string line;
        while(getline(in, line)){
            out.push_back(line);
        }
    }
}

void file_util::read_all(const string &path, string &out)
{
    ifstream in(path);
    if(in.is_open()){
        string line;
        while(getline(in, line)){
            out += line + "\n";
        }
    }
}

void file_util::read_lines(const string &path, function<bool (const string&)> func)
{
    ifstream in(path);
    if(in.is_open()){
        string line;
        while(getline(in, line) && func(line));
    }
}
