#include"associative_mapper.h"
#pragma once
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>

namespace HARMONY
{
	template <typename T>
	struct associative_container_value_t
	{
		template <typename U> static typename U::mapped_type check(typename U::mapped_type*);
		template <typename U> static void check(...);

		using type = decltype(check<T>(nullptr));
	};

	/// @brief 連想配列コンテナの基底クラス
	/// @tparam T 連想配列コンテナ型
	template<typename T>
	struct associative_container_base
	{
		using container_t = T;//コンテナの型
		using key_t = typename T::key_type;//コンテナのkeyタイプ
        using value_t = typename associative_container_value_t<T>::type;//set,unordersetの場合void
        using itr_t = typename T::iterator;
        using const_itr_t = typename T::const_iterator;

        static const key_t& get_key(const const_itr_t& itr)
        {
            return itr->first;
        }

        static itr_t begin(container_t& container)
        {
            return container.begin();
        }

        static const_itr_t begin(const container_t& container)
        {
            return container.begin();
        }

        static itr_t end(container_t& container)
        {
            return container.end();
        }

        static const_itr_t end(const container_t& container)
        {
            return container.end();
        }

        static itr_t find(container_t& container, const key_t& key)
        {
            return container.find(key);
        }

        static const_itr_t find(const container_t& container, const key_t& key)
        {
            return container.find(key);
        }

        static std::pair<itr_t, itr_t> equal_range(container_t& container, const key_t& key)
        {
            return container.equal_range(key);
        }

        static std::pair<const_itr_t, const_itr_t> equal_range(const container_t& container, const key_t& key) 
        {
            return container.equal_range(key);
        }

        static void clear(container_t& container) 
        {
            container.clear(); 
        }

        static bool is_empty(const container_t& container)
        {
            return container.empty();
        }

        static std::size_t get_size(const container_t& container)
        {
            return container.size();
        }

        static std::size_t erase(container_t& container, const key_t& key)
        {
            return container.erase(key);
        }

        static std::pair<itr_t, bool> insert_key(container_t& container, const key_t& key)
        {
            return { container.end(), false };
        }
	}


}