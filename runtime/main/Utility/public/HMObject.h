#pragma once
#include<string>
#include"GenerateMacro.h"

#ifdef _WIN32
#ifdef UTILITY_EXPORTS
#define UTILITY_API  __declspec(dllexport) 
#else
#define UTILITY_API  __declspec(dllimport)
#endif // UTILITY_API
#else
#define UTILITY_API
#endif // WIND32

namespace HARMONY
{
	HMCLASS()
	class UTILITY_API HMObject
	{
		HM_CLASS_BODY()
	public:
		HMObject();
		virtual ~HMObject();
	protected:
		HMPROPERTY()
		std::string _guid = "";
	};
};