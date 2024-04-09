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
					prop->SetPropertyValue<HMString>(object, HMString(value.GetString()));
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

			bool LoadArray(const Value& value, Property* prop, void*& object)
			{
				auto propArray = static_cast<PropertyArray*>(prop);
				//size_t size = propArray->GetArraySize(object);
				void* data = propArray->GetData(object);

				if (value.IsArray())
				{
					auto arrayJson =  value.GetArray();
					propArray->SetSize(arrayJson.Size(),object);
					for (int i = 0;i< arrayJson.Size();i++)
					{
						void* elementPtr = static_cast<char*>(data) + i * propArray->inner->GetElementSize(); // オフセット計算
						if (propArray->inner->GetKind() == PropertyKind::Class)
						{
							LoadClass(arrayJson[i], static_cast<PropertyClass*>(propArray->inner)->GetPropertyClass(), elementPtr);
						}
						else if (propArray->inner->GetKind() == PropertyKind::Object)
						{
				
							LoadObject(arrayJson[i], elementPtr);
						}
					}
				}
				return true;
			}

			bool LoadObject(const Value& reader, void*& obj)
			{
				//=============================================================================================
				// 初期化
				//=============================================================================================
				Class* DerivedClass = nullptr;
				if (!obj)//ポリモーフィズム用の対象がnullptrの場合
				{
					auto objectPtr = reinterpret_cast<HMObject*>(obj);
					auto PolymorphicType = reader.FindMember(TSTR("type"));
					DerivedClass = ClassBuilder::GetClassByname(PolymorphicType->value.GetString());
					obj = DerivedClass->Create();
				}
				else//既にポリモーフィズムのデータが出来上がっている時
				{
					DerivedClass = reinterpret_cast<HMObject*>(obj)->GetClass();
				}

				//=============================================================================================
				// メンバデータの更新
				//=============================================================================================
				auto memberJsonObject = reader.FindMember(TSTR("members"));
				if (!memberJsonObject->value.IsNull() && reader.MemberEnd() != memberJsonObject)//メンバの数や状況を確認
				{
					const auto& value = memberJsonObject->value.GetObject();
					for (auto& member : DerivedClass->GetProperties())
					{
						auto jsonMember = value.FindMember(member->GetPropertyName());
						if (member->GetKind() == PropertyKind::Class)
						{
							auto prop = static_cast<PropertyClass*>(member);
							LoadClass(jsonMember->value, prop->GetPropertyClass(), obj);
						}
						else if (member->GetKind() == PropertyKind::Object)
						{
							void* temp = member->GetPropertyValue(obj);
							LoadObject(jsonMember->value,temp);
						}
						else if (member->GetKind() == PropertyKind::Array)
						{
							LoadArray(jsonMember->value, member, obj);
						}
						else if(member->GetKind() == PropertyKind::UMap)
						{
							LoadMap(jsonMember->value,member,obj);
						}
						else
						{
							LoadNumeric(jsonMember->value, member, obj);
						}
					}
				}
				auto baseIt = reader.FindMember(TSTR("base"));
				if (baseIt != reader.MemberEnd() && !baseIt->value.IsNull()) 
				{
					auto baseObjectJsonStr = baseIt->value.FindMember(DerivedClass->GetBaseClass()->GetName());
					LoadClass(baseObjectJsonStr->value, DerivedClass->GetBaseClass(), obj);
				}
				return true;
			}

			bool LoadClass(const Value& reader, Class* classPtr, void*& obj)
			{
				//=============================================================================================
				// メンバデータの更新
				//=============================================================================================
				auto memberJsonObject = reader.FindMember(TSTR("members"));
				if (!memberJsonObject->value.IsNull() && reader.MemberEnd() != memberJsonObject)//メンバの数や状況を確認
				{
					const auto& value = memberJsonObject->value.GetObject();
					for (auto& member : classPtr->GetProperties())
					{
						auto jsonMember = value.FindMember(member->GetPropertyName());
						if (member->GetKind() == PropertyKind::Class)
						{
							auto prop = static_cast<PropertyClass*>(member);
							LoadClass(jsonMember->value, prop->GetPropertyClass(), obj);
						}
						else if (member->GetKind() == PropertyKind::Object)
						{
							void* temp = member->GetPropertyValue(obj);
							LoadObject(jsonMember->value, temp);
						}
						else if (member->GetKind() == PropertyKind::Array)
						{
							LoadArray(jsonMember->value, member, obj);
						}
						else
						{
							LoadNumeric(jsonMember->value, member, obj);
						}
					}
				}
				auto baseIt = reader.FindMember(TSTR("base"));
				if (baseIt != reader.MemberEnd() && !baseIt->value.IsNull())
				{
					auto baseObjectJsonStr = baseIt->value.FindMember(classPtr->GetBaseClass()->GetName());
					LoadClass(baseObjectJsonStr->value, classPtr->GetBaseClass(), obj);
				}
				return true;
			}

			bool LoadMap(const Value& value, Property* prop, void*& object)
			{
				if (value.IsArray())
				{
					void* Map = prop->GetPropertyValue(object);
					PropertyUMap* umapProperty = dynamic_cast<PropertyUMap*>(prop);

					for (auto& mapmember : value.GetArray())
					{
						if (mapmember.IsObject())
						{
							auto key = mapmember.FindMember(TSTR("Key"));
							auto value = mapmember.FindMember(TSTR("Value"));
							void* pkey = nullptr;
							void* pValue = nullptr;

							auto KeyKind = umapProperty->_pKey->GetKind();
							auto ValueKind = umapProperty->_pValue->GetKind();
							
							if (KeyKind == PropertyKind::Class)
							{
								LoadClass(key->value, static_cast<PropertyClass*>(umapProperty->_pKey)->GetPropertyClass(), pkey);
							}
							else if(KeyKind == PropertyKind::Array)
							{
								LoadArray(key->value,umapProperty->_pKey,pkey);
							}
							else if (KeyKind == PropertyKind::Object)
							{
								LoadObject(key->value,pkey);
							}

							if (ValueKind == PropertyKind::Class)
							{
								LoadClass(value->value, static_cast<PropertyClass*>(umapProperty->_pValue)->GetPropertyClass(), pkey);
							}
							else if (ValueKind == PropertyKind::Array)
							{
								LoadArray(value->value, umapProperty->_pValue, pkey);
							}
							else if (ValueKind == PropertyKind::Object)
							{
								LoadObject(value->value, pkey);
							}
							umapProperty->SetPair(Map, pkey, pValue);
						}
					}
				}
				return false;
			}
		}
	}
}