#pragma once
#include<string>

namespace HARMONY
{
	class Registration
	{
	public:
		template<typename Class_Type>
		class class_
		{
		public:
			class_(std::string name);
			~class_();
			template<typename A>
			class_& property(std::string name, A Class_Type::* member);
			template<typename Getter,typename Setter>
			class_& property(std::string name,Getter getter,Setter setter);
			template<typename F>
			class_& method(std::string name,F Class_Type::* memberFPtr);
		};
	};
}

#include"inl/Registration.inl"