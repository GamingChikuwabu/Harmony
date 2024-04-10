#include"Quaternion.h"
#include"Reflection.hpp"
#include"Macro/GenerateMacro.h"

namespace HARMONY
{
    namespace MATH
    {
        HM_MANUAL_REGISTER_BASE_CLASS_BODY_PROPERTIES(Quaternion)
            HM_ADD_PROPERTY_FLOAT(Quaternion, x),
            HM_ADD_PROPERTY_FLOAT(Quaternion, y),
            HM_ADD_PROPERTY_FLOAT(Quaternion, z),
            HM_ADD_PROPERTY_FLOAT(Quaternion, w),
        HM_MANUAL_REGISTER_BASE_CLASS_BODY_PROPERTIES_END(Quaternion)
    }
}
