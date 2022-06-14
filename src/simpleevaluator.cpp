//
// Created by jond on 13.06.2022.
//

#include "../include/expression/simpleevaluator.hpp"
#include "filemanager.hpp"
#include "util/util.hpp"


namespace expression {
    std::set<uint32_t> evaluate(std::vector<std::string> input) {
        std::vector<std::unordered_map<uint32_t, uint32_t>> umaps;
        std::set<uint32_t> temp_set;
        scalc::filemanager::FileManager fm;
        std::vector<uint32_t> nests;
        uint32_t number;
        std::string opr;

        for (int it = input.size() - 1; it >= 0; it--) {

            if (input[it] == "]") {
                std::unordered_map<uint32_t, uint32_t> mp;
                nests.push_back(umaps.size());
                umaps.push_back(mp);

            } else if (std::all_of(input[it].begin(), input[it].end(), ::isdigit)) {


                number = std::stoul(input[it--]);

                if (input[it] == "GR" || input[it] == "LE" || input[it] == "EQ") {
                    opr = input[it--];
                } else {
                    throw "Invalid argument: " + input[it];
                }

                if (input[it] == "[") {

                    if (nests.size() > 1) {
                        for (auto i = umaps.size(); i > nests.back(); i--) {
                            for (const auto&[key, value]: umaps.back()) {
                                if (umaps[nests.back() - 1].contains(key)) {
                                    umaps[nests.back() - 1].find(key)->second += value;
                                } else {
                                    umaps[nests.back() - 1].insert(std::pair(key, value));
                                }
                            }
                            umaps.pop_back();
                        }
                        nests.pop_back();
                    }

                    std::vector<uint32_t> removals;
                    for (const auto&[key, value]: umaps.back()) {
                        switch (OperatorType.at(opr)) {
                            case EQ:
                                if (value != number) {
                                    removals.push_back(key);
                                }
                                break;
                            case GR:
                                if (value <= number) {
                                    removals.push_back(key);
                                }
                                break;
                            case LE:
                                if (value >= number) {
                                    removals.push_back(key);
                                }
                                break;
                        }
                    }

                    for (const auto &r: removals) {
                        umaps.back().erase(r);
                    }

                    for (const auto &[key, value]: umaps.back()) {
                        umaps.back()[key] = 1;
                    }
                } else {
                    throw "Invalid argument: " + input[it];
                }

            } else if (input[it] == "GR" || input[it] == "LE" || input[it] == "EQ") {

                opr = input[it];

            } else if (fm.fileExists(input[it])) {

                for (const uint32_t &number: fm.getFileSet(input[it])) {
                    if (umaps.back().contains(number)) {
                        umaps.back().find(number)->second++;
                    } else {
                        umaps.back().insert(std::pair(number, 1));
                    }
                }

            } else {
                throw "Invalid argument: " + input[it];
            }
        };

        std::set<uint32_t> set;
        for (const auto&[key, value]: umaps.back()) {
            set.insert(key);
        }
        return set;
    }
}