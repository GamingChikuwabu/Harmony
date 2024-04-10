#pragma once
#include"Macro/ObjectMacro.h"
#include"Macro/ManualRegisterMacro.h"


namespace HARMONY
{
    class Class;
    namespace MATH
    {
        HMCLASS()
        struct UTILITY_API Float3
        {
            HM_MANUAL_REGISTER_BASE_CLASS_BODY(Float3)

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