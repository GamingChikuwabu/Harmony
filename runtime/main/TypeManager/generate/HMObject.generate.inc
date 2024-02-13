#pragma once
#include"generatemacro.h"
#include "TypeManager.h"

HM_GENERATE_CLASS_METADATA_REGIST_START()
{
	HARMONY::TypeManager::class_<HARMONY::HMObject>("HMObject")
		.construct<>()
		.property("_guid", &HARMONY::HMObject::_guid);
}