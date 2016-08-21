#ifndef ENUMS_H
#define ENUMS_H

#include <iostream>

enum class Option {
        UNKNOWN = 0,
        DO_NOT_TRACK,
        DOCUMENT,
        DOMAIN,
        ELEMENT_HIDE,
        GENERIC_HIDE,
        GENERIC_BLOCK,
        IMAGE,
        MATCH_CASE,
        OTHER,
        OBJECT,
        OBJECT_SUBREQUEST,
        PING,
        SCRIPT,
        SITEKEY,
        STYLESHEET,
        SUBDOCUMENT,
        THIRD_PARTY,
        XML_HTTP_REQUEST
};

std::ostream& operator<< (std::ostream & os, Option opt);

#endif // ENUMS_H
