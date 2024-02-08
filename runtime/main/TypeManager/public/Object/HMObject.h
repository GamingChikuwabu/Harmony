#pragma once
#include"generatemacro.h"
#include"ArchiveBace.h"
#include<string>
#include"HMObject.generate.h"

namespace HARMONY
{
	HMCLASS()
	class HMObject
	{
		HM_CLASS_ACCESS_FRIEND()
	public:
		HMObject() {};
		virtual ~HMObject() = default;
	protected:
		HMPROPERTY()
		std::string _guid;
		int* counter;
	};
}