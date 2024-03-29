#pragma once
#include"Property.h"
#include"Property/ScriptArray.h"
#include <functional> 

namespace HARMONY
{
	class REFLECTION_API PropertyArray : public Property
	{
	public:
		template<typename C,typename T>
		PropertyArray(const TCHAR* name, HARMONY::HMArray<T> C::* memberptr);
		ScriptArray GetScriptArray(void* classInstance);
		inline PropertyKind GetKind()override;
		void operator()(const TCHAR* name,size_t);//インナータイプを登録するための
	private:
		std::function<HARMONY::ScriptArray(void*)> GetScriptArrayFunc;
		Property* inner;
	};
}

#include"detail/PropertyArray_impl.inl"