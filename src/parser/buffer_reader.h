#ifndef BUFFER_READER_H
#define BUFFER_READER_H

#include "buffer_functions.hpp"
#include <regex>
#include <string>

template<class C = char, class traits =  std::char_traits<C>>
class buffer_reader
{
public:
        typedef typename std::basic_string<C> string;

        buffer_reader(const C* c_string)
                : _buf(c_string)
        {}

        buffer_reader(buffer_reader&& move)
                : _buf(move._buf)
        {
                move._buf = nullptr;
        }

        virtual ~buffer_reader() {};

        C read()
        {
                return ::read(_buf);
        }

        bool read(const C* seq)
        {
                return ::read(_buf, seq);
        }

        string read(unsigned int len)
        {
                return ::read(_buf, len);
        }

        string read_line()
        {
                return ::read_line(_buf);
        }

//        string read(const std::basic_regex<C, traits>& regex)
//        {
//                std::match_results<const C*> match;
//                std::regex_search(_buf, match, regex, std::regex_constants::match_continuous);
//                string ret(_buf,  match.length(0));
//                _buf += match.length(0);
//                return ret;
//        }

        C peek()
        {
                return ::peek(_buf);
        }

        bool peek(const C* seq)
        {
                return ::peek(_buf, seq);
        }

        string peek(unsigned int len)
        {
                return ::peek(_buf, len);
        }

        string peek_line()
        {
                return ::peek_line(_buf);
        }

//        string peek(const std::basic_regex<C, traits>& regex)
//        {
//                std::match_results<const C*> match;
//                return string(_buf, std::regex_search(_buf, match, regex, std::regex_constants::match_continuous) ? 0 : match.length(0));
//        }

        bool peek_and_read(const C* seq)
        {
                return ::peek_and_read(_buf, seq);
        }

private:
        const C* _buf;
};


#endif // BUFFER_READER_H
