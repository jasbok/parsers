#ifndef TIDY_CPP_H
#define TIDY_CPP_H

#include <tidy.h>
#include <tidybuffio.h>

#include <functional>
#include <string>
#include <vector>

class tidy_cpp
{
public:
    tidy_cpp(const std::string& in);
    tidy_cpp(std::string&& in);

    virtual ~tidy_cpp();

    int return_code();
    std::string input();
    std::string output();
    std::string error();

    int parse();
    int clean_and_repair();
    int save_buffer();
    int run_diagnostics();

    void set_option(TidyOptionId option, bool value);

    bool traverse(std::function<bool(TidyNode)> func);
    bool traverse(std::function<bool(TidyNode)> func, TidyNode node);
    bool filter(std::function<bool(TidyNode)> func);
    bool filter(std::function<bool(TidyNode)> func, TidyNode node);

    void discard(std::vector<TidyNode>& nodes);

    static std::string name(TidyNode node);

private:
    std::string _in;
    TidyDoc _doc;
    TidyBuffer _out;
    TidyBuffer _err;
    int _rcode;
};

#endif // TIDY_CPP_H
