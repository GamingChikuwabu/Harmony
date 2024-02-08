#pragma once
#include<string>

namespace HARMONY
{
	template<typename T>
	struct NVP {
		std::string name; // 名前（キー）
		T value;          // 値
	};

	// NVPを作成するヘルパー関数
	template<typename T>
	NVP<T> make_nvp(const std::string& name, const T& value) {
		return { name, value };
	}

#define MAKE_NVP(value) make_nvp(#value,value);

}