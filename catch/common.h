#ifndef COMMON_H
#define COMMON_H

#include "catch.hpp"
#include <algorithm>
#include <string>
#include <vector>

template<typename T>
inline void CHECK_EQUALS(std::string label, std::vector<T> actual, std::vector<T> expected){
        INFO("[" << label << "]");
        CHECK(actual.size() == expected.size());

        unsigned int i;
        for(i = 0; i < actual.size() && i < expected.size(); i++){
                CHECK(actual[i] == expected[i]);
        }
        for(; i < actual.size(); i++){
                WARN("Additional: " << actual[i]);
        }
        for(; i < expected.size(); i++){
                WARN("Missing: " << expected[i]);
        }
}

template<typename T>
inline void CHECK_EQUALS_IGNORE_ORDER(std::vector<T> actual, std::vector<T> expected){
        CHECK(actual.size() == expected.size());
        std::sort(actual.begin(), actual.end());
        std::sort(expected.begin(), expected.end());

        unsigned int i;
        for(i = 0; i < actual.size() && i < expected.size(); i++){
                CHECK(actual[i] == expected[i]);
        }
        for(; i < actual.size(); i++){
                WARN("Additional: " << actual[i]);
        }
        for(; i < expected.size(); i++){
                WARN("Missing: " << expected[i]);
        }
}


#endif // COMMON_H
