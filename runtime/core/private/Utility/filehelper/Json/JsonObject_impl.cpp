#include"JsonObject_impl.h"
#include"Utility/filehelper/Json/JsonHelper.h"
#include"gc.h"
#include<new>

JsonObject_impl::JsonObject_impl(const Value& value):_value(value)
{

}

JsonObject_impl::~JsonObject_impl()
{

}

JsonObject* JsonObject_impl::GetObject(const HMString& key)const
{
	if (_value.IsObject())
	{
		if (_value.HasMember(key.c_str()))
		{
			const Value& value = _value.FindMember(key.c_str())->value;
			return new (GC_NEW(JsonObject_impl)) JsonObject_impl(value);
		}
	}
	return nullptr;
}

HMArray<JsonObject*> JsonObject_impl::GetArray(const HMString& key)const
{
	if (_value.IsArray())
	{
		HMArray<JsonObject*> array;
		const Value& value = _value.FindMember(key.c_str())->value;
		for (auto& v : value.GetArray())
		{
			array.push_back(new (GC_NEW(JsonObject_impl)) JsonObject_impl(v));
		}
		return array;
	}
	return HMArray<JsonObject*>();
}

HMString JsonObject_impl::GetString(const HMString& key)const
{
	if (_value.HasMember(key.c_str()))
	{
		auto& member = _value.FindMember(key.c_str())->value;
		if (member.IsString())
		{
			return HMString(member.GetString());
		}
	
	}
	return HMString();
}

int32_t JsonObject_impl::GetInt(const HMString& key)const
{
	if (_value.HasMember(key.c_str()))
	{
		auto& member = _value.FindMember(key.c_str())->value;
		if (member.IsInt())
		{
			return member.GetInt();
		}
	}
	return 0;
}

float JsonObject_impl::GetFloat(const HMString& key)const
{
	if (_value.HasMember(key.c_str()))
	{
		auto& member = _value.FindMember(key.c_str())->value;
		if (member.IsFloat())
		{
			return member.GetFloat();
		}
	}
	return 0.0f;
}

bool JsonObject_impl::GetBool(const HMString& key)const
{
	if (_value.HasMember(key.c_str()))
	{
		auto& member = _value.FindMember(key.c_str())->value;
		if (member.IsBool())
		{
			return member.GetBool();
		}
	}
	return false;
}

bool JsonObject_impl::IsNull() const
{
	if (_value.IsNull())
	{
		return true;
	}
	return false;
}