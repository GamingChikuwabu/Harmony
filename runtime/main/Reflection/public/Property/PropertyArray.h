#pragma once
#include"Property.h"
#include"HMArray.h"

namespace HARMONY
{
	class PropertyArray : public Property
	{
	public:
		template<typename C,typename T>
		PropertyArray(const TCHAR* name, HARMONY::HMArray<T> C::* memberptr);
		template<typename C>
		void* GetValue(C* instane);
		template<typename C>
		bool SetValue(C* instance, void* value);
		inline PropertyKind GetKind()override;
	private:
		void* ArrayAccessor;
	};
}

#include"detail/PropertyArray_impl.inl"