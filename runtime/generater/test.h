#pragma once
#include<string>
#include"ObjectMacro.h"
#include"HMString.h"
#include"gc/gc_cpp.h"
#include"Refrection.hpp"
#include"Utility.hpp"
#include"HMObject.generate.h"

namespace HARMONY
{
	namespace MATH
	{
		HMCLASS()
		struct UTILITY_API Vector3f
		{
			HM_CLASS_BODY()
			union 
			{
				struct 
				{
					HMPROPERTY()
					float x;
					HMPROPERTY()
					float y;
					HMPROPERTY()
					float* z;
				};
				__m128 simd;
			};
			Vector3f(float _x,float _y,float z):x(_x), y(_y), z(_z){};
		};
	}
}