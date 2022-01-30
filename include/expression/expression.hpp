//
// Created by jond on 27.01.2022.
//

#ifndef SCALC_EXPRESSION_H
#define SCALC_EXPRESSION_H

#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include <future>
#include "../util/util.hpp"
#include "../filemanager/filemanager.hpp"
#include "gtest/gtest.h"


namespace expression {
class Expression {
    private:
        std::string operator_;
        uint32_t number_;
        inline static identifier id_;

        std::vector<std::thread> workers_;
        std::unordered_map<identifier, std::set<uint32_t>> expressions_;
        scalc::filemanager::FileManager fm_;
        std::vector<std::string>::const_iterator arg_iterator_;
        std::unordered_map<std::string, uint32_t> file_occurrences_;
        std::mutex mtx_;


        std::string getArg();
        std::string getArgStep();
        std::string evaluateOperator();
        uint32_t evaluateNumber();
        bool parseArg();
        void waitForWorkers();

    public:
        Expression();
        Expression(const std::vector<std::string>::const_iterator &it, const scalc::filemanager::FileManager &fm);

        void initialize();
        std::set<uint32_t> evaluateExpression(const std::vector<std::string> &input);
        std::set<uint32_t> evaluateExpression();


        void checkException();   // method to check if exception occurred in Expression when called in separate thread

        static const identifier & id(){ return id_; }
        const std::vector<std::string>::const_iterator & arg_iterator() const { return arg_iterator_; }
        std::vector<std::string>::const_iterator & arg_iterator() { return arg_iterator_; }
};
}

#endif //SCALC_EXPRESSION_H
