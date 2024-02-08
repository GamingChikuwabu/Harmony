#include"Archive/JsonOArchive.h"
#include"rapidjson/document.h"
#include"rapidjson/ostreamwrapper.h"
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace HARMONY
{
	struct JsonOArchive_impl
	{
		rapidjson::Document _doc;
		std::vector<rapidjson::Value> contextStack; // コンテキストスタック
		// 現在のコンテキストを取得
		rapidjson::Value& GetCurrentContext() {
			if (contextStack.empty()) {
				return _doc;
			}
			else {
				return contextStack.back();
			}
		}
	};

	JsonOArchive::JsonOArchive(std::ofstream& ofs):_ofs(ofs) 
	{
		_impl = new JsonOArchive_impl();
	}

	JsonOArchive::~JsonOArchive()
	{
		// JSONデータを文字列化するためのStringBufferとWriterを準備
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

		// Documentオブジェクトを使ってJSONをシリアライズ
		_impl->_doc.Accept(writer);

		// シリアライズされたJSONデータをファイルに書き込む
		// ここでは、コンストラクタで受け取ったofstream (_ofs) を使用
		_ofs << buffer.GetString();

		// 必要に応じて、_ofs をフラッシュまたはクローズ
		_ofs.flush();

		// メモリの解放やその他のクリーンアップ処理があればここで行う
		delete _impl;
	}

	void JsonOArchive::SaveValue(const char* name, int value) {
		rapidjson::Value key(name, _impl->_doc.GetAllocator());
		rapidjson::Value val(value);

		// 現在のコンテキストに値を追加
		_impl->GetCurrentContext().AddMember(key, val, _impl->_doc.GetAllocator());
	}

	void JsonOArchive::SaveValue(const char* name, float value) {
		rapidjson::Value key(name, _impl->_doc.GetAllocator());
		rapidjson::Value val(value);

		// 現在のコンテキストに値を追加
		_impl->GetCurrentContext().AddMember(key, val, _impl->_doc.GetAllocator());
	}

	void JsonOArchive::SaveValue(const char* name, const std::string& value) {
		rapidjson::Value key(name, _impl->_doc.GetAllocator());
		rapidjson::Value val(value.c_str(), _impl->_doc.GetAllocator());

		// 現在のコンテキストに値を追加
		_impl->GetCurrentContext().AddMember(key, val, _impl->_doc.GetAllocator());
	}

	void JsonOArchive::PushObjectType()
	{
		_impl->contextStack.push_back(rapidjson::Value(rapidjson::kObjectType));
	}

	void JsonOArchive::PopObjectType(const char* parent_name)
	{
		if (!_impl->contextStack.empty()) {
			auto& currentObject = _impl->contextStack.back();
			_impl->contextStack.pop_back();

			// 親コンテキストが存在する場合、現在のオブジェクトを親に追加
			if (!_impl->contextStack.empty()) {
				// ここで親オブジェクトを取得し、現在のオブジェクトを追加
				rapidjson::Value& parent = _impl->GetCurrentContext();
				parent.AddMember(rapidjson::Value(parent_name, _impl->_doc.GetAllocator()).Move(), currentObject, _impl->_doc.GetAllocator());
			}
		}
	}
}