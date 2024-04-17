#include"HMObject.h"
#include"Reflection/Reflection.hpp"
#include"Macro/GenerateMacro.h"


namespace HARMONY
{
	HM_MANUAL_REGISTER_BASE_CLASS_BODY_PROPERTIES(HMObject)
		HM_ADD_PROPERTY_STRING(HMObject, _guid),
	HM_MANUAL_REGISTER_BASE_CLASS_BODY_PROPERTIES_END(HMObject)

	HMObject::HMObject():
	_guid(TSTR("syokiti"))
	{
	
	}

	HMObject::~HMObject()
	{

	}

	bool HMObject::isValid() const noexcept
	{
		return false;
	}
}