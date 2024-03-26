#pragma once
#include"HMString.h"

namespace HARMONY
{
	enum class PropertyKind
	{
		Int32,
		Int64,
		Float,
		Double,
		String,
		Array,
		Map,
		Class,
		Object
	};

	class REFLECTION_API Property
	{
	public:
		Property(const TCHAR* name,void* accessor,size_t size);
		~Property() = default;
		virtual PropertyKind GetKind() { return PropertyKind(); }
		const TCHAR* GetName();
		template<typename A>
		A GetAccessorPtr();
		size_t GetSize() { return _size; };
	private:
		const TCHAR* _name;
		void* accessor;
		size_t _size;
	};
}

#include"detail/Property_impl.inl"