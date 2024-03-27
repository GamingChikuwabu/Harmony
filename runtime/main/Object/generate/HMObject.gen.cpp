#include"HMObject.h"

static void AUTO_REGISTER_FUNCTION_HMObject()
{

}

AUTO_REGISTER_STRUCTURE_HMObject ARS = {};

template<>
static HARMONY::Class* GetStaticClass<HARMONY::HMObject>()
{
	HARMONY::Class::GetClassByName(TEXT("HMObject"));
}