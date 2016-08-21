#ifndef FILTER_H
#define FILTER_H

#include "rule.h"
#include <string>

class filter
{
public:
    filter();
    static rule parse(const std::string& str);

};

#endif // FILTER_H
