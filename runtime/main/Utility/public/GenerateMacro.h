#pragma once

#define REF_LIB_CERIAL

#ifdef REF_LIB_RTTR
#include<rttr/registration>
#include<rttr/registration_friend.h>

///クラスのトークン
#define HMCLASS(...)
#define HMFUNCTION(...)
#define HMPROPERTY(...)
#define HM_CLASS_BODY(...)\
RTTR_ENABLE(__VA_ARGS__)\
RTTR_REGISTRATION_FRIEND \

#define HM_GENERATE_CLASS_METADATA_REGIST_START(myclass)\
RTTR_REGISTRATION\
{

#define HM_GENERATE_CLASS_METADATA_REGIST_END() ;}

#define HM_USING_NAMESPACE(usernamespace)\
using namespace usernamespace;

#define HM_REGISTRATION_CONSTRACTOR(...)\
.constructor<__VA_ARGS__>()

#define HM_REGISTRATION_CLASS(Class)\
rttr::registration::class_<Class>(#Class)

#define HM_REGISTRATION_PROPERTY(Class,prop)\
.property(#prop,&Class::prop)

#define HM_REGISTRATION_METADATA(key,value)\
(rttr::metadata(key,value))

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
#endif
#ifdef REF_LIB_CERIAL

///クラスのトークン
#define HMCLASS(...)
#define HMFUNCTION(...)
#define HMPROPERTY(...)
#define HM_CLASS_BODY(...)

#endif