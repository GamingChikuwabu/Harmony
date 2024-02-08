#pragma once
#include<fstream>
#include"..\Types\type_traits_basic.h"
#include"Types/type.h"
#include"namevaluepair.h"

namespace HARMONY
{
	class TYPEMANAGER_API JsonOArchive
	{
	public:
		/// @brief ファイル出力用のストリームを受け取る受け取らない場合はシリアライズの機能のみ使うことができる
		/// @param ofs 出力ファイルストリーム
		JsonOArchive(std::ofstream& ofs);

		/// @brief 出力ファイルストリームを受け取ったらデストラクタでそのファイルへの出力をする
		~JsonOArchive();

		/// @brief 出力アーカイブ用のオペレータ
		/// @tparam T valueの型
		/// @param nvp 値と名前のペア
		/// @return *this 理由はar & MAKE_NVP() & MAKE_NVP()のようにできるようにするため
		template<typename T>
		JsonOArchive& operator&(const NVP<T>& nvp)
		{
			if constexpr (std::is_class<T>::value)
			{
				PushObjectType();
				archive(*this,nvp.value);
				PopObjectType(nvp.name.c_str());
			}
			else if constexpr(std::is_same<T,std::string>::value)
			{
				SaveValue(nvp.name.c_str(), (std::string)nvp.value);
			}
			else
			{
				if constexpr (std::is_integral<T>::value)
				{
					SaveValue(nvp.name.c_str(), (int)nvp.value);
				}
				else if constexpr(std::is_floating_point<T>::value)
				{
					SaveValue(nvp.name.c_str(), (float)nvp.value);
				}
			}
			return *this;
		}
	private:
		void SaveValue(const char* name, int value);
		void SaveValue(const char* name, float value);
		void SaveValue(const char* name, const std::string& value);
		void PushObjectType();
		void PopObjectType(const char* parent_name);
		struct JsonOArchive_impl* _impl;
		std::ofstream& _ofs;
	};
}