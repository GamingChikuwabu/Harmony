#pragma once
#include"PropertyAccessor.h"

// メンバ変数の型を抜き出すメタ関数
template<typename T>
struct member_type;

// メンバ変数の型を特殊化して抜き出すためのメタ関数の実装
template<typename C, typename M>
struct member_type<M C::*> {
    using type = M;
};

#define HM_CLASS_CREATE(className,func)\
static Class* _class = new (GC_NEW(Class)) Class(new (GC_NEW(ClassData)) ClassData(TEXT(#className), sizeof(className), G_Class_Declaration_Field_##className::_propertyField,func)	);

#define HM_ADD_PROPERTY_STRING(classType,Member)\
new (GC_NEW(\
     HARMONY::PropertyAccessor\
        <HARMONY::DETAIL::member_object_pointer,
         HARMONY::DETAIL::numeric,\
         HARMONY::PropertyString,HARMONY::HMString classType::Member>)) HARMONY::PropertyAccessor<HARMONY::DETAIL::member_object_pointer,HARMONY::DETAIL::numeric,HARMONY::PropertyString,HARMONY::HMString classType::Member>(&classType::Member,TEXT(#Member))

#define HM_ADD_PROPERTY_INT32(classType,Member)\
new (GC_NEW(PropertyInt32)) PropertyInt32(TEXT(#Member),&classType::Member)

#define HM_ADD_PROPERTY_INT64(classType,Member)\
new (GC_NEW(PropertyInt64)) PropertyInt64(TEXT(#Member),&classType::Member)

#define HM_ADD_PROPERTY_FLOAT(classType,Member)\
new (GC_NEW(PropertyFloat)) PropertyFloat(TEXT(#Member),&classType::Member)

#define HM_ADD_PROPERTY_BOOL(classType,Member)\
new (GC_NEW(PropertyBool)) PropertyBool(TEXT(#Member),&classType::Member)

#define HM_ADD_PROPERTY_ARRAY(classType,Member)\
new (GC_NEW(PropertyArray)) PropertyArray(TEXT(#Member),&classType::Member)

#define HM_ADD_PROPERTY_CLASS(classType,Member)\
new (GC_NEW(PropertyClass)) PropertyClass(TEXT(#Member),&classType::Member)