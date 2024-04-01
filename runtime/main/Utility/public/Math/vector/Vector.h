#pragma once
#include"..\PlatformSimdchacker.h"
#include"..\..\..\..\Object\public\Object\Macro\ObjectMacro.h"
#include"..\..\..\generate\Vector.generate.h"

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
					float z;
				};
				__m128 simd;
			};
			Vector3f(float _x,float _y,float z):x(_x), y(_y), z(z){};
		};
	}
}