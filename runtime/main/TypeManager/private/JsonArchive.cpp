#include "JsonArchive.h"
#include"HMJson.h"#in
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include<rapidjson/ostreamwrapper.h>

namespace HARMONY
{
	//rapidjson::Document _doc;
	//
	//IJsonArchive::IJsonArchive(std::ifstream& ifs)
	//{
	//	rapidjson::IStreamWrapper isw(ifs);
	//	_doc.ParseStream(isw);
	//	rapidjson::Document::AllocatorType& allocator = _doc.GetAllocator();
	//}
	//IJsonArchive::~IJsonArchive()
	//{

	//}
	//void IJsonArchive::LoadValue(const char* name, int& value)
	//{
	//	value = _doc[name].GetInt();
	//}
	//void IJsonArchive::LoadValue(const char* name, float& value)
	//{
	//	value = _doc[name].GetFloat();
	//}
	//void IJsonArchive::LoadValue(const char* name, double& value)
	//{
	//	value = _doc[name].GetDouble();
	//}
	//void IJsonArchive::LoadValue(const char* name, long& value)
	//{
	//	value = _doc.GetInt64();
	//}
	//void IJsonArchive::LoadValue(const char* name, std::string& value)
	//{
	//	value = _doc[name].GetString();
	//}

	//OJsonArchive::OJsonArchive(std::ofstream& ofs) :OArchive::OArchive(ofs)
	//{
	//	_doc.SetObject();
	//}
	//OJsonArchive::~OJsonArchive()
	//{

	//}

	//void OJsonArchive::to_savefile()
	//{
	//	// ofstreamにUTF-8として書き込むための設定
	//	_ofs << std::noskipws;
	//	// RapidJSONのOStreamWrapperを使用してstd::ofstreamをラップ
	//	rapidjson::OStreamWrapper osw(_ofs);
	//	// Writerを使用してJSONデータをファイルに書き込む
	//	rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
	//	_doc.Accept(writer);
	//}

	//const char* OJsonArchive::to_string() {
	//	rapidjson::StringBuffer buffer;
	//	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	//	_doc.Accept(writer);
	//	auto str = buffer.GetString();
	//	return (str);
	//}

	//void OJsonArchive::SaveValue(const char* name, int& value) {
	//	rapidjson::Value key(name, _doc.GetAllocator());
	//	_doc.AddMember(key, rapidjson::Value(value), _doc.GetAllocator());
	//}

	//void OJsonArchive::SaveValue(const char* name, float& value) {
	//	rapidjson::Value key(name, _doc.GetAllocator());
	//	_doc.AddMember(key, rapidjson::Value(value), _doc.GetAllocator());
	//}

	//void OJsonArchive::SaveValue(const char* name, double& value) {
	//	rapidjson::Value key(name, _doc.GetAllocator());
	//	_doc.AddMember(key, rapidjson::Value(value), _doc.GetAllocator());
	//}

	//void OJsonArchive::SaveValue(const char* name, long& value) {
	//	rapidjson::Value key(name, _doc.GetAllocator());
	//	_doc.AddMember(key, rapidjson::Value(static_cast<int64_t>(value)), _doc.GetAllocator()); // longをint64_tにキャスト
	//}

	//void OJsonArchive::SaveValue(const char* name,std::string& value) {
	//	rapidjson::Value key(name, _doc.GetAllocator());
	//	rapidjson::Value stringValue(value.c_str(), _doc.GetAllocator());
	//	_doc.AddMember(key, stringValue, _doc.GetAllocator());
	//}
}