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


            Float3() {};
        };
    }
}