#include"Component.h"
#include"Class/ClassBuilder.h"
#include"Class/deteil/ClassData.h"
#include"Macro/GenerateMacro.h"
#include"Refrection.hpp"
static void G_AUTO_REGISTER_FUNCTION_Component()
{
    HARMONY::ClassBuilder::Registration(TEXT("Component"), &HARMONY::CORE::Component::StaticGetClass);
}
struct AUTO_REGISTER_STRUCTURE_Component
{
   AUTO_REGISTER_STRUCTURE_Component()
    {
       G_AUTO_REGISTER_FUNCTION_Component();
    }
};
struct AUTO_REGISTER_STRUCTURE_Component ARS={};
namespace HARMONY{
namespace CORE{
   struct G_Class_Declaration_Field_Component
    {
       const static inline HMArray<Property*> _propertyField = 
        {
        };
    };
   inline Class* Component::G_GetClassDataComponent()
    {
       HM_CLASS_CREATE(Component,&HMObject::StaticGetClass)
return _class;

    }
}
}
