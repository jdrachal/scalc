//
// Created by jond on 13.06.2022.
//

#ifndef SCALC_SIMPLEEVALUATOR_HPP
#define SCALC_SIMPLEEVALUATOR_HPP

#include <set>
#include <vector>
#include <string>
#include <unordered_map>

namespace expression {
    std::set<uint32_t> evaluate(std::vector<std::string> input);
}

#endif //SCALC_SIMPLEEVALUATOR_HPP
