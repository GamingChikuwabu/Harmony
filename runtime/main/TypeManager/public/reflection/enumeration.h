#pragma once
#include<memory>
#include<string>

namespace HARMONY
{
	namespace DETAIL
	{
		struct enumeration_data;
	}
	class type;
	class enumeration
	{
	public:
		/// @brief コピーコンストラクタ
		/// @param value 
		enumeration(const enumeration& value);
		/// @brief moveコンストラクタ
		/// @param value 
		enumeration(const enumeration&& value);
		/// @brief このenumのtype型
		/// @return type
		type GetType()const noexcept;
		/// @brief このenumの要素数を取得する
		/// @return 要素の数
		std::size_t GetCount()const noexcept;
		/// @brief enumの名前からその数値を取り出す関数
		/// @param name 要素の名前
		/// @return 数値
		std::size_t NameToValue(std::string name)const noexcept;
		/// @brief 数値から要素名を検索する関数
		/// @param value 数値
		/// @return 要素の名前
		std::string ValueToString(std::size_t value)const noexcept;
		/// @brief このEnumの型名
		/// @return 型名
		std::string GetName()const noexcept;
	private:
		enumeration(); 
		enumeration(DETAIL::enumeration_data* data);
		std::unique_ptr<DETAIL::enumeration_data> _data;
	};
}