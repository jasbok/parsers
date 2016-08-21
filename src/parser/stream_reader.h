#ifndef STREAM_READER_H
#define STREAM_ READER_H

#include "basic_reader.h"
#include <istream>
#include <regex>

template<class C = char, class traits = std::char_traits<C>>
class stream_reader : public basic_reader<C, std::streamsize, traits>
{
public:
        typedef typename basic_reader<C, std::streamsize, traits>::string string;

        stream_reader(std::basic_istream<C, traits>* stream)
                : _strm(stream)
        {}

        stream_reader(stream_reader&& move)
                : _strm(move._strm)
        {
                move._strm = nullptr;
        }

        virtual ~stream_reader() {}

        C read()
        {
                return _strm->get();
        }

        std::streamsize read(const string& seq)
        {
                std::streamsize i = 0;
                while(seq[i] == peek()) {
                        read();
                        i++;
                }
                return i;
        }

        string read(std::streamsize n)
        {
                std::streamsize i = 0;
                string str(n, 0);
                while(!eof() && i < n) {
                        str[i++] = _strm->get();
                }
                return str;
        }

        std::streamsize read(std::function<bool(C, std::streamsize)> func)
        {
                std::streamsize i = 0;
                while(func(read(), i++) && _strm->good());
                return i - !_strm->good();
        }

        string read_line()
        {
                string ret;
                ret.reserve(32);
                while(!eof() && _strm->peek() != '\n') {
                        ret.push_back(_strm->get());
                }
                if(!eof()) _strm->get();
                return ret;
        }

        C peek()
        {
                return _strm->peek();
        }

        bool peek(const string& seq)
        {
                auto pos = _strm->tellg();
                auto len = read(seq);
                _strm->seekg(pos);
                return len == seq.length();
        }

        string peek(std::streamsize n)
        {
                auto pos = _strm->tellg();
                string str = read(n);
                _strm->seekg(pos);
                return str;
        }

        string peek_line(){
                auto pos = _strm->tellg();
                string str = read_line();
                _strm->seekg(pos);
                return str;
        }

        bool peek_and_read(const string& seq)
        {
                auto pos = _strm->tellg();
                auto len = read(seq);
                bool success = len == seq.length();

                if(!success)
                        _strm->seekg(pos);

                return success;
        }

        bool reset()
        {
                _strm->clear();
                _strm->seekg(0, _strm->beg);
                return _strm->good();
        }

        bool good()
        {
                return _strm->good();
        }

        bool eof()
        {
                return _strm->peek() == traits::eof();
        }

        std::streamsize size()
        {
                std::streamsize size = 0;
                if(!eof()) {
                        auto pos = _strm->tellg();
                        _strm->seekg(0, _strm->end);
                        size = _strm->tellg();
                        _strm->seekg(pos);
                }
                return size;
        }

private:
        std::basic_istream<C>* _strm;
};

#endif // STREAM_READER_H
