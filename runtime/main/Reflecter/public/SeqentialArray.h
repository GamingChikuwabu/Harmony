#pragma once
#include<type_traits>
#include<vector>
#include<list>
#include<deque>
#include<array>
#include"Value.h"

namespace HARMONY
{
	template<typename T>
	struct SeqentialArrayMapperWrapper
	{

	};

	template<typename T,typename E = void>
	struct SeqentialArrayMapper:std::false_type
	{
		using isvaild = std::false_type;
	};
	
	template<typename T>
	struct SeqentialArrayDynamicBase
	{
		using Container_t = T;
		using Iterator_t = typename T::iterator;
		using ConstIteretor_t = typename T::const_iterator;
		using value_t = typename T::value_type;

		static bool IsDynamic()
		{
			return true;
		}

		static size_t GetSize(Container_t& container)
		{
			return container.size();
		}

		static bool SetSize(Container_t& container,size_t size)
		{
			container.resize(size);
			return true;
		}

		static value_t GetData(Iterator_t& ite)
		{
			return *ite;
		}

		static const value_t GetData(const ConstIteretor_t& ite)
		{
			return *ite;
		}

		static Iterator_t begin(Container_t& container)
		{
			return container.begin();
		}

		static const ConstIteretor_t begin(const Container_t& container)
		{
			return container.begin();
		}

		static Iterator_t end(Container_t& container)
		{
			return container.end();
		}

		static ConstIteretor_t end(const Container_t& container)
		{
			return container.end();
		}

		static void clear(Container_t& container)
		{
			container.clear();
		}

		static bool IsEmpty(const Container_t& container)
		{
			return container.empty();
		}

		static Iterator_t Erase(Container_t& container, const Iterator_t& itr)
		{
			return container.erase(itr);
		}

		static Iterator_t Erase(Container_t& container, const ConstIteretor_t& itr)
		{
			return container.erase(itr);
		}

		static Iterator_t Insert(Container_t& container, const value_t& value, const Iterator_t& itr_pos)
		{
			return container.insert(itr_pos, value);
		}

		static Iterator_t Insert(Container_t& container, const value_t& value, const ConstIteretor_t& itr_pos)
		{
			return container.insert(itr_pos, value);
		}
	};

	template<typename T>
	struct SeqentialArrayDynamicBaseDirectAccess
	{
		using Container_t = T;
		using value_t = typename T::value_type;

		static value_t& GetValue(Container_t& container,std::size_t index)
		{
			return container[index];
		}

		static const value_t& GetValue(const Container_t& container, std::size_t index)
		{
			return container[index];
		}
	};

	template<typename T>
	struct SeqentialArrayDynamicBaseIteraterAccess
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

	template<typename T>
	struct SeqentialArrayStaticBase
	{
		using Container_t = T;
		using Iterator_t = typename T::iterator;
		using ConstIteretor_t = typename T::const_iterator;
		using value_t = typename T::value_type;

		static bool IsDynamic()
		{
			return false;
		}

		static size_t GetSize(Container_t& container)
		{
			return container.size();
		}

		static bool SetSize(Container_t& container, size_t size)
		{
			return false;
		}

		static value_t GetData(Iterator_t& ite)
		{
			return *ite;
		}

		static const value_t GetData(const ConstIteretor_t& ite)
		{
			return *ite;
		}

		static Iterator_t begin(Container_t& container)
		{
			return container.begin();
		}

		static const ConstIteretor_t begin(const Container_t& container)
		{
			return container.begin();
		}

		static Iterator_t end(Container_t& container)
		{
			return container.end();
		}

		static ConstIteretor_t end(const Container_t& container)
		{
			return container.end();
		}

		static void clear(Container_t& container)
		{
			
		}

		static bool IsEmpty(const Container_t& container)
		{
			return container.empty();
		}

		static Iterator_t Erase(Container_t& container, const Iterator_t& itr)
		{
			return container.erase(itr);
		}

		static Iterator_t Erase(Container_t& container, const ConstIteretor_t& itr)
		{
			return container.erase(itr);
		}

		static Iterator_t Insert(Container_t& container, const value_t& value, const Iterator_t& itr_pos)
		{
			return container.insert(itr_pos, value);
		}

		static Iterator_t Insert(Container_t& container, const value_t& value, const ConstIteretor_t& itr_pos)
		{
			return container.insert(itr_pos, value);
		}
	};
}