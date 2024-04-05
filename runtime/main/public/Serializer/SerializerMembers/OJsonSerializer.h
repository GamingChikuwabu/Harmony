#pragma once
#include<ostream>
#include"Utility/String/HMString.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "Reflection/Refrection.hpp"

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
		class UTILITY_API OJsonSerializer
		{
		public:
			OJsonSerializer();
			~OJsonSerializer();
			template<typename T, typename Tp = std::remove_cvref_t<T>>
			HMString operator&(T&& obj);
		};
	}
}

namespace HARMONY
{
	namespace SERIALIZER
	{
		namespace DETAIL
		{

			bool UTILITY_API SaveBool(Writer& value, Property* prop, void* object);
			bool UTILITY_API SaveInt(Writer& value, Property* prop, void* object);
			bool UTILITY_API SaveInt64(Writer& value, Property* prop, void* object);
			bool UTILITY_API SaveFloat(Writer& value, Property* prop, void* object);
			bool UTILITY_API SaveDouble(Writer& value, Property* prop, void* object);
			bool UTILITY_API SaveString(Writer& value, Property* prop, void* object);
			bool UTILITY_API SaveArray(Writer& value, Property* prop, void* object);
			bool UTILITY_API SaveClass(Writer& value, Property* prop, void* object);
			bool UTILITY_API SerializeObject(Writer& writer, Class* classPtr, void* obj);// オブジェクトをシリアライズする関数

		}

		template<typename T, typename Tp>
		HMString OJsonSerializer::operator&(T&& obj)
		{
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