#pragma once
#include<ostream>

namespace HARMONY
{
	class variant;
	namespace ARCHIVE
	{
		class OJsonArchive
		{
		public:
			OJsonArchive(const std::ostream& os);
			~OJsonArchive();
			const char* ToString()const;
			void Archive(variant var)const;
		};
	}
}