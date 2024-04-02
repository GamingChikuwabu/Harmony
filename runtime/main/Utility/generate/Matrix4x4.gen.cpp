#include"Matrix4x4.h"
#include"Class/ClassBuilder.h"
#include"Class/deteil/ClassData.h"
#include"Macro/GenerateMacro.h"
#include"Refrection.hpp"
static void G_AUTO_REGISTER_FUNCTION_Matrix4x4()
{
    HARMONY::ClassBuilder::Registration(TEXT("Matrix4x4"), &HARMONY::MATH::Matrix4x4::StaticGetClass);
}
struct AUTO_REGISTER_STRUCTURE_Matrix4x4
{
   AUTO_REGISTER_STRUCTURE_Matrix4x4()
    {
       G_AUTO_REGISTER_FUNCTION_Matrix4x4();
    }
};
struct AUTO_REGISTER_STRUCTURE_Matrix4x4 ARS={};
namespace HARMONY{
namespace MATH{
   struct G_Class_Declaration_Field_Matrix4x4
    {
       const static inline HMArray<Property*> _propertyField = 
        {
        };
    };
   inline Class* Matrix4x4::G_GetClassDataMatrix4x4()
    {
       HM_CLASS_CREATE(Matrix4x4,nullptr)
return _class;

    }
}
}
