#include"OJsonSerializer.h"
#pragma once
#include<type_traits>
#include"Utility.hpp"
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
			bool SERIALIZER_API SaveInt(Writer& value, Property* prop,void* object);
			bool SERIALIZER_API SaveFlat(Writer& value, Property* prop,void* object);
			bool SERIALIZER_API SaveString(Writer& value, Property* prop, void* object);
		}

		template<typename T>
		HMString OJsonSerializer::operator&(T& obj)
		{
			StringBuffer sb;
			Writer writer(sb);
			if constexpr (HasGetClass<T>)
			{
				writer.StartObject();
				HARMONY::Class* pclass =  T::GetClass();
				for (auto prop : pclass->GetProperties())
				{
					writer.Key(prop->GetName());
					auto kind = prop->GetKind();
					if (kind == PropertyKind::Bool)
					{
						DETAIL::SaveBool(writer,prop,&obj);
					}
					else if (kind == PropertyKind::Int32)
					{
						DETAIL::SaveInt(writer, prop, &obj);
					}
					else if (kind == PropertyKind::Int64)
					{
						DETAIL::SaveInt(writer, prop, &obj);
					}
					else if (kind == PropertyKind::Float)
					{
						DETAIL::SaveFlat(writer, prop, &obj);
					}
					else if (kind == PropertyKind::Array)
					{

					}
					else if (kind == PropertyKind::Class)
					{

					}
					else if (kind == PropertyKind::String)
					{
						DETAIL::SaveString(writer, prop, &obj);
					}
					else if (kind == PropertyKind::Map)
					{

					}
					else if (kind == PropertyKind::Object)
					{

					}
				}
				writer.EndObject();
			}
			return HMString(sb.GetString());
		}
	}
}