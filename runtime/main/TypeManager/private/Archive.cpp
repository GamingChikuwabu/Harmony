#include"Archive.h"
#include"JsonArchive.h"

namespace HARMONY
{
	HMArchive::HMArchive(ArchiveType archive_type, std::ofstream& ofs)
	{
		/*switch (archive_type)
		{
		case HARMONY::ArchiveType::Binary:
			break;
		case HARMONY::ArchiveType::Json:
			_oArchiveBase = new OJsonArchive(ofs);
			break;
		case HARMONY::ArchiveType::XML:
			break;
		default:
			break;
		}*/
	}
	
	void HMArchive::savefile()
	{
		/*return _oArchiveBase->to_savefile();*/
	}
}