#pragma once

//========================================================================
// STD
//========================================================================
#include<unordered_map>
#include<string>
#include<any>
#include<string_view>
#include<typeindex>
#include<functional>
#include<memory>
#include <cstddef>

//========================================================================
// Mylib
//========================================================================
#include"Types/property.h"
#include"Types/type.h"
#include"Types/ItemCreator.h"

namespace HARMONY
{     
    class TYPEMANAGER_API TypeManager {
    public:
        static bool Init();
        template<class ClassType>
        class class_{
        public:
            /// @brief コンストラクタ
            /// @param name このクラスの型名
            class_(std::string name){
                DETAIL::ItemCreator::CreateType<ClassType>(name);
            }
            
            // 引数を取るコンストラクタを登録するメソッド
            template<typename... Args, typename = std::enable_if_t<std::is_constructible<ClassType, Args...>::value>>
            class_& construct() {
                /*std::string key = GenerateConstructorKey<Args...>();
                ConstructorDelegate<Args...> delegate = [](Args... args) -> ClassType* {
                    return new ClassType(std::forward<Args>(args)...);
                    };
                _classConstructors[std::type_index(typeid(ClassType))][key] = delegate;*/
                return *this;
            }

            template<typename MemberType>
            auto property(const std::string& name, MemberType ClassType::* memberPtr)
                -> std::enable_if_t<std::is_member_pointer<MemberType ClassType::*>::value, class_&>
            {
                _properties[name] = DETAIL::ItemCreator::CreateProperty<ClassType,MemberType>(name,memberPtr); 
                return *this;
            }

            template<typename BaceClass>
            class_& baceclass()
            {
                static_assert(std::is_base_of<BaceClass,ClassType>::value,"基底クラスがないのでこの宣言は無効です");
                _baceClass = Type::FindByType<BaceClass>();
            }

            // 引数を取るインスタンス生成メソッド
            template<typename... Args>
            ClassType* CreateInstance(Args... args) {
                std::string key = GenerateConstructorKey<Args...>();
                auto& classMap = _classConstructors[std::type_index(typeid(ClassType))];
                auto it = classMap.find(key);
                if (it != classMap.end()) {
                    auto constructorDelegate = std::any_cast<ConstructorDelegate<Args...>>(it->second);
                    return constructorDelegate(std::forward<Args>(args)...);
                }
                return nullptr;
            }
        private:
            Type _baseClass;
            std::unordered_map<std::type_index, std::unordered_map<std::string, std::any>>  _classConstructors;//コンストラクタのマップ
            std::unordered_map<std::string, Property>                                       _properties;//プロパティのマップ
        };
    private:
        // 型の名前をキーにして型安全にメタデータを保存
        static inline std::unordered_map<std::string, Type> _Types;
    };
}