#pragma once
#include<string>
#include<typeinfo>

namespace HARMONY
{
	class Type
	{
	public:
		Type(std::string name,size_t size)
		:_name(name),
		_size(size){}
		virtual ~Type() {};
		inline std::string GetName() { return _name; }
		inline std::size_t GetSize() { return _size; }
	private:
		std::string _name;
		std::size_t _size;
	};
}