#pragma once
#include"Utility/collections/strings.h"
#include"Utility/collections/containers.h"
#include<inttypes.h>

/// @brief Json操作用のインターフェース
class JsonObject
{
public:
	virtual ~JsonObject() = default;
	virtual JsonObject* GetObject(const HMString& key) const = 0;
	virtual HMArray<JsonObject*> GetArray(const HMString& key) const = 0;
	virtual HMString GetString(const HMString& key) const = 0;
	virtual int32_t GetInt(const HMString& key) const = 0;
	virtual float GetFloat(const HMString& key) const = 0;
	virtual bool GetBool(const HMString& key) const = 0;
	virtual bool IsNull() const = 0;
};