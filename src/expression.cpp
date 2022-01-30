//
// Created by jond on 27.01.2022.
//
#include <queue>
#include <stdexcept>
#include <iostream>

#include "../include/expression/expression.hpp"

namespace expression {

    inline static std::exception_ptr ex_ptr;

    Expression::Expression(){
        id_=0;
    }

    Expression::Expression(
            const std::vector<std::string>::const_iterator &it,
            const scalc::filemanager::FileManager &fm) : arg_iterator_(it + 1), fm_(fm) {
        id_++;
    }

    void Expression::initialize()  {
        operator_ = evaluateOperator();
        number_ = evaluateNumber();

        while (parseArg()) { arg_iterator_++; }
    }

    std::set<uint32_t> Expression::evaluateExpression(const std::vector<std::string> &input) {
        if(input.empty()){
            throw std::invalid_argument("Wrong expression given!");
        }
        arg_iterator_ = input.begin() + 1;
        initialize();
        waitForWorkers();
        checkException();
        return evaluateExpression();
    }

    std::set<uint32_t> Expression::evaluateExpression() {
        std::lock_guard<std::mutex> lock(mtx_);

        // Wait for all threads (nested expressions and file reads)
        waitForWorkers();

        // Go through all files and compute all integer occurrences by multiplication
        // Add occurrences of file with the same path to all integer keys it contains
        std::unordered_map<uint32_t, uint32_t> occurrences;
        std::set<uint32_t> temp_set;

        for (const auto&[key, val]: file_occurrences_) {
            temp_set = fm_.getFileSet(key);
            for (const uint32_t &number: temp_set) {
                if (occurrences.contains(number)) {
                    occurrences.find(number)->second += val;
                } else {
                    occurrences.insert(std::pair(number, val));
                }
            }
        }

        // Evaluate all expression sets in this expression and put them in occurrences map
        for (const auto&[key, value]: expressions_) {
            for (const auto &number: value) {
                if (occurrences.contains(number)) {
                    occurrences.find(number)->second++;
                } else {
                    occurrences.insert(std::pair(number, 1));
                }
            }

        }
        temp_set.clear();

        // Compare all integer occurrences with given number
        for (const auto&[key, value]: occurrences) {
            switch (OperatorType.at(operator_)) {
                case EQ:
                    if (value == number_) {
                        temp_set.insert(key);
                    }
                    break;
                case GR:
                    if (value > number_) {
                        temp_set.insert(key);
                    }
                    break;
                case LE:
                    if (value < number_) {
                        temp_set.insert(key);
                    }
                    break;
            }
        }
        return temp_set;
    }

    bool Expression::parseArg() {
        bool ret_val = true;
        std::shared_ptr<expression::Expression> ex;
        std::string arg = getArg();

        if (OperatorType.contains(arg)) {
            // Expression case
            switch (OperatorType.find(arg)->second) {
                case OP:
                    // Expression open parenthesis - initialize new Expression parser
                    ex = std::make_shared<expression::Expression>(arg_iterator_, fm_);
                    ex->initialize();
                    workers_.emplace_back(std::thread([ex, this](){
                        expressions_.insert(
                                std::pair(
                                        ex->id(),
                                        ex->evaluateExpression()));
                    }));
                    arg_iterator_ = ex->arg_iterator(); // actualize iterator after parsing

                    break;
                case CP:
                    // Expression close parenthesis - finish actual Expression parser
                    ret_val = false;
                    break;
            }
        } else {
            // File case
            if(!fm_.fileExists(arg)){
                throw std::invalid_argument("File " + arg + " doesn't exist!");
            }
            workers_.emplace_back(std::thread([arg, this](){
                if(fm_.readFile(arg)) {
                    if (file_occurrences_.contains(arg)) {
                        file_occurrences_.find(arg)->second += 1;
                    } else {
                        file_occurrences_.insert(std::pair(arg, 1));
                    }
                } else {
                    try{
                        throw std::runtime_error("File parsing failed! Check its content! (" + arg + ")");
                    } catch(...){
                        ex_ptr = std::current_exception();
                    }
                }
            }));
        }

        return ret_val;
    }

    std::string Expression::getArgStep() {
        return (arg_iterator_++)->data();
    }

    std::string Expression::getArg() {
        return arg_iterator_->data();
    }

    std::string Expression::evaluateOperator() {
        std::string op = getArgStep();
        if (!OperatorType.contains(op)) {
            throw std::invalid_argument("Operator " + op + " not recognized!");
        }
        return op;
    }

    uint32_t Expression::evaluateNumber() {
        std::string num_str = getArgStep();
        try {
            return static_cast<uint32_t>(std::stoi(num_str)); // number - N
        } catch (std::bad_cast &bc) {
            throw std::invalid_argument("Invalid number " + num_str + " in expression " + operator_);
        }
    }

    void Expression::checkException() {
        if(ex_ptr){
            std::rethrow_exception(ex_ptr);
        }
    }

    void Expression::waitForWorkers() {
        for (auto &&w: workers_) {
            if (w.joinable()) {
                w.join();
            }
        }
    }
}