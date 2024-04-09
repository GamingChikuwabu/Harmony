#pragma once
#include<string>
#include"ObjectMacro.h"
#include"HMString.h"
#include"gc/gc_cpp.h"
#include"Refrection.hpp"
#include"Utility.hpp"
#include"HMObject.generate.h"

namespace HARMONY
{
	// コマンド情報を格納する構造体
struct CommandInfo {
	int id;
	std::string description;
};
HMCLASS()
struct NetworkCommandMap
{
	HM_CLASS_BODY()
	HMUnorderedMap<HMString, CommandInfo> commandMap;
};
}