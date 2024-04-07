#pragma once
#include"Macro/ObjectMacro.h"
#include"Float3.generate.h"

namespace HARMONY
{
    namespace MATH
    {
        HMCLASS()
        struct UTILITY_API Float3
        {
            HM_CLASS_BODY()

            HMPROPERTY()
            float x;
            HMPROPERTY()
            float y;
            HMPROPERTY()
            float z;
            Float3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f):x(_x),y(_y),z(_z) {};
        };
    }
}