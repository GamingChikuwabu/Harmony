#include"Archive/namevaluepair.h"

TYPEMANAGER_API HARMONY::NVP HARMONY::make_nvp(const std::string& name, variant value)
{
	return { name, value };
}