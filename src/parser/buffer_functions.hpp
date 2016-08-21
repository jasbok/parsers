#ifndef BUFFER_FUNCTIONS_HPP
#define BUFFER_FUNCTIONS_HPP

#include "template_literals.hpp"
#include <string>

template<class C> inline
C read(const C*& buffer)
{
        return *buffer != L(C,'\0') ? *(buffer++) : L(C,'\0');
}

template<class C> inline
bool read(const C*& buffer, const C* seq)
{
        while(*seq == *buffer) {
                seq++;
                buffer++;
        }
        return *seq == L(C,'\0');
}

template<class C> inline
std::basic_string<C> read(const C*& buffer, unsigned int len)
{
        const C* start = buffer;
        unsigned int i;
        for(i = 0; i < len && read(buffer) != L(C,'\0'); i++);
        return string(start, i);
}

template<class C> inline
std::basic_string<C> read_line(const C*& buffer)
{
        const C* start = buffer;
        while(*buffer != L(C,'\0')) {
                buffer++;
        }
        return string(start, buffer - start);
}

template<class C> inline
C peek(const C* buffer)
{
        return *buffer;
}

template<class C> inline
bool peek(const C* buffer, const C* seq)
{
        unsigned int i = 0;
        while(seq++ == *buffer[i++]) ;
        return --seq == L(C,'\0');
}

template<class C> inline
std::basic_string<C> peek(const C* buffer, unsigned int len)
{
        unsigned int i;
        for(i = 0; i < len && buffer[i] != L(C,'\0'); i++);
        return string(buffer, i);
}

template<class C> inline
std::basic_string<C> peek_line(const C* buffer)
{
        const C* end = buffer;
        while(*end != L(C,'\0')) {
                end++;
        }
        return std::basic_string<C>(buffer, end - buffer);
}

template<class C> inline
bool peek_and_read(const C*& buffer, const C* seq)
{
        const C* tmp= buffer;
        buffer = read(seq) ? buffer : tmp;
        return buffer != tmp;
}

template<class C> inline
bool end(const C* buffer){
        return peek(buffer) == L(C, '\0');
}
#endif // BUFFER_FUNCTIONS_HPP
