#include"Construction.h"
#pragma once

namespace HARMONY
{
	template<typename ...Args>
	inline ConstructionBase<Args...>::ConstructionBase(Invoker* invoker)
	:_invoker(invoker)
	{

	}

	template<typename ...Args>
	inline void* ConstructionBase<Args...>::invoke() const
	{
		return _invoker->invoke();
	}

	template<typename ...Args>
	void* ConstructionBase<Args...>::invoke(Args... arg)
	{
		return _constructFunction(arg);
	}

	template<typename C>
	inline InvokerBase<C>::InvokerBase()
	{
		_constructFunction = []()->void*
			{
				void* ptr = (void*)GC_malloc(sizeof(C));
				new (ptr) C();
				return ptr;
			};
	}

	template<typename C>
	inline void* InvokerBase<C>::invoke()
	{
		return _constructFunction();
	}

	template<typename C, typename ...Args >
	inline InvokerWithArgs<C, Args ...>::InvokerWithArgs()
	{
		_constructFunction = [](Args ...args)->void*
			{
				void* ptr = (void*)GC_malloc(sizeof(C));
				new (ptr) C(args);
				return ptr;
			};
	}

	template<typename C,typename ...Args>
	inline void* InvokerWithArgs<C,Args ...>::invoke(Args ...args)
	{
		return _constructFunction(args);
	}
}