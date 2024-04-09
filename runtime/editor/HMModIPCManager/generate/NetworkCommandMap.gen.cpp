#include"NetworkCommandMap.h"
#include"Class/ClassBuilder.h"
#include"Class/deteil/ClassData.h"
#include"Macro/GenerateMacro.h"
#include"Refrection.hpp"
static void G_AUTO_REGISTER_FUNCTION_NetworkCommandMap()
{
    HARMONY::ClassBuilder::Registration(TSTR("NetworkCommandMap"), &HARMONY::NetworkCommandMap::StaticGetClass);
}
struct AUTO_REGISTER_STRUCTURE_NetworkCommandMap
{
   AUTO_REGISTER_STRUCTURE_NetworkCommandMap()
    {
       G_AUTO_REGISTER_FUNCTION_NetworkCommandMap();
    }
};
struct AUTO_REGISTER_STRUCTURE_NetworkCommandMap ARS={};
namespace HARMONY{
   struct G_Class_Declaration_Field_NetworkCommandMap
    {
        static HMArray<Property*>& GetPropertyField() {
            static HMArray<Property*> propertyField = {
        };
return propertyField;
    }
        static HMArray<Construction*>& GetConstraction(){
        static HMArray<Construction*> constructionField = {
           HM_ADD_CONSTRUCTION(NetworkCommandMap),
        };
    return constructionField;
    }
    };
   inline Class* NetworkCommandMap::G_GetClassDataNetworkCommandMap()
    {
       HM_CLASS_CREATE(NetworkCommandMap,nullptr)
        return _class;

    }
}
