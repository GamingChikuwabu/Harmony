#include"HMObject.h"
#include"Registration.h"
#include"GenerateMacro.h"

HM_GENERATE_CLASS_METADATA_REGIST_START()
{
	using namespace HARMONY;
	Registration::class_<HMObject>("HMObject")
		.property("guid", &HMObject::_guid);
}