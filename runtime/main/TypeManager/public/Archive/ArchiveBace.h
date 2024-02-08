#pragma once
#include<type_traits>
#include<string>
#include<fstream>
#include"TypeManager.h"


namespace HARMONY
{
	template<typename Archive>
	void archive(Archive& ar, int& obj)
	{
		printf("int");
	};

	template<typename Archive>
	void archive(Archive& ar, float& obj)
	{
		printf("float");
	};
}