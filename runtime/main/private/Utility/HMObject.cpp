#include"HMObject.h"

namespace HARMONY
{
	HMObject::HMObject()
	:_guid(TSTR("dummy")),
	_isValid(true),
	vec(0.03f,2099.0f,53.5f),
	ag(0),
	test(0)
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