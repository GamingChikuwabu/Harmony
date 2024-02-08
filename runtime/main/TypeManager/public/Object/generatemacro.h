#pragma once
#include"ArchiveBace.h"

///クラスのトークン
#define HMCLASS(...)
#define HMFUNCTION(...)
#define HMPROPERTY(...)
#define HM_CLASS_ACCESS_FRIEND()\
friend void ::auto_register_class_type();\ 
template<typename Archive, typename T>\
friend void archive(Archive ar, T& obj);

static void auto_register_class_type();
#define HM_GENERATE_CLASS_METADATA_REGIST_START()\
namespace {\
struct register_type_static_initializer\
{\
	register_type_static_initializer() {\
		auto_register_class_type();\
	}\
};\
}\
static const register_type_static_initializer inintializer;\
static void auto_register_class_type()