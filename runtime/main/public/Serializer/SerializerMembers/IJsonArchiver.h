#pragma once
#include"Utility/String/HMString.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <rapidjson/prettywriter.h> // prettywriterをインクルード
#include<rapidjson/istreamwrapper.h>
#include<fstream>
#include "Reflection/Refrection.hpp"
#undef LoadString
#undef GetObject
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



namespace HARMONY
{
	namespace SERIALIZER
	{
		class UTILITY_API IJsonArchiver
		{
		public:
			IJsonArchiver(const TCHAR* jsonStr);
			IJsonArchiver(Ifstream& ifs);
			~IJsonArchiver();
			template<typename T, typename Tp = std::remove_cvref_t<T>>
			bool operator&(T&& obj);
		private:
			Document doc;
		};
		namespace DETAIL
		{
			bool UTILITY_API LoadNumeric(const Value& value, Property* prop, void*& object);
			bool UTILITY_API LoadArray(const Value& value, Property* prop, void** object);
			bool UTILITY_API LoadObject(const Value& reader, Class* classPtr, void** obj); // オブジェクトをシリアライズする関数
		}
		 
		template<typename T, typename Tp>
		bool IJsonArchiver::operator&(T&& obj)
		{
			Class* class_ = std::remove_pointer_t<Tp>::StaticGetClass();
			Value& source = doc[class_->GetName()];
			if (source.IsObject()) {
				auto memberIt = source.FindMember(TSTR("type"));
				if (memberIt != source.MemberEnd()) {
					auto& firstMemberName = memberIt->value;
					// firstMemberName を GetClassByName の引数として使用
					Class* specificClass = ClassBuilder::GetClassByname(firstMemberName.GetString());
					void* temp = obj;
					DETAIL::LoadObject(source, specificClass, &temp);
					if (temp != nullptr) {
						obj = static_cast<Tp>(temp); // ここでtempの変更をobjに反映
					}
					printf("");
				}
			}
			return true;
		}
	}
}