#pragma once
#include<memory>
#include<vector>
#include<unordered_map>
#include<string>
#include"Type.h"

namespace HARMONY
{
	class Property;
	class REFLECTER_API Class :public Type
	{
	public:
		~Class();
		static Class& GetClassByName(std::string name);
		Property& GetPropertyByName(std::string name);
		std::vector<Property*> GetProperties();
	private:
		Class(std::string name,std::size_t size);
		static inline std::vector<std::unique_ptr<Class>>	_classes;
		static inline std::unordered_map<std::string, int>  _nameIndexMapper;
		std::vector<int>									_BaseClassIndex;
		std::vector<int>									_DerivedClassIndex;
		std::vector<Property*>                              _properties;
		friend class Registration;
	};
}