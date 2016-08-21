list(APPEND FILTER_SRCS
    "filter.cpp"
    "enums.cpp"
    "excludable.hpp"
    "rule.cpp"
    "rule_parser.cpp"
)

add_library(filter STATIC ${FILTER_SRCS})
