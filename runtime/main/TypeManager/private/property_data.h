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
			std::string									_propertyName;	//このプロパティの名前
			ACCESS_LEVEL								_accessLevel;	//このプロパティのアクセスレベル
			std::function<void(void*,std::any)>			_setFunc;		//このプロパティのセッタ
			std::function<void* (void*)>				_getFunc;		//このプロパティのゲッタ
		};
	}
}