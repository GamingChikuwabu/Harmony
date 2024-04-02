#pragma once
#include <filesystem>
#include <fstream>
//#include"../thirdparty/rapidjson/rapidjson/document.h"
//#include"../thirdparty/rapidjson/rapidjson/istreamwrapper.h"
//#include <string>
//
//std::filesystem::path FindMetaFileWithGUID(const std::filesystem::path& rootDir, const std::string& guid) {
//    if (!std::filesystem::exists(rootDir) || !std::filesystem::is_directory(rootDir)) {
//        throw std::runtime_error("Invalid root directory: " + rootDir.string());
//    }
//
//    for (const auto& entry : std::filesystem::recursive_directory_iterator(rootDir)) { 
//        if (entry.is_regular_file() && entry.path().extension() == ".meta") {
//            std::ifstream file(entry.path());
//            if (!file.is_open()) {
//                continue;  // ファイルが開けない場合、スキップ
//            }
//
//            rapidjson::IStreamWrapper isw(file);
//            rapidjson::Document document;
//            document.ParseStream(isw);
//
//            if (document.HasParseError()) {
//                continue;  // JSON解析エラーがあればスキップ
//            }
//
//            if (document.HasMember("guid") && document["guid"].IsString()) {
//                std::string fileGUID = document["guid"].GetString();
//                if (fileGUID == guid) {
//                    return entry.path();  // 一致するGUIDを持つ.metaファイルを見つけた
//                }
//            }
//        }
//    }
//
//    throw std::runtime_error("Meta file with GUID not found: " + guid);
//}
//
//std::string RemoveMetaExtension(const std::filesystem::path& filePath) {
//    std::string pathStr = filePath.string();
//    const std::string extension = ".meta";
//
//    // パスの終わりが ".meta" であるかをチェック
//    if (pathStr.size() >= extension.size() &&
//        pathStr.substr(pathStr.size() - extension.size()) == extension) {
//        // ".meta" を取り除く
//        return pathStr.substr(0, pathStr.size() - extension.size());
//    }
//    else {
//        // ".meta" 拡張子を持たない場合、元のパスをそのまま返す
//        return pathStr;
//    }
//}