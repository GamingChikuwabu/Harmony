#include"HMObject.h"

namespace HARMONY
{
	HMObject::HMObject()
	{
		_guid = TEXT("");
	}

	HMObject::~HMObject()
	{

	}

	bool HMObject::isValid() const noexcept
	{
		return _isValid;
	}
}