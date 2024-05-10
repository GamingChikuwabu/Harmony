#pragma once
#include<fstream>

#ifdef UNICODE
	using Ifstream = std::wifstream;
	using Ofstream = std::wofstream;

#else
	using Ifstream = std::ifstream;
	using Ofstream = std::ofstream;
#endif // UNICODE