#include "catch.hpp"
#include "../src/parser/regex.h"
#include <vector>


#include <locale>
#include <codecvt>
namespace catch_regex
{

static std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> WCHAR_CONVERTER;

void REGEX_TEST(const char* regex_str, std::vector<const char*> positive, std::vector<const char*> negative, bool exact_match){
        regex<char> regex(regex_str);
        for(const char* str : positive) {
                INFO((exact_match ? "Exact " : "Partial ") <<  "Match (char): Regex=" << regex_str << ", String=" << str);
                CHECK(regex.match(str,exact_match) == true);
                regex.reset();
        }
        for(const char* str : negative) {
                INFO("Mismatch (char): Regex=" << regex_str << ", String=" << str);
                CHECK(regex.match(str,exact_match) == false);
                regex.reset();
        }
}

void REGEX_TEST(const wchar_t* regex_wstr, std::vector<const wchar_t*> positive, std::vector<const wchar_t*> negative, bool exact_match){
        regex<wchar_t> regex(regex_wstr);
        std::string regex_str = WCHAR_CONVERTER.to_bytes(regex_wstr);
        for(const wchar_t* str : positive) {
                INFO((exact_match ? "" : "Partial ") <<  "Match (wchar_t): Regex=" << regex_str << ", String=" << WCHAR_CONVERTER.to_bytes(str));
                CHECK(regex.match(str,exact_match) == true);
                regex.reset();
        }
        for(const wchar_t* str : negative) {
                INFO("Mismatch (wchar_t): Regex=" << regex_str << ", String=" << WCHAR_CONVERTER.to_bytes(str));
                CHECK(regex.match(str,exact_match) == false);
                regex.reset();
        }
}

SCENARIO("Basic String Matches (Exact)")
{
        std::vector<const char*> strings = {
                "string", "strong", "strange", "stringer", "stronger", "stranger", "strike", "striker", "loner", "longer"
        };

        for(const char* regex_str : strings) {
                regex<char> regex(regex_str);
                for(const char* str : strings) {
                        if(str == regex_str) {
                                INFO("Match: Regex=" << regex_str << ", String=" << str);
                                CHECK(regex.match(str, true) == true);
                        } else {
                                INFO("Mismatch: " << regex_str << " != " << str);
                                CHECK(regex.match(str, true) != true);
                        }
                        regex.reset();
                }
        }
}

SCENARIO("Basic String Matches (Partial)")
{
        REGEX_TEST("string", {
                           "string", "stringer", "strings", "stringers"
                   }, {
                           "", "s", "st", "str", "stri", "strin", "stro", "strong", "loner", "loners"
                   }, false);

        REGEX_TEST(L"string", {
                           L"string", L"stringer", L"strings", L"stringers"
                   }, {
                           L"", L"s", L"st", L"str", L"stri", L"strin", L"stro", L"strong", L"loner", L"loners"
                   }, false);
}

SCENARIO("Quantifiers: Optional A (Exact)")
{
        REGEX_TEST("stri?ng", {
                           "string", "strng"
                   }, {
                           "", "striing", "strong", "strung", "str", "stri", "strin", "strn", "stng", "loner", "loners"
                   }, true);

        REGEX_TEST(L"stri?ng", {
                           L"string", L"strng"
                   }, {
                           L"", L"striing", L"strong", L"strung", L"str", L"stri", L"strin", L"strn", L"stng", L"loner", L"loners"
                   }, true);
}

SCENARIO("Quantifiers: Optional B (Exact)")
{
        REGEX_TEST("stri?", {
                           "stri", "str"
                   }, {
                            "", "strong", "strung", "striing", "string", "strin", "strn", "stng", "loner", "loners"
                   }, true);

        REGEX_TEST(L"stri?", {
                           L"stri", L"str"
                   }, {
                           L"", L"strong", L"strung", L"striing", L"string", L"strin", L"strn", L"stng", L"loner", L"loners"
                   }, true);
}

SCENARIO("Quantifiers: Optional A (Partial)")
{
        REGEX_TEST("stri?ng", {
                           "string", "strng"
                   }, {
                          "", "striing", "strong", "strung", "str", "stri", "strin", "strn", "stng", "loner", "loners"
                   }, false);

        REGEX_TEST(L"stri?ng", {
                           L"string", L"strng"
                   }, {
                           L"", L"striing", L"strong", L"strung", L"str", L"stri", L"strin", L"strn", L"stng", L"loner", L"loners"
                   }, false);
}

SCENARIO("Quantifiers: Optional B (Partial)")
{
        REGEX_TEST("stri?", {
                           "stri", "str", "string", "strin", "strn", "striing", "strong", "strung",
                   }, {
                          "", "stng", "loner", "loners"
                   }, false);

        REGEX_TEST(L"stri?", {
                           L"stri", L"str", L"string", L"strin", L"strn", L"striing", L"strong", L"strung",
                   }, {
                           L"", L"stng", L"loner", L"loners"
                   }, false);
}

SCENARIO("Quantifiers: One-or-more A (Exact)")
{
        REGEX_TEST("stri+ng", {
                           "string", "striing", "striiing", "striiiing",
                   }, {
                          "", "strong", "strung", "str", "stri", "strin", "strn", "stng", "loner", "loners","strng"
                   }, true);

        REGEX_TEST(L"stri+ng", {
                           L"string", L"striing", L"striiing", L"striiiing",
                   }, {
                           L"", L"strong", L"strung", L"str", L"stri", L"strin", L"strn", L"stng", L"loner", L"loners", L"strng"
                   }, true);
}

SCENARIO("Quantifiers: One-or-more B (Exact)")
{
        REGEX_TEST("stri+", {
                           "stri", "strii", "striii", "striiii"
                   }, {
                          "", "strong", "strung", "str", "strin", "strn", "stng", "loner", "loners","strng","string", "striing", "striiing", "striiiing",
                   }, true);

        REGEX_TEST(L"stri+", {
                           L"stri", L"strii", L"striii", L"striiii"
                   }, {
                          L"", L"strong", L"strung", L"str", L"strin", L"strn", L"stng", L"loner", L"loners", L"strng", L"string", L"striing", L"striiing", L"striiiing",
                   }, true);
}

SCENARIO("Quantifiers: One-or-more A (Partial)")
{
        REGEX_TEST("stri+ng", {
                           "string", "striing", "striiing", "striiiing", "stringer", "striinger", "striiinger"
                   }, {
                          "", "strong", "strung", "str", "stri", "strin", "strn", "stng", "loner", "loners","strng", "strnger"
                   }, false);

        REGEX_TEST(L"stri+ng", {
                           L"string", L"striing", L"striiing", L"striiiing", L"stringer", L"striinger", L"striiinger"
                   }, {
                           L"", L"strong", L"strung", L"str", L"stri", L"strin", L"strn", L"stng", L"loner", L"loners", L"strng", L"strnger"
                   }, false);
}

SCENARIO("Quantifiers - Zero or more A (Exact)")
{
        REGEX_TEST("stri*ng", {
                           "strng", "string", "striing", "striiing", "striiiing"
                   }, {
                         "", "strong", "strung", "str", "stri", "strin", "strn", "stng", "loner", "loners"
                   }, true);

        REGEX_TEST(L"stri*ng", {
                          L"strng", L"string", L"striing", L"striiing", L"striiiing"
                   }, {
                           L"", L"strong", L"strung", L"str", L"stri", L"strin", L"strn", L"stng", L"loner", L"loners"
                   }, true);
}

}
