#pragma once
#include<string>
#include"variant.h"

namespace HARMONY
{
	struct TYPEMANAGER_API NVP {
		std::string name; // 名前（キー）
		variant value;          // 値
	};
	// NVPを作成するヘルパー関数
	TYPEMANAGER_API NVP make_nvp(const std::string& name, variant value);

#define MAKE_NVP(value) make_nvp(#value,value);

}