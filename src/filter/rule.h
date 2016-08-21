#ifndef RULE_H
#define RULE_H

#include "enums.h"
#include "excludable.hpp"
#include <string>
#include <vector>

class rule
{
public:
        rule();
        rule(const rule& r);
        rule(rule&& r);

        void operator=(const rule& r);
        void operator=(rule&& r);

        bool is_exception;
        std::string expression;
        std::string css_selector;

        std::vector<std::string> domains;
        std::vector<std::string> domains_excp;
        std::vector<Option> options;
        std::vector<Option> options_excp;

        void add(const excludable<std::string>& domain);
        void add(excludable<std::string>&& domain);
        void add(const excludable<Option>& option);
        void add(excludable<Option>&& option);
};

#endif // RULE_H
