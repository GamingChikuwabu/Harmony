#include"Float3.h"
#include"Class/ClassBuilder.h"
#include"Class/deteil/ClassData.h"
#include"Macro/GenerateMacro.h"
#include"Refrection.hpp"
static void G_AUTO_REGISTER_FUNCTION_Float3()
{
    HARMONY::ClassBuilder::Registration(TSTR("Float3"), &HARMONY::MATH::Float3::StaticGetClass);
}
struct AUTO_REGISTER_STRUCTURE_Float3
{
   AUTO_REGISTER_STRUCTURE_Float3()
    {
       G_AUTO_REGISTER_FUNCTION_Float3();
    }
};
struct AUTO_REGISTER_STRUCTURE_Float3 ARS={};
namespace HARMONY{
namespace MATH{
   struct G_Class_Declaration_Field_Float3
    {
        static HMArray<Property*>& GetPropertyField() {
            static HMArray<Property*> propertyField = {
           HM_ADD_PROPERTY_FLOAT(Float3,x),
           HM_ADD_PROPERTY_FLOAT(Float3,y),
           HM_ADD_PROPERTY_FLOAT(Float3,z),
        };
return propertyField;
    }
        static HMArray<Construction*>& GetConstraction(){
        static HMArray<Construction*> constructionField = {
           HM_ADD_CONSTRUCTION(Float3),
        };
    return constructionField;
    }
    };
   inline Class* Float3::G_GetClassDataFloat3()
    {
       HM_CLASS_CREATE(Float3,nullptr)
        return _class;

    }
}
}
