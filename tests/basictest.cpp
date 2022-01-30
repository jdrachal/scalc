//
// Created by jond on 28.01.2022.
//

#include <fstream>
#include "gtest/gtest.h"
#include "../include/expression/expression.hpp"
#include "../include/filemanager/filemanager.hpp"

constexpr char data_dir[] = "./files/data/";

constexpr char examples_dir[] = "./files/input/examples/";
constexpr char valid_data_dir[] = "./files/input/valid_data/";
constexpr char invalid_data_dir[] = "./files/input/invalid_data/";

constexpr char examples_dir_o[] = "./files/output/examples/";

constexpr char space_delim = ' ';

std::set<uint32_t> getOutputFromFile(std::string path){
    std::set<uint32_t> ret_set;

    std::ifstream fs(path);
    std::string ln;
    while (std::getline(fs, ln)) {
        ret_set.insert(std::stoi(ln));
    }

    return ret_set;
}

std::string getInputFromFile(std::string path){
    std::vector<std::string> test_expressions;

    std::ifstream fs(path);
    std::string line;
    std::getline(fs, line);
    return line;
}

std::vector<std::string> splitExpression(std::string exp){
    std::vector<std::string> expression_args;
    std::istringstream iss(exp);
    std::string s;
    while ( getline( iss, s, space_delim ) ) {
        expression_args.push_back(s);
    }
    return expression_args;
}


TEST(BasicTest, dataTestA){
    std::string filename = "a.txt";
    std::set<uint32_t> s = {1, 2, 3};
    std::set<uint32_t> out = getOutputFromFile(data_dir + filename);
    EXPECT_EQ(s, out);
}

TEST(BasicTest, dataTestB){
    std::string filename = "b.txt";
    std::set<uint32_t> s = {2, 3, 4};
    std::set<uint32_t> out = getOutputFromFile(data_dir + filename);
    EXPECT_EQ(s, out);
}

TEST(BasicTest, dataTestC){
    std::string filename = "c.txt";
    std::set<uint32_t> s = {1, 2, 3, 4, 5};
    std::set<uint32_t> out = getOutputFromFile(data_dir + filename);
    EXPECT_EQ(s, out);
}

TEST(FileManager, fileExists){
    std::string filename = data_dir + std::string("a.txt");
    scalc::filemanager::FileManager fm;
    EXPECT_TRUE(fm.fileExists(filename));
}

TEST(FileManager, fileDoentExist){
    std::string filename = data_dir + std::string("m.txt");
    scalc::filemanager::FileManager fm;
    EXPECT_FALSE(fm.fileExists(filename));
}

TEST(FileManager, validFileRead){
    std::string filename = data_dir + std::string("a.txt");
    scalc::filemanager::FileManager fm;
    EXPECT_TRUE(fm.readFile(filename));
}

TEST(FileManager, validFileGetSet){
    std::string filename = data_dir + std::string("a.txt");
    std::set<uint32_t> s = {1, 2, 3};

    scalc::filemanager::FileManager fm;
    fm.readFile(filename);
    EXPECT_EQ(s, fm.getFileSet(filename));
}


TEST(FileManager, fileEmpty){
    std::string filename = data_dir + std::string("x.txt");
    scalc::filemanager::FileManager fm;
    EXPECT_FALSE(fm.readFile(filename));
}

TEST(FileManager, fileLetters){
    std::string filename = data_dir + std::string("y.txt");
    scalc::filemanager::FileManager fm;
    EXPECT_FALSE(fm.readFile(filename));
}

TEST(FileManager, fileOneLine){
    std::string filename = data_dir + std::string("z.txt");
    scalc::filemanager::FileManager fm;
    EXPECT_FALSE(fm.readFile(filename));
}

TEST(Expression, evaluateExpressionExample1){
    std::string filename = "ex1.txt";
    std::string expression = getInputFromFile(examples_dir + filename);
    std::set<uint32_t> out = getOutputFromFile(examples_dir_o + filename);

    std::vector<std::string> args = splitExpression(expression);
    expression::Expression ex;
    std::set<uint32_t> s = ex.evaluateExpression(args);

    EXPECT_EQ(s, out);
}

TEST(Expression, evaluateExpressionExample2){
    std::string filename = "ex2.txt";
    std::string expression = getInputFromFile(examples_dir + filename);
    std::set<uint32_t> out = getOutputFromFile(examples_dir_o + filename);

    std::vector<std::string> args = splitExpression(expression);
    expression::Expression ex;
    std::set<uint32_t> s = ex.evaluateExpression(args);

    EXPECT_EQ(s, out);
}

TEST(Expression, evaluateExpressionValidData1){
    std::string filename = "ex1.txt";
    std::string expression = getInputFromFile(valid_data_dir + filename);

    std::vector<std::string> args = splitExpression(expression);
    expression::Expression ex;

    EXPECT_NO_THROW( ex.evaluateExpression(args));
}

TEST(Expression, evaluateExpressionValidData2){
    std::string filename = "ex2.txt";
    std::string expression = getInputFromFile(valid_data_dir + filename);

    std::vector<std::string> args = splitExpression(expression);
    expression::Expression ex;

    EXPECT_NO_THROW( ex.evaluateExpression(args));
}


TEST(Expression, evaluateExpressionValidData3){
    std::string filename = "ex3.txt";
    std::string expression = getInputFromFile(valid_data_dir + filename);

    std::vector<std::string> args = splitExpression(expression);
    expression::Expression ex;

    EXPECT_NO_THROW( ex.evaluateExpression(args));
}

TEST(Expression, evaluateExpressionValidData4){
    std::string filename = "ex4.txt";
    std::string expression = getInputFromFile(valid_data_dir + filename);

    std::vector<std::string> args = splitExpression(expression);
    expression::Expression ex;

    EXPECT_NO_THROW( ex.evaluateExpression(args));
}

TEST(Expression, evaluateExpressionInvalidData1){
    std::string filename = "ex1.txt";
    std::string expression = getInputFromFile(invalid_data_dir + filename);

    std::vector<std::string> args = splitExpression(expression);
    expression::Expression ex;

    EXPECT_ANY_THROW(ex.evaluateExpression(args));
}

TEST(Expression, evaluateExpressionInvalidData2){
    std::string filename = "ex2.txt";
    std::string expression = getInputFromFile(invalid_data_dir + filename);

    std::vector<std::string> args = splitExpression(expression);
    expression::Expression ex;

    EXPECT_ANY_THROW(ex.evaluateExpression(args));
}

TEST(Expression, evaluateExpressionInvalidData3){
    std::string filename = "ex3.txt";
    std::string expression = getInputFromFile(invalid_data_dir + filename);

    std::vector<std::string> args = splitExpression(expression);
    expression::Expression ex;

    EXPECT_ANY_THROW(ex.evaluateExpression(args));
}

TEST(Expression, evaluateExpressionInvalidData4){
    std::string filename = "ex4.txt";
    std::string expression = getInputFromFile(invalid_data_dir + filename);

    std::vector<std::string> args = splitExpression(expression);
    expression::Expression ex;

    EXPECT_ANY_THROW(ex.evaluateExpression(args));
}

TEST(Expression, evaluateExpressionInvalidData5){
    std::string filename = "ex5.txt";
    std::string expression = getInputFromFile(invalid_data_dir + filename);

    std::vector<std::string> args = splitExpression(expression);
    expression::Expression ex;

    EXPECT_ANY_THROW(ex.evaluateExpression(args));
}

int main(int argc, char* argv[]){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}