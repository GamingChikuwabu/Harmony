#include"Component.h"
#include"Class/ClassBuilder.h"
#include"Class/deteil/ClassData.h"
#include"Macro/GenerateMacro.h"
#include"Refrection.hpp"
static void G_AUTO_REGISTER_FUNCTION_Component()
{
    HARMONY::ClassBuilder::Registration(TSTR("Component"), &HARMONY::CORE::Component::StaticGetClass);
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
        static HMArray<Property*>& GetPropertyField() {
            static HMArray<Property*> propertyField = {
        };
return propertyField;
    }
        static HMArray<Construction*>& GetConstraction(){
        static HMArray<Construction*> constructionField = {
           HM_ADD_CONSTRUCTION(Component),
        };
    return constructionField;
    }
    };
   inline Class* Component::G_GetClassDataComponent()
    {
       HM_CLASS_CREATE(Component,&HMObject::StaticGetClass)
        return _class;

    }
}
}
