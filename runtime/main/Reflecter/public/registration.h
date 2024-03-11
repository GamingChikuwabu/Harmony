#pragma once
#include<string>
#include<memory>

namespace HARMONY
{
	class Class;
	class REFLECTER_API Registration
	{
	public:
		template<typename Class_Type>
		class REFLECTER_API class_
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
		private:
			Class* _class;
		};
	};
}

#include"inl/Registration.inl"