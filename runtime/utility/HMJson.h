#pragma once
#include"../thirdparty/rapidjson/rapidjson/document.h"
#include"../thirdparty/rapidjson/rapidjson/istreamwrapper.h"
#include<filesystem>
#include <string>
#include<fstream>

static inline rapidjson::Document LoadJson(const char* path)
{
    std::filesystem::path projpath = path;

    // JSONファイルがあるかを確認
    if (!std::filesystem::exists(projpath))
    {
        throw std::runtime_error("JSON file not found: " + projpath.string());
    }

    std::ifstream file(projpath);
    rapidjson::IStreamWrapper isw(file);
    rapidjson::Document json_obj;
    if (file.fail()) {
        throw std::runtime_error("Failed to open JSON file: " + projpath.string());
    }

    json_obj.ParseStream(isw);
    if (json_obj.HasParseError()) {
        throw std::runtime_error("Error parsing JSON file: " + projpath.string());
    }

    return json_obj;
}