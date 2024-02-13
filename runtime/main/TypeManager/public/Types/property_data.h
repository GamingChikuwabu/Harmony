#pragma once
#include"Archive/access.h"
#include<string>
#include<typeinfo>
#include<variant>
#include<functional>
#include<any>
#include"Types/type.h"


namespace HARMONY
{
	namespace DETAIL
	{
		struct Property_Data
		{
			std::string				_propertyName;	//このプロパティの名前
			PROPERTY_ACCESS_LEVEL	_accessLevel;	//このプロパティのアクセスレベル
			std::size_t				_offset;		//このプロパティのオフセット
			std::function<void(void*,std::any)>			_castFunc;
			template<typename PropertyType>
			void init(std::string name, PROPERTY_ACCESS_LEVEL acc, std::size_t offset)
			{
				_propertyName = name;
				_accessLevel = acc;
				_offset = offset;
				// _castFuncにラムダ式を設定
				_castFunc = [this](void* classInstance, std::any value) { 
					// std::any から PropertyType へのキャストを試みる
					if (value.type() == typeid(PropertyType)) { 
						// キャスト成功
						PropertyType* propertyAddr = reinterpret_cast<PropertyType*>( 
							reinterpret_cast<char*>(classInstance) + this->_offset); 
						*propertyAddr = std::any_cast<PropertyType>(value); 
					}
					else {
						// キャスト失敗または型不一致
						std::cerr << "Type mismatch or cannot cast std::any to PropertyType" << std::endl;
					}
					};
			}
		};
	}
}