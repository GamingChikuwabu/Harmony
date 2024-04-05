#include"GameObject.h"
#include"Class/ClassBuilder.h"
#include"Class/deteil/ClassData.h"
#include"Macro/GenerateMacro.h"
#include"Refrection.hpp"
static void G_AUTO_REGISTER_FUNCTION_GameObject()
{
    HARMONY::ClassBuilder::Registration(TSTR("GameObject"), &HARMONY::CORE::GameObject::StaticGetClass);
}
struct AUTO_REGISTER_STRUCTURE_GameObject
{
   AUTO_REGISTER_STRUCTURE_GameObject()
    {
       G_AUTO_REGISTER_FUNCTION_GameObject();
    }
};
struct AUTO_REGISTER_STRUCTURE_GameObject ARS={};
namespace HARMONY{
namespace CORE{
   struct G_Class_Declaration_Field_GameObject
    {
       const static inline HMArray<Property*> _propertyField = 
        {
           HM_ADD_PROPERTY_CLASS(GameObject,_transform),
           HM_ADD_PROPERTY_STRING(GameObject,_name),
           HM_ADD_PROPERTY_STRING(GameObject,_tag),
           HM_ADD_PROPERTY_STRING(GameObject,_layer),
           HM_ADD_PROPERTY_ARRAY(GameObject,m_componentList),
        };
    };
   inline Class* GameObject::G_GetClassDataGameObject()
    {
       HM_CLASS_CREATE(GameObject,&HMObject::StaticGetClass)
        return _class;

    }
}
}
