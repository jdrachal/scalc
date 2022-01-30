//
// Created by jond on 27.01.2022.
//

#ifndef SCALC_UTIL_HPP
#define SCALC_UTIL_HPP

#include <string>
#include <unordered_map>
#include <memory>

typedef uint32_t identifier;

enum en_operators{
    EQ,
    GR,
    LE,
    OP,
    CP
};

inline std::unordered_map<std::string, uint32_t> OperatorType = {
        {"EQ", EQ},
        {"GR", GR},
        {"LE", LE},
        {"[", OP},
        {"]", CP}
};

#endif //SCALC_UTIL_HPP
