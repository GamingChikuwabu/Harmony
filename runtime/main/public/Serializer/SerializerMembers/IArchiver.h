#pragma once
#include"Archiver.h"

namespace HARMONY
{
	namespace SERIALIZER
	{
		class IArchiver : public Archiver
		{
		public:
			IArchiver() = default;
			bool IsSave()override 
			{
				return true;
			}
		};
	}
}