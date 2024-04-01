#pragma once
#include"Utility.hpp"
#include<functional>

namespace HARMONY
{
	struct ClassData;
	class Property;
	class REFLECTION_API Class
	{
	public:
		Class(ClassData* data);
		const TCHAR* GetName()const;
		size_t GetElementSize()const;
		const HMArray<Property*>& GetProperties()const;
		void* Create();
		template<typename ...Args>
		void* Create(Args... arg);
	private:
		ClassData* _data;
	};
}

#include"deteil/Class_impl.inl"