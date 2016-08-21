#ifndef BASIC_READER_H
#define BASIC_READER_H

#include <functional>
#include <string>

template<class C, class S, class traits>
class basic_reader
{
public:
        typedef std::basic_string<C, traits> string;

        virtual ~basic_reader(){};

        virtual C read() = 0;
        virtual S read(const string& seq) = 0;
        virtual string read(S n) = 0;
        virtual S read(std::function<bool(C,S)> func) = 0;
        virtual string read_line() = 0;

        virtual C peek() = 0;
        virtual bool peek(const string& seq) = 0;
        virtual string peek(S n) = 0;
        virtual string peek_line() = 0;

        virtual bool peek_and_read(const string& seq) = 0;

        virtual bool reset() = 0;
        virtual bool eof() = 0;

        virtual S size() = 0;
};

#endif // BASIC_READER_H
