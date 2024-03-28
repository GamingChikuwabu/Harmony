#include"ObjectMacro.h"
#include"Class/ClassBuilder.h"
#include"Class/deteil/ClassData.h"
#include"Macro/GenerateMacro.h"
static void G_AUTO_REGISTER_FUNCTION_()
{
   HARMONY::ClassBuilder::Registration(TEXT("HMObject"), &::GetClass);
}
struct AUTO_REGISTER_STRUCTURE_
{
   AUTO_REGISTER_STRUCTURE_()
    {
       G_AUTO_REGISTER_FUNCTION_();
    }
};
struct AUTO_REGISTER_STRUCTURE_ ARS={};
   struct G_Class_Declaration_Field_
    {
       const static inline HMArray<Property*> _propertyField = 
        {
        };
    };
   inline Class* ::G_GetClassData()
    {
       HM_CLASS_CREATE()
return _class;

    }
