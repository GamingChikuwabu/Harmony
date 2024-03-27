#pragma once
#include"Utility.hpp"
#include<functional>

namespace HARMONY
{
	class Property;
	class Construction;
	class REFLECTION_API Class
	{
	public:
		template<class C> 
		Class(const TCHAR* name);
		const HMArray<Property*>& GetProperties()const;
		void* Create();
		template<typename ...Args>
		void* Create(Args... arg);
		static Class* GetClassByName(const TCHAR* name);
	private:
		const TCHAR* _name;
		const size_t _size;

		HMArray<Property*> _property;
		HMArray<Class*> _derivedClass;
		Class* _baseClass;
		Construction* _construction;

		static HMArray<Class*> _allClass;
	};
}

template<typename T>
HARMONY::Class* GetStaticClass() {return nullptr};

#include"deteil/Class_impl.inl"