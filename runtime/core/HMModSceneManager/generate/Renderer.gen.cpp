#include"Renderer.h"
#include"Class/ClassBuilder.h"
#include"Class/deteil/ClassData.h"
#include"Macro/GenerateMacro.h"
#include"Refrection.hpp"
static void G_AUTO_REGISTER_FUNCTION_Renderer()
{
    HARMONY::ClassBuilder::Registration(TSTR("Renderer"), &HARMONY::CORE::Renderer::StaticGetClass);
}
struct AUTO_REGISTER_STRUCTURE_Renderer
{
   AUTO_REGISTER_STRUCTURE_Renderer()
    {
       G_AUTO_REGISTER_FUNCTION_Renderer();
    }
};
struct AUTO_REGISTER_STRUCTURE_Renderer ARS={};
namespace HARMONY{
namespace CORE{
   struct G_Class_Declaration_Field_Renderer
    {
        static HMArray<Property*>& GetPropertyField() {
            static HMArray<Property*> propertyField = {
        };
return propertyField;
    }
        static HMArray<Construction*>& GetConstraction(){
        static HMArray<Construction*> constructionField = {
           HM_ADD_CONSTRUCTION(Renderer),
        };
    return constructionField;
    }
    };
   inline Class* Renderer::G_GetClassDataRenderer()
    {
       HM_CLASS_CREATE(Renderer,&Component::StaticGetClass)
        return _class;

    }
}
}
