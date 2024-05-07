#pragma once
#include<fstream>
#include"HMString.h"

namespace HARMONY
{
	namespace FILEHELPER
	{
#ifdef UNICODE
#ifdef _WIN32 // UTF16 for Windows
		using Ofstream = std::wofstream;
		using Ifstream = std::wifstream;
#else // UTF32 for Unix-like systems
		using Ofstream = std::wofstream;
		using Ifstream = std::wifstream;
#endif // _WIN32
#else // Multibyte character set
		using Ofstream = std::ofstream;
		using Ifstream = std::ifstream;
#endif
		class HMFileHelperBase
		{
		public:
			HMFileHelperBase(Ofstream& ofs,const TCHAR* outputpath);
			HMFileHelperBase(Ifstream& ifs,const TCHAR* inputpath);
			virtual ~HMFileHelperBase();
			virtual bool Open() = 0;
			virtual void Close() = 0;
		protected:
			const Ofstream& m_ofs;
			const Ifstream& m_ifs;
		};
	}
}