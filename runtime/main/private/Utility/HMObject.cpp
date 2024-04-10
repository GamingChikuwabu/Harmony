#include"HMObject.h"
#include"Reflection/Reflection.hpp"
#include"Macro/GenerateMacro.h"


namespace HARMONY
{
	HM_MANUAL_REGISTER_BASE_CLASS_BODY_PROPERTIES(HMObject)
		HM_ADD_PROPERTY_STRING(HMObject, _guid),
		HM_ADD_PROPERTY_ARRAY(HMObject, _gg)
	HM_MANUAL_REGISTER_BASE_CLASS_BODY_PROPERTIES_END(HMObject)

	HMObject::HMObject():
	_guid(TSTR("syokiti"))
	{
		_gg.Add(MATH::Float3(0.0f,2.0f,0.0f));
		_gg.Add(MATH::Float3(6.0f, 2.0f, 9.0f));
	}

	HMObject::~HMObject()
	{

	}

	bool HMObject::isValid() const noexcept
	{
		return false;
	}
}