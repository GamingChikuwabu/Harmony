#pragma once
#define HM_MANUAL_REGISTER_BASE_CLASS_BODY(classType)\
private:\
friend struct G_Class_Declaration_Field_##classType;\
static HARMONY::Class* G_GetClassData##classType();\
public:\
static inline HARMONY::Class* StaticGetClass()\
{\
    return G_GetClassData##classType();\
}\
inline virtual HARMONY::Class* GetClass()const\
{\
    return classType::StaticGetClass();\
}

#define HM_MANUAL_REGISTER_DERIVED_CLASS_BODY(classType,derivedClassType)\
public:\
using Super = derivedClassType;\
private:\
friend struct G_Class_Declaration_Field_##classType;\
static HARMONY::Class* G_GetClassData##classType();\
public:\
static inline HARMONY::Class* StaticGetClass()\
{\
    return G_GetClassData##classType();\
}\
inline virtual HARMONY::Class* GetClass()const\
{\
    return classType::StaticGetClass();\
}

#define HM_MANUAL_REGISTER_BASE_CLASS_BODY_PROPERTIES(classType)\
static void G_AUTO_REGISTER_FUNCTION_##classType()\
{\
    HARMONY::ClassBuilder::Registration(TSTR(#classType), &classType::StaticGetClass);\
}\
struct AUTO_REGISTER_STRUCTURE_##classType\
{\
    AUTO_REGISTER_STRUCTURE_##classType()\
    {\
        G_AUTO_REGISTER_FUNCTION_##classType();\
    }\
};\
struct AUTO_REGISTER_STRUCTURE_##classType ARS = {};\
    struct G_Class_Declaration_Field_##classType\
    {\
        static HMArray<Property*>& GetPropertyField() {\
            static HMArray<Property*> propertyField = {

#define HM_MANUAL_REGISTER_BASE_CLASS_BODY_PROPERTIES_END(classType)\
 };\
            return propertyField;\
        }\
        static HMArray<Construction*>& GetConstraction() {\
            static HMArray<Construction*> constructionField = {\
               HM_ADD_CONSTRUCTION(classType),\
            };\
            return constructionField;\
        }\
};\
inline Class* classType::G_GetClassData##classType()\
{\
     HM_CLASS_CREATE(classType, nullptr)\
     return _class; \
}


#define HM_MANUAL_REGISTER_DERIVED_CLASS_BODY_PROPERTIES(classType)\
static void G_AUTO_REGISTER_FUNCTION_##classType()\
{\
    HARMONY::ClassBuilder::Registration(TSTR(#classType), &classType::StaticGetClass);\
}\
struct AUTO_REGISTER_STRUCTURE_##classType\
{\
    AUTO_REGISTER_STRUCTURE_##classType()\
    {\
        G_AUTO_REGISTER_FUNCTION_##classType();\
    }\
};\
struct AUTO_REGISTER_STRUCTURE_##classType ARS = {};\
    struct G_Class_Declaration_Field_##classType\
    {\
        static HMArray<Property*>& GetPropertyField() {\
            static HMArray<Property*> propertyField = {



#define HM_MANUAL_REGISTER_DERIVED_CLASS_BODY_PROPERTIES_END(classType,derived)\
 };\
        return propertyField;\
    }\
        static HMArray<Construction*>& GetConstraction() {\
            static HMArray<Construction*> constructionField = {\
               HM_ADD_CONSTRUCTION(classType),\
            };\
            return constructionField;\
        }\
};\
inline Class* classType::G_GetClassData##classType()\
    {\
        HM_CLASS_CREATE(classType, &derived::StaticGetClass)\
        return _class;\
    }