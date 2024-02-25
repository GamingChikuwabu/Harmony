#include"associative_mapper.h"
#pragma once
#include<map>
#include<set>
#include<unordered_map>
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

    /// @brief map型の特殊化用のクラス
    /// @tparam T 連想配列コンテナ型
    template<typename T>
    struct associative_container_map_base : associative_container_base<T>
    {
        using container_t = typename associative_container_base<T>::container_t;
        using key_t = typename associative_container_base<T>::key_t;
        using value_t = typename associative_container_base<T>::value_t;
        using itr_t = typename associative_container_base<T>::itr_t;
        using const_itr_t = typename associative_container_base<T>::const_itr_t;

        static value_t& get_value(itr_t& itr)
        {
            return itr->second;
        }

        static const value_t& get_value(const const_itr_t& itr)
        {
            return itr->second;
        }

        static std::pair<itr_t, bool> insert_key_value(container_t& container, const key_t& key, const value_t& value)
        {
            return container.insert(std::make_pair(key, value));
        }
    };

    /// @brief setなどの特殊化用
    /// @tparam T 連想配列コンテナ型
    template<typename T>
    struct associative_container_key_base : associative_container_base<T>
    {
        using container_t = typename associative_container_base<T>::container_t;
        using key_t = typename T::key_type;
        using value_t = void;
        using itr_t = typename T::iterator;
        using const_itr_t = typename T::const_iterator;

        static const key_t& get_key(const const_itr_t& itr)
        {
            return *itr;
        }

        static std::pair<itr_t, bool> insert_key(container_t& container, const key_t& key)
        {
            return container.insert(key);
        }
    };

    /// @brief mapのマルチバージョン用
    /// @tparam T 
    template<typename T>
    struct associative_container_base_multi : associative_container_base<T>
    {
        using container_t = typename associative_container_base<T>::container_t;
        using key_t = typename T::key_type;
        using value_t = typename T::mapped_type;
        using itr_t = typename T::iterator;
        using const_itr_t = typename T::const_iterator;

        static value_t& get_value(itr_t& itr)
        {
            return itr->second;
        }

        static const value_t& get_value(const const_itr_t& itr)
        {
            return itr->second;
        }

        static std::pair<itr_t, bool> insert_key_value(container_t& container, const key_t& key, const value_t& value)
        {
            return { container.insert(std::make_pair(key, value)), true };
        }
    };

    /// @brief setのマルチバージョン用
    /// @tparam T 
    template<typename T>
    struct associative_container_key_base_multi : associative_container_key_base<T>
    {
        using container_t = typename associative_container_key_base<T>::container_t;
        using key_t = typename T::key_type;
        using itr_t = typename T::iterator;

        static std::pair<itr_t, bool> insert_key(container_t& container, const key_t& key)
        {
            return { container.insert(key), true };
        }
    };

    template<typename K>
    struct associative_container_mapper<std::set<K>> : associative_container_key_base<std::set<K>> {};　　

    //////////////////////////////////////////////////////////////////////////////////////

    template<typename K>
    struct associative_container_mapper<std::multiset<K>> :　associative_container_key_base_multi<std::multiset<K>> {};

    //////////////////////////////////////////////////////////////////////////////////////

    template<typename K, typename T>
    struct associative_container_mapper<std::map<K, T>> : associative_container_map_base<std::map<K, T>> { };　

    //////////////////////////////////////////////////////////////////////////////////////

    template<typename K, typename T>
    struct associative_container_mapper<std::multimap<K, T>> : associative_container_base_multi<std::multimap<K, T>> {};

    //////////////////////////////////////////////////////////////////////////////////////

    template<typename K>
    struct associative_container_mapper<std::unordered_set<K>> : associative_container_key_base<std::unordered_set<K>> {};

    //////////////////////////////////////////////////////////////////////////////////////

    template<typename K, typename T>
    struct associative_container_mapper<std::unordered_map<K, T>> : associative_container_map_base<std::unordered_map<K, T>> {};

    //////////////////////////////////////////////////////////////////////////////////////

    template<typename K>
    struct associative_container_mapper<std::unordered_multiset<K>> : associative_container_key_base_multi<std::unordered_multiset<K>> {};

    //////////////////////////////////////////////////////////////////////////////////////

    template<typename K, typename T>
    struct associative_container_mapper<std::unordered_multimap<K, T>> : associative_container_base_multi<std::unordered_multimap<K, T>> {};
}