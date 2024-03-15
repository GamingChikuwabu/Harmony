#include"HMObject.h"
#include<rttr/registration.h>

namespace HARMONY
{
	HMObject::HMObject()
	{

	}

	HMObject::~HMObject()
	{

	}
}

RTTR_REGISTRATION
{
	rttr::registration::class_<HARMONY::HMObject>("HMObject")
	.property("guid",&HARMONY::HMObject::_guid);
}