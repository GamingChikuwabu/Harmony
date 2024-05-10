#pragma once
#include"Utility/filehelper/Json/JsonObject.h"
#include"rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <rapidjson/prettywriter.h> 
#include <rapidjson/istreamwrapper.h>

#ifdef UNICODE
#ifdef _WIN32 // UTF16 for Windows
using Document = rapidjson::GenericDocument<rapidjson::UTF16<>>;
using Value = rapidjson::GenericValue<rapidjson::UTF16<>>;
// UTF-16版のReaderを定義
using Reader = rapidjson::GenericReader<rapidjson::UTF16<>, rapidjson::UTF16<>>;
using StringBuffer = rapidjson::GenericStringBuffer<rapidjson::UTF16<>>;
using Writer = rapidjson::PrettyWriter<StringBuffer, rapidjson::UTF16<>, rapidjson::UTF16<>>;
using StreamWrapper = rapidjson::WIStreamWrapper;
#else // UTF32 for Unix-like systems
using Document = rapidjson::GenericDocument<rapidjson::UTF32<>>;
using Value = rapidjson::GenericValue<rapidjson::UTF32<>>;
// UTF-32版のReaderを定義
using Reader = rapidjson::GenericReader<rapidjson::UTF32<>, rapidjson::UTF32<>>;
using StringBuffer = rapidjson::GenericStringBuffer<rapidjson::UTF32<>>;
using Writer = rapidjson::Writer<StringBuffer, rapidjson::UTF32<>, rapidjson::UTF32<>>;
#endif // _WIN32
#else // Multibyte character set
using Document = rapidjson::Document;
using Value = rapidjson::Value;
// マルチバイト文字セット用のReaderを定義
using Reader = rapidjson::Reader;
using StringBuffer = rapidjson::StringBuffer;
using Writer = rapidjson::Writer<StringBuffer>;
#endif

class JsonObject_impl : public JsonObject
{
public:
	JsonObject_impl(const Value& value);
	~JsonObject_impl();

	JsonObject* GetObject(const HMString& key)const;
	HMArray<JsonObject*> GetArray(const HMString& key)const;
	HMString GetString(const HMString& key)const;
	int32_t GetInt(const HMString& key)const;
	float GetFloat(const HMString& key)const;
	bool GetBool(const HMString& key)const;
	bool IsNull() const override;
private:
	const Value& _value;
};