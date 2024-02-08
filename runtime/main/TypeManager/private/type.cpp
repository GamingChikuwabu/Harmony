#include"Types/type.h"
#include"gc.h"

namespace HARMONY
{
	TypeBase::TypeBase(const std::type_info& info, const std::string& name, size_t size)
		:_info(typeid(info)), _name(name), _size(size)
	{
		// このオブジェクトを_typeListに登録
		_typeMap[_info] = this;
	}
	
	bool TypeBase::IsArithmetic()
	{
		if (_typeCategory == TYPE_CATEGORY::TYPE_ARITHMETIC)
		{
			return true;
		}
		return false;
	}

	bool TypeBase::IsEnum()
	{
		if (_typeCategory == TYPE_CATEGORY::TYPE_ENUM)
		{
			return true;
		}
		return false;
	}

	bool TypeBase::IsArray()
	{
		if (_typeCategory == TYPE_CATEGORY::TYPE_ARRAY)
		{
			return true;
		}
		return false;
	}

	bool TypeBase::IsClass()
	{
		if (_typeCategory == TYPE_CATEGORY::TYPE_OBJECT)
		{
			return true;
		}
		return false;
	}

	void* TypeBase::CreateInstanceByType()
	{
		return (void*)GC_MALLOC(_size); 
	}
}