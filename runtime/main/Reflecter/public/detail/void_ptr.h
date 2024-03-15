#pragma once

namespace HARMONY
{
	namespace DETAIL
	{
        template<typename T>
        struct get_ptr_impl
        {
            static inline void* get(T& data)
            {
                return const_cast<void*>(reinterpret_cast<const void*>(&data));
            }
        };

        template<typename T>
        struct get_ptr_impl<T*>
        {
            static inline void* get(T* data)
            {
                return get_ptr_impl<T>::get(*data);
            }
        };

        template<>
        struct get_ptr_impl<void*>
        {
            static inline void* get(void* data)
            {
                return data;
            }
        };

        template<>
        struct get_ptr_impl<const void*>
        {
            static inline void* get(const void* data)
            {
                return const_cast<void*>(data);
            }
        };

        template<typename T>
        static inline void* get_void_ptr(T* data)
        {
            return get_ptr_impl<T*>::get(data);
        }

        template<typename T>
        static inline void* get_void_ptr(T& data)
        {
            return get_ptr_impl<T>::get(data);
        }
	}
}
