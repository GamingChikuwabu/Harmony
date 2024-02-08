#include"generatemacro.h"
#include"HMObject.generate.h"
#include"HMObject.h"

HM_GENERATE_CLASS_METADATA_REGIST_START()
{
	HARMONY::TypeManager::class_<HARMONY::HMObject>("HMObject")
		.construct<>()
		.property("_guid", &HARMONY::HMObject::_guid)
		.property("_counter", &HARMONY::HMObject::counter);
}

namespace HARMONY
{
	
}