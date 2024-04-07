#include"SerializerMembers/IJsonArchiver.h"

namespace HARMONY
{
	namespace SERIALIZER
	{
		IJsonArchiver::IJsonArchiver(const TCHAR* jsonStr)
		{
			doc.Parse(jsonStr);
		}
		IJsonArchiver::IJsonArchiver(Ifstream& ifs)
		{
			StreamWrapper isw(ifs);
			doc.ParseStream(isw);
		}
		IJsonArchiver::~IJsonArchiver()
		{

		}

		namespace DETAIL
		{
			bool LoadNumeric(const Value& value, Property* prop, void*& object)
			{
				// 各数値型のプロパティ設定に正しいメソッドを使用
				switch (prop->GetKind()) {
				case PropertyKind::Bool:
					prop->SetPropertyValue<bool>(object, value.GetBool());
					break;
				case PropertyKind::String:
					prop->SetPropertyValue<HMString>(object, value.GetString());
					break;
				case PropertyKind::Int32:
					prop->SetPropertyValue<int32_t>(object, value.GetInt());
					break;
				case PropertyKind::UInt32:
					prop->SetPropertyValue<uint32_t>(object, value.GetUint());
					break;
				case PropertyKind::Int64:
					prop->SetPropertyValue<int64_t>(object, value.GetInt64());
					break;
				case PropertyKind::UInt64:
					prop->SetPropertyValue<uint64_t>(object, value.GetUint64());
					break;
				case PropertyKind::Float:
					prop->SetPropertyValue<float>(object, value.GetFloat());
					break;
				case PropertyKind::Double:
					prop->SetPropertyValue<double>(object, value.GetDouble());
					break;
				default:
					return false; // 未対応のプロパティ型
				}
				return true;
			}

			bool LoadArray(const Value& value, Property* prop, void** object)
			{
				return true;
			}

			bool LoadObject(const Value& reader, Class* classPtr, void** obj)
			{
				if (*obj == nullptr)
				{
					*obj = classPtr->Create();//ここでnewする
				}

				auto memberJsonObject = reader.FindMember(TSTR("members"));
				if (!memberJsonObject->value.IsNull() && reader.MemberEnd() != memberJsonObject)
				{
					const auto& value = memberJsonObject->value.GetObject(); 
					for (auto member : classPtr->GetProperties())
					{
						auto jsonMember = value.FindMember(member->GetPropertyName());
						if (member->GetKind() == PropertyKind::Class)
						{
							auto prop = static_cast<PropertyClass*>(member);
							auto temp = prop->GetPropertyValue(obj);
							LoadObject(jsonMember->value, prop->GetPropertyClass(),&temp);
							prop->SetPropertyValue(*obj,temp);
						}
						else if (member->GetKind() == PropertyKind::Array)
						{

						}
						else
						{
							void* tempNum = nullptr;
							member->GetPropertyValue(obj);
							LoadNumeric(jsonMember->value, member, tempNum);
						}
					}
				}
				auto baseIt = reader.FindMember(TSTR("base"));
				if (baseIt != reader.MemberEnd() && !baseIt->value.IsNull()) 
				{
					auto baseObjectJsonStr = baseIt->value.FindMember(classPtr->GetBaseClass()->GetName());
					LoadObject(baseObjectJsonStr->value, classPtr->GetBaseClass(), obj);
				}
				return true;
			}
		}
	}
}