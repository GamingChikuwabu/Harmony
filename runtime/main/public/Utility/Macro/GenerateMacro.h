#pragma once
#include"PropertyAccessor.h"
#include"Property.h"

// メンバ変数の型を抜き出すメタ関数
template<typename T>
struct member_type;

// メンバ変数の型を特殊化して抜き出すためのメタ関数の実装
template<typename C, typename M>
struct member_type<M C::*> {
    using type = M;
};

#define HM_PROPERTY_ACCESSER_MEMBER_NUM(PropertyType)\
HARMONY::PropertyAccessor\
        <HARMONY::DETAIL::member_object_pointer,HARMONY::DETAIL::numeric,\
         PropertyType\
>

#define HM_CLASS_CREATE(className,func)\
static Class* _class = new (GC_NEW(Class)) Class(new (GC_NEW(ClassData)) ClassData(TSTR(#className), sizeof(className), G_Class_Declaration_Field_##className::GetPropertyField(),G_Class_Declaration_Field_##className::GetConstraction(),func));

#define HM_ADD_PROPERTY_STRING(classType,Member)\
new (GC_NEW(HM_PROPERTY_ACCESSER_MEMBER_NUM(HARMONY::PropertyString)))\
HM_PROPERTY_ACCESSER_MEMBER_NUM(HARMONY::PropertyString)(OFFSET_OF(classType,Member),TSTR(#Member))

#define HM_ADD_PROPERTY_INT32(classType,Member)\
new (GC_NEW(HM_PROPERTY_ACCESSER_MEMBER_NUM(HARMONY::PropertyInt32)))\
HM_PROPERTY_ACCESSER_MEMBER_NUM(HARMONY::PropertyInt32)(OFFSET_OF(classType,Member),TSTR(#Member))

#define HM_ADD_PROPERTY_UINT32(classType, Member)\
new (GC_NEW(HM_PROPERTY_ACCESSER_MEMBER_NUM(HARMONY::PropertyUInt32)))\
HM_PROPERTY_ACCESSER_MEMBER_NUM(HARMONY::PropertyUInt32)(OFFSET_OF(classType, Member), TSTR(#Member)) 

#define HM_ADD_PROPERTY_INT64(classType, Member)\
new (GC_NEW(HM_PROPERTY_ACCESSER_MEMBER_NUM(HARMONY::PropertyInt64)))\
HM_PROPERTY_ACCESSER_MEMBER_NUM(HARMONY::PropertyInt64)(OFFSET_OF(classType, Member), TSTR(#Member))

// uint64型のプロパティを追加
#define HM_ADD_PROPERTY_UINT64(classType, Member)\
new (GC_NEW(HM_PROPERTY_ACCESSER_MEMBER_NUM(HARMONY::PropertyUInt64)))\
HM_PROPERTY_ACCESSER_MEMBER_NUM(HARMONY::PropertyUInt64)(OFFSET_OF(classType, Member), TSTR(#Member))

#define HM_ADD_PROPERTY_FLOAT(classType, Member)\
new (GC_NEW(HM_PROPERTY_ACCESSER_MEMBER_NUM(HARMONY::PropertyFloat)))\
HM_PROPERTY_ACCESSER_MEMBER_NUM(HARMONY::PropertyFloat)(OFFSET_OF(classType, Member), TSTR(#Member))

// double型のプロパティを追加
#define HM_ADD_PROPERTY_DOUBLE(classType, Member)\
new (GC_NEW(HM_PROPERTY_ACCESSER_MEMBER_NUM(HARMONY::PropertyDouble)))\
HM_PROPERTY_ACCESSER_MEMBER_NUM(HARMONY::PropertyDouble)(OFFSET_OF(classType, Member), TSTR(#Member))

#define HM_ADD_PROPERTY_BOOL(classType, Member)\
new (GC_NEW(HM_PROPERTY_ACCESSER_MEMBER_NUM(HARMONY::PropertyBool)))\
HM_PROPERTY_ACCESSER_MEMBER_NUM(HARMONY::PropertyBool)(OFFSET_OF(classType, Member), TSTR(#Member))

#define HM_ADD_PROPERTY_CLASS(classType,Member)\
new (GC_NEW(HM_PROPERTY_ACCESSER_MEMBER_NUM(HARMONY::PropertyClassBase<member_type<decltype(&classType::Member)>::type>)))\
HM_PROPERTY_ACCESSER_MEMBER_NUM(HARMONY::PropertyClassBase<member_type<decltype(&classType::Member)>::type>)(OFFSET_OF(classType, Member), TSTR(#Member))

#define HM_ADD_PROPERTY_ARRAY(classType,Member)\
new (GC_NEW(HM_PROPERTY_ACCESSER_MEMBER_NUM(HARMONY::PropertyArrayBase<member_type<decltype(&classType::Member)>::type::value_type>)))\
HM_PROPERTY_ACCESSER_MEMBER_NUM(HARMONY::PropertyArrayBase<member_type<decltype(&classType::Member)>::type::value_type>)(OFFSET_OF(classType, Member), TSTR(#Member))

#define UMAP_BASE(classType,Member)\
HARMONY::PropertyUMapBase\
<member_type<decltype(&classType::Member)>::type::KEY,\
member_type<decltype(&classType::Member)>::type::VALUE>

#define HM_ADD_PROPERTY_UMAP(classType,Member)\
new (GC_NEW(HM_PROPERTY_ACCESSER_MEMBER_NUM(UMAP_BASE(classType,Member))))\
HM_PROPERTY_ACCESSER_MEMBER_NUM(UMAP_BASE(classType,Member))(OFFSET_OF(classType, Member), TSTR(#Member))

#define CONSTRUCTER_BASE(classType,...)\
HARMONY::ConstructionBase<classType,__VA_ARGS__ >

#define INVOKER_BASE(classType,...)\
HARMONY::InvokerBase<classType,__VA_ARGS__>

#define HM_ADD_CONSTRUCTION(classType,...)\
new (GC_NEW(CONSTRUCTER_BASE(classType,__VA_ARGS__))) CONSTRUCTER_BASE(classType,__VA_ARGS__)\
(new (GC_NEW(INVOKER_BASE(classType,__VA_ARGS__))) INVOKER_BASE(classType,__VA_ARGS__)())