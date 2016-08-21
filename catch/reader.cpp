#include "catch.hpp"
#include "../src/parser/stream_reader.h"

#include <sstream>

namespace reader_catch{

typedef wchar_t wchar;

SCENARIO("Basic Read Operation"){
        std::stringstream stream;
        stream << "abcxdefyghi";

        stream_reader<char> stream_reader(&stream);

        CHECK(stream_reader.peek("abc") == true);
        CHECK(stream_reader.read("abc") == 3);
        CHECK(stream_reader.read() == 'x');

        CHECK(stream_reader.peek("def") == true);
        CHECK(stream_reader.read("def") == 3);
        CHECK(stream_reader.read() == 'y');

        CHECK(stream_reader.peek("ghi") == true);
        CHECK(stream_reader.read("ghi") == 3);
        CHECK(stream_reader.eof() == true);

        REQUIRE(stream_reader.reset() == true);
        CHECK(stream_reader.eof() == false);
        CHECK(stream_reader.peek("abcxdefyghi") == true);
        CHECK(stream_reader.read("abcxdefyghi") == 11);
        CHECK(stream_reader.eof() == true);

        REQUIRE(stream_reader.reset() == true);
        CHECK(stream_reader.eof() == false);
        CHECK(stream_reader.peek("abcxdef_ghi") == false);
        CHECK(stream_reader.read("abcxdef_ghi") == 7);
        CHECK(stream_reader.eof() == false);
        CHECK(stream_reader.peek() == 'y');
        CHECK(stream_reader.read() == 'y');

        REQUIRE(stream_reader.reset() == true);
        CHECK(stream_reader.eof() == false);
        CHECK(stream_reader.peek("abcxdefygh_") == false);
        CHECK(stream_reader.read("abcxdefygh_") == 10);
        CHECK(stream_reader.eof() == false);
        CHECK(stream_reader.peek() == 'i');
        CHECK(stream_reader.read() == 'i');

        REQUIRE(stream_reader.reset() == true);
        CHECK(stream_reader.eof() == false);
        CHECK(stream_reader.peek_and_read("abc") == true);
        CHECK(stream_reader.read() == 'x');
        CHECK(stream_reader.peek_and_read("def") == true);
        CHECK(stream_reader.read() == 'y');
        CHECK(stream_reader.peek_and_read("ghi") == true);
        CHECK(stream_reader.eof() == true);

        REQUIRE(stream_reader.reset() == true);
        CHECK(stream_reader.eof() == false);
        CHECK(stream_reader.peek_and_read("_bc") == false);
        CHECK(stream_reader.peek_and_read("abc") == true);
        CHECK(stream_reader.read() == 'x');
        CHECK(stream_reader.peek_and_read("d_f") == false);
        CHECK(stream_reader.peek_and_read("def") == true);
        CHECK(stream_reader.read() == 'y');
        CHECK(stream_reader.peek_and_read("gh_") == false);
        CHECK(stream_reader.peek_and_read("ghi") == true);
        CHECK(stream_reader.eof() == true);

        REQUIRE(stream_reader.reset() == true);
        CHECK(stream_reader.eof() == false);
        CHECK(stream_reader.size() == 11);
        CHECK(stream_reader.peek_and_read("abcx") == true);
        CHECK(stream_reader.size() == 11);
        CHECK(stream_reader.peek_and_read("defyghi") == true);
        CHECK(stream_reader.size() == 0);
        CHECK(stream_reader.eof() == true);

        REQUIRE(stream_reader.reset() == true);
        CHECK(stream_reader.eof() == false);
        stream << "zjkl";
        CHECK(stream_reader.read("abcxdefyghi") == 11);
        CHECK(stream_reader.eof() == false);
        CHECK(stream_reader.peek("zjkl") == true);
        CHECK(stream_reader.read("zjkl") == 4);
        CHECK(stream_reader.eof() == true);

        REQUIRE(stream_reader.reset() == true);
        CHECK(stream_reader.eof() == false);
        CHECK(stream_reader.read([](char c, unsigned int i){
                return c != 'x';
        }) == 4);
        CHECK(stream_reader.read([](char c, unsigned int i){
                return c != 'y';
        }) == 4);
        CHECK(stream_reader.read([](char c, unsigned int i){
                return c != 'z';
        }) == 4);
        CHECK(stream_reader.read([&stream_reader](char c, unsigned int i){
                return c != std::char_traits<char>::eof();
        }) == 3);
        CHECK(stream_reader.eof() == true);

        REQUIRE(stream_reader.reset() == true);
        CHECK(stream_reader.eof() == false);
        CHECK(stream_reader.read(15) == "abcxdefyghizjkl");
        CHECK(stream_reader.eof() == true);

        REQUIRE(stream_reader.reset() == true);
}
}
