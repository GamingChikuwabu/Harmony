#pragma once
#include<string>
#include<fstream>
#include"Archive/namevaluepair.h"

namespace HARMONY
{
	class TYPEMANAGER_API OArchive
	{
	public:
		
	protected:
		std::ofstream& _ofs;
	};
}