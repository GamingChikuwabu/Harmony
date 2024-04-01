#pragma once
#include"rttr/registration.h"
#include"rttr/registration_friend.h"
///クラスのトークン
#define HMCLASS(...)
#define HMFUNCTION(...)
#define HMPROPERTY(...)
#define HM_CLASS_BODY(...)\
#define COMMENT "COMMENT"
RTTR_ENABLE(__VA_ARGS__)\
RTTR_REGISTRATION_FRIEND

#define HM_GENERATE_CLASS_METADATA_REGIST_START(classtype)\
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