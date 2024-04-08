#include"Serializer/SerializerMembers/OjsonArchiver.h"

namespace HARMONY
{
	namespace SERIALIZER
	{
		OJsonArchiver::OJsonArchiver()
		{

		}

		OJsonArchiver::~OJsonArchiver()
		{

		}

		namespace DETAIL
		{
			bool SaveBool(Writer& value, Property* prop, void* object)
			{
				if (!prop || !object) return false;
				bool temp = static_cast<PropertyBool*>(prop)->GetBool(object);
				value.Bool(temp);
				return true;
			}

			bool SaveInt(Writer& value, Property* prop, void* object)
			{
				if (!prop || !object) return false;
				int32_t temp = static_cast<PropertyInt32*>(prop)->GetInt32(object);
				value.Int(temp);
				return true;
			}

			bool SaveInt64(Writer& value, Property* prop, void* object)
			{
				if (!prop || !object) return false;
				int64_t temp = static_cast<PropertyInt64*>(prop)->GetInt64(object);
				value.Int64(temp);
				return true;
			}

			bool SaveFloat(Writer& value, Property* prop, void* object)
			{
				if (!prop || !object) return false;
				float temp = static_cast<PropertyFloat*>(prop)->GetFloat(object);
				value.Double(temp);
				return true;
			}

			bool SaveDouble(Writer& value, Property* prop, void* object)
			{
				if (!prop || !object) return false;
				double temp = static_cast<PropertyDouble*>(prop)->GetDouble(object);
				value.Double(temp);
				return true;
			}

			bool SaveString(Writer& value, Property* prop, void* object)
			{
				if (!prop || !object) return false;
				HMString temp = static_cast<PropertyString*>(prop)->GetString(object);
				TCHAR* m = temp.GetRaw();
				value.String(temp.GetRaw());
				return true;
			}

			bool SaveNumeric(Writer& value, Property* prop, void* object)
			{
				switch (prop->GetKind()) {
				case PropertyKind::Bool: {
					SaveBool(value, prop, object);
					break;
				}
				case PropertyKind::Int32: {
					SaveInt(value, prop, object);
					break;
				}
				case PropertyKind::UInt32: {
					SaveInt(value, prop, object);
					break;
				}
				case PropertyKind::Int64: {
					SaveInt64(value, prop, object);
					break;
				}
				case PropertyKind::Float: {
					SaveFloat(value, prop, object);
					break;
				}
				case PropertyKind::Double: {
					SaveDouble(value, prop, object);
					break;
				}
				case PropertyKind::String: {
					SaveString(value, prop, object);
					break;
				}
				default:
					value.Null();
					break;
				}
				return true;
			}

			bool SaveClass(Writer& value, Property* prop, void* object)
			{
				if (!prop || !object) return false;
				auto* _class = dynamic_cast<PropertyClass*>(prop)->GetPropertyClass();
				SerializeObject(value, _class, object);
			}

			bool SaveMap(Writer& value, Property* prop, void* object)
			{
				if (!prop || !object) return false;
				auto* Mapper = dynamic_cast<PropertyUMap*>(prop);
				void* innerMap = Mapper->GetPropertyValue(object);
				auto pairs = Mapper->GetPair(innerMap);
				value.StartArray();
				for (auto pair : pairs)
				{
					value.StartObject();
					value.Key(TSTR("Key"));
					if (Mapper->_pKey->GetKind() == PropertyKind::Class)
					{
						SaveClass(value, Mapper->_pKey, Mapper->GetKey(pair));
					}
					else if (Mapper->_pKey->GetKind() == PropertyKind::Array)
					{
						SaveArray(value, Mapper->_pKey, Mapper->GetKey(pair));
					}
					else
					{
						SaveNumeric(value, Mapper->_pKey, Mapper->GetKey(pair));
					}
					value.Key(TSTR("Value"));
					if (Mapper->_pValue->GetKind() == PropertyKind::Class)
					{
						SaveClass(value, Mapper->_pValue, Mapper->GetValue(pair));
					}
					else if (Mapper->_pValue->GetKind() == PropertyKind::Array)
					{
						SaveArray(value, Mapper->_pValue, Mapper->GetValue(pair));
					}
					else
					{
						SaveNumeric(value, Mapper->_pValue, Mapper->GetValue(pair));
					}
					value.EndObject();
				}
				value.EndArray();
				return true;
			}

			bool SaveArray(Writer& writer, Property* prop, void* object)
			{
				if (!prop || !object) return false;

				auto propArray = static_cast<PropertyArray*>(prop);
				size_t size = propArray->GetArraySize(object);
				void* data = propArray->GetData(object);

				auto innerProperty = propArray->inner;

				writer.StartArray();

				for (size_t i = 0; i < size; i++) {
					char* elementPtr = static_cast<char*>(data) + i * innerProperty->GetElementSize(); // オフセット計算

					switch (innerProperty->GetKind()) {
					case PropertyKind::Bool: {
						// bool値を取得して書き込む
						bool value = *reinterpret_cast<bool*>(elementPtr);
						writer.Bool(value);
						break;
					}
					case PropertyKind::Int32: {
						// int値を取得して書き込む
						int value = *reinterpret_cast<int*>(elementPtr);
						writer.Int(value);
						break;
					}
					case PropertyKind::Int64: {
						// int64_t値を取得して書き込む
						int64_t value = *reinterpret_cast<int64_t*>(elementPtr);
						writer.Int64(value);
						break;
					}
					case PropertyKind::Float: {
						// float値を取得して書き込む
						float value = *reinterpret_cast<float*>(elementPtr);
						writer.Double(value); // JSONにfloatはないため、doubleとして書き込む
						break;
					}
					case PropertyKind::Double: {
						// double値を取得して書き込む
						double value = *reinterpret_cast<double*>(elementPtr);
						writer.Double(value);
						break;
					}
					case PropertyKind::String: {
						// HMStringからCスタイルの文字列を取得して書き込む
						const HMString* strValue = reinterpret_cast<HMString*>(elementPtr);
						writer.String(strValue->GetRaw());
						break;
					}
					case PropertyKind::Class:
					{
						auto prop = static_cast<PropertyClass*>(innerProperty);
						SerializeObject(writer, prop->GetPropertyClass(), prop->GetPropertyValue(reinterpret_cast<void*>(elementPtr)));
						break;
					}
					default:
						writer.Null();
						break;
					}
				}

				writer.EndArray();
				return true;
			}

			bool SerializeObject(Writer& writer, Class* classPtr, void* obj)
			{
				if (classPtr == nullptr) {
					return true;
				}

				writer.StartObject();
				writer.Key(TSTR("type"));
				writer.String(classPtr->GetName());
				writer.Key(TSTR("members"));
				
				// 現在のクラスのプロパティをシリアライズ
				size_t propertyNum = classPtr->GetProperties().GetSize();
				if (propertyNum == 0)
				{
					writer.Null();
				}
				else
				{
					writer.StartObject();
					for (auto prop : classPtr->GetProperties()) {
						writer.Key(prop->GetPropertyName());
						auto kind = prop->GetKind();
						switch (kind) {
							// プロパティタイプに基づいて適切なシリアライズ関数を呼び出す
						case PropertyKind::Bool:
							DETAIL::SaveBool(writer, prop, obj);
							break;
						case PropertyKind::Int32:
							DETAIL::SaveInt(writer, prop, obj);
							break;
						case PropertyKind::Int64:
							DETAIL::SaveInt64(writer, prop, obj);
							break;
						case PropertyKind::Float:
							DETAIL::SaveFloat(writer, prop, obj);
							break;
						case PropertyKind::Double:
							DETAIL::SaveDouble(writer, prop, obj);
							break;
						case PropertyKind::String:
							DETAIL::SaveString(writer, prop, obj);
							break;
						case PropertyKind::Array:
							SaveArray(writer, prop, obj);
							break;
						case PropertyKind::Class:
							SerializeObject(writer, static_cast<PropertyClass*>(prop)->GetPropertyClass(), static_cast<PropertyClass*>(prop)->GetPropertyValue(obj));
							break;
						case PropertyKind::UMap:
							SaveMap(writer, prop, obj);
							break;
						default:
							writer.Null();
							break;
						}
					}
					writer.EndObject();
				}
				
				writer.Key(TSTR("base"));
				// 基底クラスのプロパティを再帰的にシリアライズ
				if (classPtr->GetBaseClass() != nullptr) {
					writer.StartObject();
					writer.Key(classPtr->GetBaseClass()->GetName());
					SerializeObject(writer, classPtr->GetBaseClass(), obj);
					writer.EndObject();
				}
				else
				{
					writer.Null();
				}
				// クラスのオブジェクトの終了
				writer.EndObject();
			}
		}
	}
}