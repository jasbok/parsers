#ifndef RULE_PARSER_H
#define RULE_PARSER_H

#include "rule.h"

#include <string>
#include <vector>

class rule_parser
{
public:
        rule_parser();
        rule parse(const std::string& str);

private:
        const char * _curr;
        enum class Token;

        Token _read_token();
        void _read_expression(rule& r);
        void _read_selector(rule& r);

        void _read_domains(rule& r);
        void _read_options(rule& r);
        void _read_domain_list(rule& r);

        char _read();
        bool _read(const char* seq);
        char _peak();
        bool _peak(const char* seq);
        bool _peak_and_read(const char* seq);
        bool _is_end();

        bool _read_option(const char* seq, Option opt, excludable<Option>& out);
};

#endif // RULE_PARSER_H
