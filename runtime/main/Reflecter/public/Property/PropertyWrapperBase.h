#pragma once
#include<string>


namespace HARMONY
{
	class Class;
	namespace DETEIL
	{
		class PropertyWrapperBase
		{
		public:
			PropertyWrapperBase(std::string name, Class& holder)
			:_name(name)
			,_class(holder) {};

			const std::string& GetPropertyName() { return _name; }
			
			const Class& GetDeclareClass() { return _class; }

			void 

		private:
			std::string _name;
			Class& _class;
		};
	}
}
