#pragma once
#include"Property.h"
#include"Property/ScriptArray.h"
#include <functional> 

namespace HARMONY
{
	class Class;
	class REFLECTION_API PropertyArray : public Property
	{
	public:
		template<typename C,typename T>
		PropertyArray(const TCHAR* name, HARMONY::HMArray<T> C::* memberptr);
		ScriptArray GetScriptArray(void* classInstance);
		inline PropertyKind GetKind()override;
		PropertyKind GetInnerKind() { return _innerKind; }
		size_t GetInnerElementSize() { return _innerSize; }
		bool GetInnerIsPointer() { return _innerIsPointer; }
	private:
		std::function<HARMONY::ScriptArray(void*)> GetScriptArrayFunc;
		PropertyKind _innerKind;
		size_t _innerSize;
		const bool _innerIsPointer;//innerがポインタかどうか
	};
}

#include"detail/PropertyArray_impl.inl"