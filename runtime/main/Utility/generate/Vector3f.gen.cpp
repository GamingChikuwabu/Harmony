#include"Vector3f.h"
#include"Class/ClassBuilder.h"
#include"Class/deteil/ClassData.h"
#include"Macro/GenerateMacro.h"
#include"Refrection.hpp"
static void G_AUTO_REGISTER_FUNCTION_Vector3f()
{
    HARMONY::ClassBuilder::Registration(TEXT("Vector3f"), &HARMONY::MATH::Vector3f::StaticGetClass);
}
struct AUTO_REGISTER_STRUCTURE_Vector3f
{
   AUTO_REGISTER_STRUCTURE_Vector3f()
    {
       G_AUTO_REGISTER_FUNCTION_Vector3f();
    }
};
struct AUTO_REGISTER_STRUCTURE_Vector3f ARS={};
namespace HARMONY{
namespace MATH{
   struct G_Class_Declaration_Field_Vector3f
    {
       const static inline HMArray<Property*> _propertyField = 
        {
           HM_ADD_PROPERTY_FLOAT(Vector3f,x),
           HM_ADD_PROPERTY_FLOAT(Vector3f,y),
           HM_ADD_PROPERTY_FLOAT(Vector3f,z),
        };
    };
   inline Class* Vector3f::G_GetClassDataVector3f()
    {
       HM_CLASS_CREATE(Vector3f,nullptr)
return _class;

    }
}
}
