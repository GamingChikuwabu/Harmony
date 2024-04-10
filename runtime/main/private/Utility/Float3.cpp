#include"Float3.h"
#include"Reflection.hpp"
#include"Macro/GenerateMacro.h"

namespace HARMONY
{
    namespace MATH
    {
        HM_MANUAL_REGISTER_BASE_CLASS_BODY_PROPERTIES(Float3)
            HM_ADD_PROPERTY_FLOAT(Float3, x),
            HM_ADD_PROPERTY_FLOAT(Float3, y),
            HM_ADD_PROPERTY_FLOAT(Float3, z),
        HM_MANUAL_REGISTER_BASE_CLASS_BODY_PROPERTIES_END(Float3)
    }
}