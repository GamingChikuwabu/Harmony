#include "Registration.h"
#pragma once
namespace HARMONY
{
	template<typename Class_Type>
	Registration::class_<Class_Type>::class_(std::string name)
	{

	}

	template<typename Class_Type>
	template<typename A>
	inline Registration::class_<Class_Type>& Registration::class_<Class_Type>::property(std::string name, A Class_Type::* member)
	{
		return *this;
	}

	template<typename Class_Type>
	template<typename Getter, typename Setter>
	inline Registration::class_<Class_Type>& Registration::class_<Class_Type>::property(std::string name, Getter getter, Setter setter)
	{
		return *this;
	}

	template<typename Class_Type>
	template<typename F>
	inline Registration::class_<Class_Type>& Registration::class_<Class_Type>::method(std::string name, F Class_Type::* memberFPtr)
	{
		return *this;
	}
}