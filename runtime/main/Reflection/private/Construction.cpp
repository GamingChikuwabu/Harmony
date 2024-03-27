#include"Construction/Construction.h"

namespace HARMONY
{
	void* Construction::invoke()
	{
		for (auto fn : _constructor)
		{
			auto temp = std::any_cast<std::function<void* ()>>(fn);
			if (temp)
			{
				return temp();
			}
		}
		return nullptr;
	}
}