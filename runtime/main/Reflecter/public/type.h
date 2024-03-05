#pragma once
#include<string>
#include<typeinfo>

namespace HARMONY
{
	class Type
	{
	public:
		template<typename T>
		Type(std::string name)
		:_name(name),
		_size(sizeof(T)),{}
		virtual ~Type() {};
		inline std::string GetName() { return _name; }
		inline std::size_t GetSize() { return _size; }
	private:
		std::string _name;
		std::size_t _size;
	};
}