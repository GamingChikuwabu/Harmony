#pragma once

namespace HARMONY
{
	class PathManager
	{
	public:
		static void Init();
		static void Terminate();
	private:
		class Impl* _impl;
	};
}