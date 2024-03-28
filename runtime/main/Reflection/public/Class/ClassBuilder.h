#pragma once
#include"HMString.h"
#include"Array/HMArray.h"
#include"Map/HMUnorderedMap.h"
#include<functional>

namespace HARMONY
{
	class Class;
	class REFLECTION_API ClassBuilder
	{
	public:
		static void Registration(const TCHAR* name, Class* (*classCreateFunc)());
		static Class* GetClassByname(const TCHAR* name);
	private:
		static inline HMUnorderedMap<HMString, Class* (*)()> _classCreatorFunction;
	};
}