#pragma once
#include<functional>
#include<any>
#include"HMArray.h"

namespace HARMONY
{
	
	class Invoker
	{
	public:
		/// @brief デフォルトコンストラクタを実行する
		/// @return クラスインスタンス
		virtual void* invoke() { return nullptr; }
	};

	template<typename C>
	class InvokerBase : public Invoker
	{
	public:
		InvokerBase();
		void* invoke()override;
	private:
		void* (*_constructFunction)();
	};

	template<typename C,typename ...Args>
	class InvokerWithArgs : public Invoker
	{
	public:
		InvokerWithArgs();
		void* invoke(Args... args);
	private:
		void* (*_constructFunction)(Args...);
	};

	class UTILITY_API Construction
	{
	public:
		Construction();
		virtual void* invoke()const = 0;
	};

	template<typename ...Args>
	class ConstructionBase : public Construction
	{
	public:
		ConstructionBase(Invoker* invorker);
		void* invoke()const override;
		void* invoke(Args... arg);
	private:
		Invoker* _invoker;
	};
}

#include"deteil/Construction_impl.inl"