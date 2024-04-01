#include"HMObject.h"

namespace HARMONY
{
	HMObject::HMObject()
	:_guid(TEXT("guid")),
	_isValid(true)
	{
		damy.Add(10);
		damy.Add(20);
	}

	HMObject::~HMObject()
	{

	}

	bool HMObject::isValid() const noexcept
	{
		return _isValid;
	}
}