#include "rule_parser.h"
#include <iostream>

using namespace std;

enum class rule_parser::Token {
        DOMAIN,
        EXCEPTION,
        LIST,
        OPTIONS,
        SELECTOR,
        SELECTOR_EXCEPTION,
        EXPRESSION,
        END_OF_RULE,
        UNKNOWN
};

rule_parser::rule_parser()
        : _curr(nullptr)
{}

rule rule_parser::parse(const string &str)
{
        rule r;
        Token token;
        unsigned int index = 0;
        _curr = str.c_str();
        while(token != Token::END_OF_RULE) {
                token = _read_token();
                switch(token) {
                case Token::EXCEPTION:
                        r.is_exception = true;
                        break;

                case Token::EXPRESSION:
                        _read_expression(r);
                        break;

                case Token::SELECTOR:
                        _read_selector(r);
                        break;

                case Token::SELECTOR_EXCEPTION:
                        r.is_exception = true;
                        _read_selector(r);
                        break;

                case Token::OPTIONS:
                        _read_options(r);
                        break;
                }
        }

        return r;
}

rule_parser::Token rule_parser::_read_token()
{
        Token token;

        if(_peak_and_read("@@")) {
                token = Token::EXCEPTION;
        } else if(_peak_and_read("##")) {
                token = Token::SELECTOR;
        } else if(_peak_and_read("#!#")) {
                token = Token::SELECTOR_EXCEPTION;
        } else if(_peak_and_read("||")) {
                token = Token::DOMAIN;
        } else if(_peak_and_read("$")) {
                token = Token::OPTIONS;
        } else if(_is_end()) {
                token =Token::END_OF_RULE;
        } else {
                token = Token::EXPRESSION;
        }
        return token;
}

void rule_parser::_read_expression(rule& r)
{
        unsigned int length = 0;
        const char* start = _curr;
        while(!_is_end() && !_peak("$") && !_peak("##") && !_peak("#!#")) {
                _read();
                length++;
        }
        r.expression = string(start, length);
}

void rule_parser::_read_selector(rule& r)
{
        unsigned int length = 0;
        const char* start = _curr;
        while(!_is_end() && !_peak("$")) {
                _read();
                length++;
        }
        r.css_selector = string(start, length);
}

void rule_parser::_read_options(rule &r)
{
        while(*_curr != '\0') {
                excludable<Option> option;
                option.is_exclusion = _peak_and_read("~");
                _read_option("document", Option::DOCUMENT,option) ||
                _read_option("domain", Option::DOMAIN,option) ||
                _read_option("donottrack", Option::DO_NOT_TRACK,option) ||
                _read_option("elementhide", Option::ELEMENT_HIDE,option) ||
                _read_option("genericblock", Option::GENERIC_BLOCK,option) ||
                _read_option("generichide", Option::GENERIC_HIDE,option) ||
                _read_option("image", Option::IMAGE,option) ||
                _read_option("match-case", Option::MATCH_CASE,option) ||
                _read_option("object-subrequest", Option::OBJECT_SUBREQUEST,option) ||
                _read_option("object", Option::OBJECT,option) ||
                _read_option("other", Option::OTHER,option) ||
                _read_option("ping", Option::PING,option) ||
                _read_option("script", Option::SCRIPT,option) ||
                _read_option("sitekey", Option::SITEKEY,option) ||
                _read_option("stylesheet", Option::STYLESHEET,option) ||
                _read_option("subdocument", Option::SUBDOCUMENT,option) ||
                _read_option("third-party", Option::THIRD_PARTY,option) ||
                _read_option("xmlhttprequest", Option::XML_HTTP_REQUEST,option);

                switch(option.value) {
                case Option::UNKNOWN:
                        break;
                case Option::DOMAIN:
                        _read_domain_list(r);
                        break;
                default:
                        r.add(option);
                        break;
                }
                _peak_and_read(",");
        }
}

void rule_parser::_read_domain_list(rule &r)
{
        _peak_and_read("=");
        while(!_peak(",") && !_is_end()) {
                unsigned int length;
                const char* start = _curr;
                bool is_exception = _peak_and_read("~");
                for( length = 0; !_peak_and_read("|") && !_peak(",") && _read(); length++);
                r.add(excludable<string>(std::string(start + is_exception, length), is_exception));
        }
}

char rule_parser::_read()
{
        return *_curr == '\0' ? '\0' : *(_curr++);
}

bool rule_parser::_read(const char *seq)
{
        unsigned int i;
        for( i = 0; seq[i] == *_curr  && seq[i] != '\0'; i++, _curr++);
        return seq[i] == '\0';
}

char rule_parser::_peak()
{
        return *_curr;
}

bool rule_parser::_peak(const char* seq)
{
        unsigned int i;
        for( i = 0; seq[i] == _curr[i] && seq[i] != '\0'; i++);
        return seq[i] == '\0';
}

bool rule_parser::_peak_and_read(const char *seq)
{
        return _peak(seq) && _read(seq);
}

bool rule_parser::_is_end()
{
        return *_curr == '\0';
}

bool rule_parser::_read_option(const char *seq, Option opt, excludable<Option> &out)
{
        out.value = _peak_and_read(seq) ? opt : Option::UNKNOWN;
        return out.value != Option::UNKNOWN;
}
