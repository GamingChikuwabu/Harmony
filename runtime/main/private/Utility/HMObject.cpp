#include"HMObject.h"

namespace HARMONY
{
	HMObject::HMObject():
	_guid(TSTR("syokiti"))
	{
		_gg.Add(MATH::Float3(0.0f,2.0f,0.0f));
		_gg.Add(MATH::Float3(6.0f, 2.0f, 9.0f));
		_mapper[10] = TSTR("mamamama");
	}

	HMObject::~HMObject()
	{

	}

	bool HMObject::isValid() const noexcept
	{
		return false;
	}
}