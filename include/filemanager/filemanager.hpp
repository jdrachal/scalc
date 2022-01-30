//
// Created by jond on 27.01.2022.
//

#ifndef SCALC_FILEMANAGER_HPP
#define SCALC_FILEMANAGER_HPP


#include <unordered_map>
#include <string>
#include <set>
#include <mutex>

namespace scalc::filemanager {

    class FileManager {
    private:
        std::unordered_map<std::string, std::set<uint32_t>> files_data_;
        std::mutex mtx_;

        void addFileData(const std::string &file_path, const std::set<uint32_t> &data_set);

    public:
        FileManager() = default;
        FileManager(const FileManager &fileManager);

        std::set<uint32_t> getFileSet(const std::string &file_path);
        bool readFile(const std::string &file_path);
        bool fileExists (const std::string& name);

        const std::unordered_map<std::string, std::set<uint32_t>> & files_data() const { return files_data_; }
    };
}


#endif //SCALC_FILEMANAGER_HPP
