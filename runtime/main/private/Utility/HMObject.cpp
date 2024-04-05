#include"HMObject.h"

namespace HARMONY
{
	HMObject::HMObject()
	:_guid(TSTR("dummy")),
	_isValid(true)
	{

	}

	HMObject::~HMObject()
	{

	}

	bool HMObject::isValid() const noexcept
	{
		return _isValid;
	}
}