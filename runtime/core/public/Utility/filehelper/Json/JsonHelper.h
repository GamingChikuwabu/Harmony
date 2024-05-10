#pragma once
#include"Utility/filehelper/filehelpercore.h"
#include"Utility/collections/strings.h"
#include"Utility/filehelper/Json/JsonObject.h"

class CORE_API JsonHelper
{
public:
	/// @brief パスからJsonを読み込む
	/// @param path Jsonファイルのパス
	/// @return リザルト
	static JsonObject* LoadJson(Ifstream& ofs);

	/// @brief Json文字列からJsonを読み込む
	static JsonObject* LoadJson(const TCHAR* jsonStr);

	/// @brief Jsonを保存する
	static bool SaveJson(const Ofstream& ofs, JsonObject* obj);

	static bool SaveJson(const TCHAR* jsonStr);
};