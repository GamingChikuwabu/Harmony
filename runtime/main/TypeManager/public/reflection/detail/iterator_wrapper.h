#pragma once
#include"variant.h"
#include <memory>
#include <type_traits>

namespace HARMONY
{
	namespace DETAIL
	{
		using iterator_data = std::aligned_storage<sizeof(double)>::type;

		template<typename T, bool Can_Place = (sizeof(T) <= sizeof(iterator_data)) &&
			(std::alignment_of<T>::value <= std::alignment_of<iterator_data>::value)>
		using can_place_in_iterator_data = std::integral_constant<bool, Can_Place>;

        template<typename Itr>
        struct iterator_wrapper_small
        {
            using type = Itr;
            using iterator = Itr;

            static const Itr& get_iterator(const iterator_data& data)
            {
                return reinterpret_cast<const Itr&>(data);
            }

            static Itr& get_iterator(iterator_data& data)
            {
                return reinterpret_cast<Itr&>(data);
            }

            static void create(iterator_data& itr_tgt, const iterator& itr_src)
            {
                new (&itr_tgt) iterator(itr_src);
            }

            static void create(iterator_data& itr_tgt, const iterator_data& itr_src)
            {
                new (&itr_tgt) iterator(get_iterator(itr_src));
            }

            static void destroy(iterator_data& itr)
            {
                get_iterator(itr).~Itr();
            }
        };

        template<typename Itr>
        struct iterator_wrapper_big
        {
            using type = Itr;
            using iterator = Itr;

            static const Itr& get_iterator(const iterator_data& data)
            {
                return *reinterpret_cast<Itr* const&>(data);
            }

            static Itr& get_iterator(iterator_data& data)
            {
                return *reinterpret_cast<Itr*&>(data);
            }

            static void create(iterator_data& itr_tgt, const iterator& itr_src)
            {
                reinterpret_cast<Itr*&>(itr_tgt) = new iterator(itr_src);
            }

            static void create(iterator_data& itr_tgt, const iterator_data& itr_src)
            {
                reinterpret_cast<Itr*&>(itr_tgt) = new iterator(*reinterpret_cast<Itr* const&>(itr_src));
            }

            static void destroy(iterator_data& itr)
            {
                auto& it = get_iterator(itr);
                delete& it;
            }
        };

        template<typename Itr, typename Tp = std::conditional_t<can_place_in_iterator_data<Itr>::value,
            iterator_wrapper_small<Itr>,
            iterator_wrapper_big<Itr>>>
            struct iterator_wrapper_base : Tp
        {

            static void advance(iterator_data& itr, std::ptrdiff_t idx)
            {
                std::advance(Tp::get_iterator(itr), idx);
            }

            static bool equal(const iterator_data& lhs_itr, const iterator_data& rhs_itr)
            {
                return (Tp::get_iterator(lhs_itr) == Tp::get_iterator(rhs_itr)); 
            }
        };

        template<typename Itr>
        struct iterator_wrapper_associative_container : iterator_wrapper_base<Itr>
        {
            static variant get_key(const iterator_data& itr)
            {
                auto& it = iterator_wrapper_base<Itr>::get_iterator(itr);
                return variant(std::ref(it->first)); 
            }

            static variant get_value(const iterator_data& itr)
            {
                auto& it = iterator_wrapper_base<Itr>::get_iterator(itr);
                return variant(std::ref(it->second)); 
            }
        };
	}
}