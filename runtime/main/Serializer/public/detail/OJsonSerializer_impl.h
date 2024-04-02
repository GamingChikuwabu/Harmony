#include"OJsonSerializer.h"
#pragma once
#include<type_traits>
#include"Refrection.hpp"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

template<typename C>
concept HasGetClass = requires(C * c) {
	{ c->GetClass() } -> std::convertible_to<void*>;
};

#ifdef UNICODE
#ifdef _WIN32 // UTF16 for Windows
using Document = rapidjson::GenericDocument<rapidjson::UTF16<>>;
using Value = rapidjson::GenericValue<rapidjson::UTF16<>>;
using StringBuffer = rapidjson::GenericStringBuffer<rapidjson::UTF16<>>;
using Writer = rapidjson::Writer<StringBuffer, rapidjson::UTF16<>, rapidjson::UTF16<>>;
#else // UTF32 for Unix-like systems
using Document = rapidjson::GenericDocument<rapidjson::UTF32<>>;
using Value = rapidjson::GenericValue<rapidjson::UTF32<>>;
using StringBuffer = rapidjson::GenericStringBuffer<rapidjson::UTF32<>>;
using Writer = rapidjson::Writer<StringBuffer, rapidjson::UTF32<>, rapidjson::UTF32<>>;
#endif // _WIN32
#else // Multibyte character set
using Document = rapidjson::Document;
using Value = rapidjson::Value;
using StringBuffer = rapidjson::StringBuffer;
using Writer = rapidjson::Writer<StringBuffer>;
#endif

namespace HARMONY 
{
	namespace SERIALIZER 
	{
		namespace DETAIL
		{

			bool SERIALIZER_API SaveBool(Writer& value, Property* prop, void* object);
			bool SERIALIZER_API SaveInt(Writer& value, Property* prop, void* object);
			bool SERIALIZER_API SaveInt64(Writer& value, Property* prop, void* object);
			bool SERIALIZER_API SaveFloat(Writer& value, Property* prop, void* object);
			bool SERIALIZER_API SaveDouble(Writer& value, Property* prop, void* object);
			bool SERIALIZER_API SaveString(Writer& value, Property* prop, void* object);
			bool SERIALIZER_API SaveArray(Writer& value, Property* prop, void* object);
			bool SERIALIZER_API SaveClass(Writer& value, Property* prop, void* object);
			bool SERIALIZER_API SerializeObject(Writer& writer, Class* classPtr, void* obj);// オブジェクトをシリアライズする関数

		}

		template<typename T, typename Tp>
		HMString OJsonSerializer::operator&(T&& obj) {
			StringBuffer sb;
			Writer writer(sb);
			// JSONオブジェクト全体の開始
			writer.StartObject();
			if constexpr (std::is_pointer_v<Tp>)
			{
				auto class_ptr = obj->GetClass();
				DETAIL::SerializeObject(writer, class_ptr, obj);
			}
			else if constexpr (std::is_class_v<Tp>)
			{
				// オブジェクトをシリアライズするための関数を呼び出す
				DETAIL::SerializeObject(writer, Tp::GetClass(), static_cast<void*>(&obj));
			}
			// JSONオブジェクト全体の終了
			writer.EndObject();
			return HMString(sb.GetString());
		}
	}
}