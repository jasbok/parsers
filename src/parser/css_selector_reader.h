#ifndef CSS_SELECTOR_READER_H
#define CSS_SELECTOR_READER_H

#include "css_selector_reader_enums.h"
#include "stream_reader.h"
#include "token.h"

template<class C = char, class traits = std::char_traits<C>>
class css_selector_reader
{
public:
        typedef typename stream_reader<C,traits>::string string;


        css_selector_reader(std::basic_istream<C, traits>* stream)
                : _reader(stream)
        {}

        token<css_token, string> read_token(){
                if(_reader.peek_and_read("#")){

                }
        }
private:
        stream_reader<C, traits> _reader;
};

#endif // CSS_SELECTOR_READER_H
