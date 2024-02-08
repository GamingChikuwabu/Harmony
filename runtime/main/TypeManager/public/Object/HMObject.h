#pragma once
#include"generatemacro.h"
#include<string>

namespace HARMONY
{
	HMCLASS()
	class HMObject
	{
		HM_CLASS_ACCESS_FRIEND()
	public:
		HMObject() {};
		virtual ~HMObject() = default;
		virtual void Serialize(class HMArchive arcive);
	protected:
		HMPROPERTY()
		std::string _guid;
	};
}