#pragma once
#include<fstream>
#include"..\Types\type_traits_basic.h"
#include"Types/type.h"
#include"namevaluepair.h"

namespace HARMONY
{
	template<typename Archive, typename T>
	void archive(Archive& ar, T& obj)
	{};
	class TYPEMANAGER_API JsonOArcive
	{
	public:
		/// @brief ファイル出力用のストリームを受け取る受け取らない場合はシリアライズの機能のみ使うことができる
		/// @param ofs 出力ファイルストリーム
		JsonOArcive(std::ofstream& ofs);

		/// @brief 出力ファイルストリームを受け取ったらデストラクタでそのファイルへの出力をする
		~JsonOArcive();

		/// @brief 出力アーカイブ用のオペレータ
		/// @tparam T valueの型
		/// @param nvp 値と名前のペア
		/// @return *this 理由はar & MAKE_NVP() & MAKE_NVP()のようにできるようにするため
		template<typename T>
		JsonOArcive& operator&(NVP<T>& nvp)
		{
			TypeBase* tb = TypeBase::FindByType<remove_pointer<T>::type>();
			//archive<JsonOArcive, T>(*this, nvp.value);
			return *this;
		}
	private:
		void SaveValue(TypeBase* tb,const char* name, void* value);
		struct JsonOArchive_impl* _impl;
		std::ofstream& _ofs;
	};
}