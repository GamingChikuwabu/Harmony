#include"Transform.h"
#include"Class/ClassBuilder.h"
#include"Class/deteil/ClassData.h"
#include"Macro/GenerateMacro.h"
#include"Refrection.hpp"
static void G_AUTO_REGISTER_FUNCTION_Transform()
{
    HARMONY::ClassBuilder::Registration(TEXT("Transform"), &HARMONY::CORE::Transform::StaticGetClass);
}
struct AUTO_REGISTER_STRUCTURE_Transform
{
   AUTO_REGISTER_STRUCTURE_Transform()
    {
       G_AUTO_REGISTER_FUNCTION_Transform();
    }
};
struct AUTO_REGISTER_STRUCTURE_Transform ARS={};
namespace HARMONY{
namespace CORE{
   struct G_Class_Declaration_Field_Transform
    {
       const static inline HMArray<Property*> _propertyField = 
        {
           HM_ADD_PROPERTY_CLASS(Transform,_position),
           HM_ADD_PROPERTY_CLASS(Transform,_scale),
           HM_ADD_PROPERTY_CLASS(Transform,_rotate),
        };
    };
   inline Class* Transform::G_GetClassDataTransform()
    {
       HM_CLASS_CREATE(Transform,&Component::StaticGetClass)
return _class;

    }
}
}
