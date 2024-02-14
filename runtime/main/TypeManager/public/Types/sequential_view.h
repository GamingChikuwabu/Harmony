#pragma once
#include <concepts>
#include<iterator>
#include<type_traits>

namespace HARMONY
{
	// コンテナが持つべき特性を定義するコンセプト
	template<typename T>
	concept Sequential_container = requires(T a, typename T::value_type value) {
		{ a.size() } -> std::convertible_to<size_t>;
		{ a.push_back(value) };
			requires std::input_iterator<typename T::iterator>; 
			requires std::input_iterator<typename T::const_iterator>;
	};

	/// @brief vectorや,listなどのコンテナ用の抽象クラス
	class Sequential_view
	{
	public:
		virtual bool is_empty() const noexcept = 0;
		virtual bool is_dynamic() const noexcept = 0;
		virtual size_t get_rank() const noexcept = 0;
		virtual size_t get_container_size() const noexcept = 0;
		virtual 
	};
}