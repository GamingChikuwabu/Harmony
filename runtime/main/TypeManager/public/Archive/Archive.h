#pragma once
#include<map>
#include<unordered_map>
#include<vector>
#include<list>
#include<string>
#include<fstream>
#include"Archive/namevaluepair.h"
#include"TypeManager.h"
#include"OArchive.h"
#include"IArchive.h"

namespace HARMONY
{
	enum class ArchiveType
	{
		Binary,
		Json,
		XML
	};

	class TYPEMANAGER_API HMArchive
	{
	public:
		/// @brief ファイル出力用コンストラクタ
		/// @param archive_type アーカイブ形式
		/// @param ofs 出力ファイルストリーム型
		HMArchive(ArchiveType archive_type,std::ofstream& ofs);

		/// @brief ファイル入力用コンストラクタ
		/// @param archive_type 入力形式
		/// @param ifs 
		HMArchive(ArchiveType archive_type, std::ifstream& ifs);


		/// @brief デストラクタでもしファイル出力形式で起動していたらファイルに出力する処理をする
		/// @brief デストラクタでもしファイル出力形式で起動していたらファイルに出力する処理をする
		~HMArchive();
		
		/// @brief オブジェクトにデシリアライズする
		/// @tparam T NVPの型
		/// @param value NVP
		/// @return *this
		template<typename T>
		HMArchive& operator>>(NVP<T>& value)
		{
			return *this;
		}

		/// @brief オブジェクトをシリアライズする
		/// @tparam T NVPの型
		/// @param value NVP
		/// @return *this
		template<typename T>
		HMArchive& operator<<(NVP<T>& value)
		{
			_oArchiveBase->SaveValueMain(value);
			return *this;
		}

	private:
		void savefile();
		OArchive* _oArchiveBase;
		IArchive* _iArchiveBase;
	};
}