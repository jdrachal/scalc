//
// Created by jond on 27.01.2022.
//

#include <fstream>
#include <algorithm>
#include "../include/filemanager/filemanager.hpp"

namespace scalc::filemanager {

    FileManager::FileManager(const FileManager &fileManager) {
        files_data_ = fileManager.files_data();
    }

    void FileManager::addFileData(const std::string &file_path, const std::set<uint32_t> &data_set) {
        files_data_.insert(std::pair(file_path, data_set));
    };

    bool FileManager::fileExists(const std::string &name) {
        std::ifstream f(name.c_str());
        return f.good();
    }

    bool FileManager::readFile(const std::string &file_path) {
        std::lock_guard<std::mutex> lock(mtx_);
        std::set<uint32_t> temp_set;
        bool ret_val = false;

        if (files_data_.contains(file_path)){
            return true;
        }

        std::ifstream fs(file_path);
        std::string ln;
        while (std::getline(fs, ln)) {
            if(std::all_of(ln.begin(), ln.end(), ::isdigit)) {
                temp_set.insert(static_cast<uint32_t>(std::stoul(ln)));
            }
        }

        if(!temp_set.empty()){
            addFileData(file_path, temp_set);
            ret_val = true;
        }

        return ret_val;
    };


    std::set<uint32_t> FileManager::getFileSet(const std::string &file_path) {
        return files_data_.find(file_path)->second;
    };
}