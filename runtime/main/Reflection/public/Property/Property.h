#pragma once
#include"HMString.h"

namespace HARMONY
{
	enum class PropertyKind
	{
		Int,
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
		Property(const TCHAR* name,void* accessor);
		~Property();
		virtual PropertyKind GetKind() { return PropertyKind(); }
		const TCHAR* GetName();
		template<typename A>
		A GetAccessorPtr();
	private:
		const TCHAR* _name;
		void* accessor;
	};
}

#include"detail/Property_impl.inl"