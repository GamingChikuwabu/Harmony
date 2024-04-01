#include "PropertyArray.h"

namespace HARMONY
{
	ScriptArray PropertyArray::GetScriptArray(void* classInstance)
	{
		return GetScriptArrayFunc(classInstance);
	}
	inline PropertyKind PropertyArray::GetKind()
	{
		return PropertyKind::Array;
	}
}