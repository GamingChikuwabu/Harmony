#include "Registration.h"
#pragma once
#include"Class.h"
#include"Property/PropertyWrapper.h"
#include"detail/AccessLevel.h"
#include"Property.h"
#include<type_traits>

namespace HARMONY
{
	template<typename Class_Type>
	Registration::class_<Class_Type>::class_(std::string name)
	{
		_class = new Class(name,sizeof(Class_Type));
	}

	template<typename Class_Type>
	Registration::class_<Class_Type>::~class_()
	{
		Class::_classes.push_back(std::unique_ptr<Class>(_class));
	}

	template<typename Class_Type>
	template<typename A>
	inline Registration::class_<Class_Type>& Registration::class_<Class_Type>::property(std::string name, A Class_Type::* member)
	{
		using DefaultGetPoricy = DETAIL::return_as_copy;
		using DefaultSetPoricy = DETAIL::set_value;

		if constexpr (!std::is_pointer_v<A>)
		{
			std::shared_ptr<DETAIL::PropertyWrapperBase> tempWrapper(
				new DETAIL::PropertyWrapper<
				DETAIL::member_object_ptr
				, A Class_Type::*
				, void
				, DETAIL::ACCESSLEVEL::PUBLIC
				, DETAIL::return_as_copy
				, DETAIL::set_value>(name, member)
			);
			_class->_properties.push_back(new Property(tempWrapper));
		}
		else
		{
			DETAIL::PropertyWrapperBase* tempWrapper
				= new DETAIL::PropertyWrapper<
				DETAIL::member_object_ptr
				, A Class_Type::*
				, void
				, DETAIL::ACCESSLEVEL::PUBLIC
				, DETAIL::return_as_ptr
				, DETAIL::set_value>(name, member);
		}
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