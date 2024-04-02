#include"Property/PropertyInt.h"
#pragma once

namespace HARMONY
{
	namespace DETAIL
	{
		template<typename ACC, typename A>
		class PropertyInt32_impl
		{

		};

		template<typename ACC, typename A>
		class PropertyInt_impl
		{

		};

		template<typename C>
		class PropertyInt32_impl<member_object_pointer,int32_t C::*> : public PropertyInt32
		{
			using Access = A(C::*);
		public:
			PropertyInt32_impl(const TCHAR* name, Access acc):_acc,PropertyInt32(name)
			{

			}
			virtual int32_t GetValue(void* holderClass = nullptr)override
			{
				C* class_ = reinterpret_cast<C*>(holderClass);
				return class_->*_acc;
			}
			virtual bool SetValue(int32_t value, void* holderClass = nullptr)override
			{
				C* class_ = reinterpret_cast<C*>(holderClass);
				class_->*_acc = value;
			}
		private:
			Access _acc;
		};

		template<>
		class PropertyInt32_impl<object_pointer,int> : public PropertyInt32
		{
		public:
			PropertyInt32_impl(const TCHAR* name)
			:PropertyInt32(name)
			{

			}
			virtual int32_t GetValue(void* holderClass = nullptr)override
			{
				return *reinterpret_cast<int32_t*>(holderClass);
			}
			virtual bool SetValue(int32_t value, void* holderClass = nullptr)override
			{
			 	int32_t* in = reinterpret_cast<int32_t*>(holderClass);
				in = &value;
			}
		};

		template<typename C>
		class PropertyInt32_impl<member_object_pointer, uint32_t C::*> : public PropertyInt32
		{
			using Access = A(C::*);
		public:
			PropertyInt32_impl(const TCHAR* name, Access acc) :_acc
			{

			}
			virtual uint32_t GetValue(void* holderClass = nullptr)override
			{
				C* class_ = reinterpret_cast<C*>(holderClass);
				return class_->*_acc;
			}
			virtual bool SetValue(uint32_t value, void* holderClass = nullptr)override
			{
				C* class_ = reinterpret_cast<C*>(holderClass);
				class_->*_acc = value;
			}
		private:
			Access _acc;
		};
	}
}