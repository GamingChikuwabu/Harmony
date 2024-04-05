#pragma once
#include"Utility/String/HMString.h"
#include"Utility/Array/HMArray.h"
#include<functional>

namespace HARMONY
{
	struct ClassData;
	class Property;
	class UTILITY_API Class
	{
	public:
		Class(ClassData* data);
		const TCHAR* GetName()const;
		size_t GetElementSize()const;
		const HMArray<Property*>& GetProperties()const;
		void* Create();
		template<typename ...Args>
		void* Create(Args... arg);
		Class* GetBaseClass();
	private:
		ClassData* _data;
	};
}

#include"deteil/Class_impl.inl"