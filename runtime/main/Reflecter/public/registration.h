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
		};
	};
}

#include"inl/Registration.inl"