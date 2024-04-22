#pragma once
#include <filesystem>
#include <fstream>
#include"HMString.h"
#include"../..\thirdparty/include/rapidjson/rapidjson/document.h"
#include"../..\thirdparty/include/rapidjson/rapidjson/istreamwrapper.h"

#ifdef UNICODE
#ifdef _WIN32 // UTF16 for Windows
using Document = rapidjson::GenericDocument<rapidjson::UTF16<>>;
using Value = rapidjson::GenericValue<rapidjson::UTF16<>>;
// UTF-16版のReaderを定義
using Reader = rapidjson::GenericReader<rapidjson::UTF16<>, rapidjson::UTF16<>>;
using Ifstream = std::wifstream;
using StreamWrapper = rapidjson::WIStreamWrapper;
#else // UTF32 for Unix-like systems
using Document = rapidjson::GenericDocument<rapidjson::UTF32<>>;
using Value = rapidjson::GenericValue<rapidjson::UTF32<>>;
// UTF-32版のReaderを定義
using Reader = rapidjson::GenericReader<rapidjson::UTF32<>, rapidjson::UTF32<>>;
#endif // _WIN32
#else // Multibyte character set
using Document = rapidjson::Document;
using Value = rapidjson::Value;
// マルチバイト文字セット用のReaderを定義
using Reader = rapidjson::Reader;
#endif

std::filesystem::path FindMetaFileWithGUID(const std::filesystem::path& rootDir, const TCHAR* guid) {
    if (!std::filesystem::exists(rootDir) || !std::filesystem::is_directory(rootDir)) {
        throw std::runtime_error("Invalid root directory: " + rootDir.string());
    }

    for (const auto& entry : std::filesystem::recursive_directory_iterator(rootDir)) { 
        if (entry.is_regular_file() && entry.path().extension() == ".meta") {
            Ifstream file(entry.path());
            if (!file.is_open()) {
                continue;  // ファイルが開けない場合、スキップ
            }

            StreamWrapper isw(file);
            Document document;

            document.ParseStream(isw);

            if (document.HasParseError()) {
                continue;  // JSON解析エラーがあればスキップ
            }

            if (document.HasMember(TSTR("guid")) && document[TSTR("guid")].IsString()) { 
                const TCHAR* fileGUID = document[TSTR("guid")].GetString();
                if (HARMONY::HMString(fileGUID) == guid) {
                    return entry.path();  // 一致するGUIDを持つ.metaファイルを見つけた
                }
            }
        }
    }

    throw std::runtime_error("Meta file with GUID not found: ");
}


HARMONY::HMString RemoveMetaExtension(const std::filesystem::path& filePath) {
    const std::wstring extension = TSTR(".meta");
    std::wstring pathStr = filePath.c_str();

    // パスの終わりが ".meta" であるかをチェック
    if (pathStr.size() >= extension.size() &&
        pathStr.substr(pathStr.size() - extension.size()) == extension) {
        
        return HARMONY::HMString(pathStr.substr(0, pathStr.size() - extension.size()).c_str());
    }
    else {
        // ".meta" 拡張子を持たない場合、元のパスをそのまま返す
        return HARMONY::HMString(pathStr.c_str());
    }
}