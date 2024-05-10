#include"Utility/filehelper/Json/JsonHelper.h"
#include"JsonObject_impl.h"

Document doc;

JsonObject* JsonHelper::LoadJson(Ifstream& ifs)
{
	if (ifs) { // ストリームが有効かどうかを確認
		StreamWrapper isw(ifs);
		doc.ParseStream(isw);
		if (doc.HasParseError()) { // パースエラーがあるかどうかを確認
			return nullptr;
		}
		else {
			return new (GC_NEW(JsonObject_impl)) JsonObject_impl(doc);
		}
	}
	return nullptr;
}

JsonObject* JsonHelper::LoadJson(const TCHAR* jsonStr)
{
	return nullptr;
}

bool JsonHelper::SaveJson(const Ofstream& ofs, JsonObject* obj)
{
	return false;
}

bool JsonHelper::SaveJson(const TCHAR* jsonStr)
{
	return false;
}