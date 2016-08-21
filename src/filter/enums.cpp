#include "enums.h"

std::ostream& operator<< (std::ostream & os, Option opt)
{
        switch (opt) {
        case Option::UNKNOWN             :
                return os << "Option::UNKNOWN";
        case Option::DO_NOT_TRACK        :
                return os << "Option::DO_NOT_TRACK";
        case Option::DOCUMENT            :
                return os << "Option::DOCUMENT";
        case Option::DOMAIN              :
                return os << "Option::DOMAIN";
        case Option::ELEMENT_HIDE        :
                return os << "Option::ELEMENT_HIDE";
        case Option::GENERIC_HIDE        :
                return os << "Option::GENERIC_HIDE";
        case Option::GENERIC_BLOCK       :
                return os << "Option::GENERIC_BLOCK";
        case Option::IMAGE               :
                return os << "Option::IMAGE";
        case Option::MATCH_CASE          :
                return os << "Option::MATCH_CASE";
        case Option::OTHER               :
                return os << "Option::OTHER";
        case Option::OBJECT              :
                return os << "Option::OBJECT";
        case Option::OBJECT_SUBREQUEST   :
                return os << "Option::OBJECT_SUBREQUEST";
        case Option::PING                :
                return os << "Option::PING";
        case Option::SCRIPT              :
                return os << "Option::SCRIPT";
        case Option::SITEKEY             :
                return os << "Option::SITEKEY";
        case Option::STYLESHEET          :
                return os << "Option::STYLESHEET";
        case Option::SUBDOCUMENT         :
                return os << "Option::SUBDOCUMENT";
        case Option::THIRD_PARTY         :
                return os << "Option::THIRD_PARTY";
        case Option::XML_HTTP_REQUEST    :
                return os << "Option::XML_HTTP_REQUEST ";
        }
}
