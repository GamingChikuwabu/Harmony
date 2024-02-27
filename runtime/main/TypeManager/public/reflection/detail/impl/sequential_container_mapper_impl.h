#include"sequential_mapper.h"
#pragma once
#include <type_traits>
#include <vector>
#include <list>
#include <deque>
#include <array>
#include <initializer_list>


namespace HARMONY
{
	namespace DETEIL
	{
		/// @brief 可変長配列用のベースクラス
		/// @tparam T コンテナ型
		template<typename T>
		class sequential_container_base_dynamic
		{
			using container_t = T; 
			using value_t = typename T::value_type;
			using itr_t = typename T::iterator; 
			using const_itr_t = typename T::const_iterator;

			static bool is_dynamic()
			{
				return true;
			}

			static value_t& get_data(const itr_t& itr)
			{
				return *itr;
			}

			static const value_t& get_data(const const_itr_t& itr)
			{
				return *itr;
			}

            static itr_t begin(container_t& container)
            {
                return container.begin();
            }

            static const_itr_t begin(const container_t& container)
            {
                return container.begin();
            }

            /////////////////////////////////////////////////////////////////////////////////////

            static itr_t end(container_t& container)
            {
                return container.end();
            }

            static const_itr_t end(const container_t& container)
            {
                return container.end();
            }

            /////////////////////////////////////////////////////////////////////////////////////

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

            static bool set_size(container_t& container, std::size_t size) 
            {
                container.resize(size); 
                return true;
            }

            static itr_t erase(container_t& container, const itr_t& itr) 
            {
                return container.erase(itr); 
            }

            static itr_t erase(container_t& container, const const_itr_t& itr) 
            {
                return container.erase(itr); 
            }

            static itr_t insert(container_t& container, const value_t& value, const itr_t& itr_pos)
            {
                return container.insert(itr_pos, value);
            }

            static itr_t insert(container_t& container, const value_t& value, const const_itr_t& itr_pos)
            {
                return container.insert(itr_pos, value);
            }
		};

        /// @brief ランダムアクセスイテレータ用のクラス vector,dequeなど
        /// @tparam T コンテナ
        template<typename T>
        class sequential_container_base_dynamic_direct_access : public sequential_container_base_dynamic<T> 
        {
            using container_t = T;
            using value_t = typename T::value_type; 

            static value_t& get_value(container_t& container, std::size_t index) 
            {
                return container[index];
            }

            static const value_t& get_value(const container_t& container, std::size_t index) 
            {
                return container[index];
            }
        };

        /// @brief 双方向連結型のコンテナ用 listなど
        /// @tparam T 
        template<typename T>
        struct sequential_container_base_dynamic_itr_access : sequential_container_base_dynamic<T> 
        {
            using container_t = T;
            using value_t = typename T::value_type;

            static value_t& get_value(container_t& container, std::size_t index)
            {
                auto it = container.begin();
                std::advance(it, index);
                return *it;
            }

            static const value_t& get_value(const container_t& container, std::size_t index)
            {
                auto it = container.begin();
                std::advance(it, index);
                return *it;
            }
        };

        /// @brief 固定長配列コンテナ用 arrayなど
        /// @tparam T 
        template<typename T>
        struct sequential_container_base_static
        {
            using container_t = T;
            using value_t = typename T::value_type;
            using itr_t = typename T::iterator;
            using const_itr_t = typename T::const_iterator;

            static bool is_dynamic()
            {
                return false;
            }

            static value_t& get_data(const itr_t& itr)
            {
                return *itr;
            }

            static const value_t& get_data(const const_itr_t& itr)
            {
                return *itr;
            }

            /////////////////////////////////////////////////////////////////////////////////////

            static itr_t begin(container_t& container)
            {
                return container.begin();
            }

            static const_itr_t begin(const container_t& container)
            {
                return container.begin();
            }

            /////////////////////////////////////////////////////////////////////////////////////

            static itr_t end(container_t& container)
            {
                return container.end();
            }

            static const_itr_t end(const container_t& container)
            {
                return container.end();
            }

            /////////////////////////////////////////////////////////////////////////////////////

            static void clear(container_t& container)
            {
            }

            static bool is_empty(const container_t& container)
            {
                return container.empty();
            }

            static std::size_t get_size(const container_t& container)
            {
                return container.size();
            }

            static bool set_size(container_t& container, std::size_t size)
            {
                return false;
            }

            static itr_t erase(container_t& container, const itr_t& itr)
            {
                return end(container);
            }

            static itr_t erase(container_t& container, const const_itr_t& itr)
            {
                return end(container);
            }

            static itr_t insert(container_t& container, const value_t& value, const itr_t& itr_pos)
            {
                return end(container);
            }

            static itr_t insert(container_t& container, const value_t& value, const const_itr_t& itr_pos)
            {
                return end(container);
            }

            static value_t& get_value(container_t& container, std::size_t index)
            {
                return container[index];
            }

            static const value_t& get_value(const container_t& container, std::size_t index)
            {
                return container[index];
            }
        };
	}
    template<typename T, std::size_t N> 
    struct sequential_container_mapper<T[N]>
    {
        using container_t = T[N];
        using value_t = std::remove_pointer_t<typename std::decay<T[N]>::type>;
        using itr_t = typename std::decay<T[N]>::type;
        using const_itr_t = typename std::decay<std::add_const_t<T[N]>>::type;

        static bool is_dynamic()
        {
            return false;
        }

        static value_t& get_data(itr_t& itr)
        {
            return *itr;
        }

        static const value_t& get_data(const const_itr_t& itr)
        {
            return *itr;
        }

        /////////////////////////////////////////////////////////////////////////////////////

        static itr_t begin(container_t& container)
        {
            return &container[0];
        }

        static const_itr_t begin(const container_t& container)
        {
            return &container[0];
        }

        /////////////////////////////////////////////////////////////////////////////////////

        static itr_t end(container_t& container)
        {
            return &container[N];
        }

        static const_itr_t end(const container_t& container)
        {
            return &container[N];
        }

        /////////////////////////////////////////////////////////////////////////////////////

        static void clear(container_t& container)
        {
        }

        static bool is_empty(const container_t& container)
        {
            return false;
        }

        static std::size_t get_size(const container_t& container)
        {
            return N;
        }

        static bool set_size(container_t& container, std::size_t size)
        {
            return false;
        }

        static itr_t erase(container_t& container, const itr_t& itr)
        {
            return end(container);
        }

        static itr_t insert(container_t& container, const value_t& value, const itr_t& itr_pos)
        {
            return end(container);
        }

        static value_t& get_value(container_t& container, std::size_t index)
        {
            return container[index];
        }

        static const value_t& get_value(const container_t& container, std::size_t index)
        {
            return container[index];
        }
    };

    template<typename T>
    struct sequential_container_mapper<std::initializer_list<T>>
    {
        using container_t = std::initializer_list<T>;
        using value_t = typename std::initializer_list<T>::value_type;
        using itr_t = typename std::initializer_list<T>::iterator;
        using const_itr_t = typename std::initializer_list<T>::const_iterator;

        static bool is_dynamic()
        {
            return false;
        }

        static value_t& get_data(itr_t& itr)
        {
            return *itr;
        }

        static const value_t& get_data(const const_itr_t& itr)
        {
            return *itr;
        }

        /////////////////////////////////////////////////////////////////////////////////////

        static itr_t begin(container_t& container)
        {
            return container.begin();
        }

        static const_itr_t begin(const container_t& container)
        {
            return container.end();
        }

        /////////////////////////////////////////////////////////////////////////////////////

        static itr_t end(container_t& container)
        {
            return container.end();
        }

        static const_itr_t end(const container_t& container)
        {
            return container.end();
        }

        /////////////////////////////////////////////////////////////////////////////////////

        static void clear(container_t& container)
        {
        }

        static bool is_empty(const container_t& container)
        {
            return false;
        }

        static std::size_t get_size(const container_t& container)
        {
            return container.size();
        }

        static bool set_size(container_t& container, std::size_t size)
        {
            return false;
        }

        static itr_t erase(container_t& container, const itr_t& itr)
        {
            return end(container);
        }

        static itr_t insert(container_t& container, const value_t& value, const itr_t& itr_pos)
        {
            return end(container);
        }

        static const value_t& get_value(container_t& container, std::size_t index)
        {
            auto it = container.begin();
            std::advance(it, index);
            return *it;
        }

        static const value_t& get_value(const container_t& container, std::size_t index)
        {
            auto it = container.begin();
            std::advance(it, index);
            return *it;
        }
    };

    template<>
    struct sequential_container_mapper<std::vector<bool>>
    {
        using container_t = std::vector<bool>;
        using value_t = std::vector<bool>::value_type;
        using itr_t = std::vector<bool>::iterator;
        using const_itr_t = std::vector<bool>::const_iterator;

        static bool is_dynamic()
        {
            return true;
        }

        static value_t get_data(const itr_t& itr)
        {
            return *itr;
        }

        static value_t get_data(const const_itr_t& itr)
        {
            return *itr;
        }

        /////////////////////////////////////////////////////////////////////////////////////

        static itr_t begin(container_t& container)
        {
            return container.begin();
        }

        static const_itr_t begin(const container_t& container)
        {
            return container.begin();
        }

        /////////////////////////////////////////////////////////////////////////////////////

        static itr_t end(container_t& container)
        {
            return container.end();
        }

        static const_itr_t end(const container_t& container)
        {
            return container.end();
        }

        /////////////////////////////////////////////////////////////////////////////////////

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

        static bool set_size(container_t& container, std::size_t size)
        {
            container.resize(size);
            return true;
        }

        static itr_t erase(container_t& container, const itr_t& itr)
        {
            return container.erase(itr);
        }

        static itr_t erase(container_t& container, const const_itr_t& itr)
        {
            return container.erase(itr);
        }

        static itr_t insert(container_t& container, const value_t& value, const itr_t& itr_pos)
        {
            return container.insert(itr_pos, value);
        }

        static itr_t insert(container_t& container, const value_t& value, const const_itr_t& itr_pos)
        {
            return container.insert(itr_pos, value);
        }

        static std::vector<bool>::reference get_value(container_t& container, std::size_t index)
        {
            return container[index];
        }

        static std::vector<bool>::const_reference get_value(const container_t& container, std::size_t index)
        {
            return container[index];
        }
    };

    template<typename T>
    struct sequential_container_mapper<std::vector<T>> : DETEIL::sequential_container_base_dynamic_direct_access<std::vector<T>> {};
    template<typename T>
    struct sequential_container_mapper<std::list<T>> : DETEIL::sequential_container_base_dynamic_itr_access<std::list<T>> {};
    template<typename T>
    struct sequential_container_mapper<std::deque<T>> : DETEIL::sequential_container_base_dynamic_direct_access<std::deque<T>> {};
    template<typename T, std::size_t N>
    struct sequential_container_mapper<std::array<T, N>> : DETEIL::sequential_container_base_static<std::array<T, N>> {};

    template<   typename T, 
                typename ConstType,
                typename Tp = std::conditional_t<std::is_const<ConstType>::value,
                typename sequential_container_mapper<T>::const_itr_t,
                typename sequential_container_mapper<T>::itr_t>>
    struct sequential_constainer_wrapper_mapper
    {
        using base_class = sequential_container_mapper<T>;
        using value_t = typename base_class::value_t;
        using itr_t = typename base_class::itr_t;
        using const_itr_t = typename base_class::const_itr_t;

        static ConstType& get_container(void* container)
        {
            return *reinterpret_cast<ConstType*>(container);
        }


    };
}