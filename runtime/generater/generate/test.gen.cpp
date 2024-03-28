#include"test.h"
#include"Class/ClassBuilder.h"
#include"Class/deteil/ClassData.h"
#include"GenerateMacro.h"
static void G_AUTO_REGISTER_FUNCTION_HMObject()
{
   HARMONY::ClassBuilder::Registration(TEXT("HMObject"), &HARMONY::HMObject::GetClass);
}
struct AUTO_REGISTER_STRUCTURE_HMObject
{
   AUTO_REGISTER_STRUCTURE_HMObject()
    {
       void G_AUTO_REGISTER_FUNCTION_HMObject();
    }
};
struct AUTO_REGISTER_STRUCTURE_HMObject ARS;
namespace HARMONY{
   struct G_Class_Declaration_Field_HMObject
    {
       const static inline HMArray<Property*> _propertyField = 
        {
           HM_ADD_PROPERTY_STRING(HMObject,_guid),
           HM_ADD_PROPERTY_BOOL(HMObject,_isValid),
        };
    };
   inline Class* HMObject::G_GetClassDataHMObject()
    {
       static Class* _class = new (GC_NEW(Class)) Class(new (GC_NEW(ClassData)) ClassData(TEXT("HMObject"), sizeof(HMObject), G_Class_Declaration_Field_HMObject::_propertyField)	);return _class;
    }
}
