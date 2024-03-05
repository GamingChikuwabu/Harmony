#pragma once
#include"generatemacro.h"
#include<string>

namespace HARMONY
{
	HMCLASS()
	class HMObject
	{
		HM_CLASS_BODY()
	public:
		HMObject() {};
		virtual ~HMObject() = default;
	protected:
		HMPROPERTY()
		std::string _guid;
	};
}