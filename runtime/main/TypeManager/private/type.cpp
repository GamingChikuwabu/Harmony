#include"Types/type.h"
#include"gc.h"
#include"type_data.h"

namespace HARMONY
{
	Type::Type(const std::type_info& info, const std::string& name, size_t size)
		:_info(typeid(info)), _name(name), _size(size)
	{
		// このオブジェクトを_typeListに登録
		_typeMap[_info] = this;
	}

	const std::string& Type::GetName() const
	{
		// TODO: return ステートメントをここに挿入します
	}

	size_t Type::GetSize() const
	{
		return size_t();
	}

	bool Type::operator==(const Type& other) const
	{
		return (_info == other._info) &&
			(_name == other._name) &&
			(_size == other._size);
	}

	bool Type::operator!=(const Type& other) const
	{
		return !(*this == other);
	}

	Type* Type::FindByName(const std::string& name)
	{
		for (auto type_bace : _typeMap)
		{
			if (name == type_bace.second->_name)
			{
				return type_bace.second;
			}
		}
		return nullptr;
	}

	bool Type::IsArithmetic()
	{
		if (_typeCategory == TYPE_CATEGORY::TYPE_ARITHMETIC)
		{
			return true;
		}
		return false;
	}

	bool Type::IsEnum()
	{
		if (_typeCategory == TYPE_CATEGORY::TYPE_ENUM)
		{
			return true;
		}
		return false;
	}

	bool Type::IsArray()
	{
		if (_typeCategory == TYPE_CATEGORY::TYPE_ARRAY)
		{
			return true;
		}
		return false;
	}

	bool Type::IsClass()
	{
		if (_typeCategory == TYPE_CATEGORY::TYPE_OBJECT)
		{
			return true;
		}
		return false;
	}

	void* Type::CreateInstanceByType()
	{
		return (void*)GC_MALLOC(_size); 
	}
}