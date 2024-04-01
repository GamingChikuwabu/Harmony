#pragma once
#include"HMString.h"
#include"PropertyKind.h"

namespace HARMONY
{
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