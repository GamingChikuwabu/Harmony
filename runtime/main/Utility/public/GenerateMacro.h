#pragma once

///クラスのトークン
#define HMCLASS(...)
#define HMFUNCTION(...)
#define HMPROPERTY(...)
#define HM_CLASS_BODY(...)
//friend void ::auto_register_class_type();
//
//static void auto_register_class_type();
//#define HM_GENERATE_CLASS_METADATA_REGIST_START()\
//namespace {\
//struct register_type_static_initializer\
//{\
//	register_type_static_initializer() {\
//		auto_register_class_type();\
//	}\
//};\
//}\
//static const register_type_static_initializer inintializer;\
//static void auto_register_class_type()