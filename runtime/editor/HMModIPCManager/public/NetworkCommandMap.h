#pragma once
#include"Utility.hpp"
#include"NetworkCommandMap.generate.h"

namespace HARMONY
{
	struct CommandInfo;
	HMCLASS()
	struct NetworkCommandMap
	{
		HM_CLASS_BODY()
		HMUnorderedMap<HMString, CommandInfo> commandMap;
	};
	// コマンド情報を格納する構造体
	struct CommandInfo {
		int id;
		std::string description;
	};
}