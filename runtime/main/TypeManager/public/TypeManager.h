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

//========================================================================
// Mylib
//========================================================================
#include"Types/property.h"
#include"Types/type.h"

namespace HARMONY
{     
    class TYPEMANAGER_API TypeManager {
    public:
        static bool Init();
        template<class ClassType>
        class class_ : public Type{
        public:
            /// @brief コンストラクタ
            /// @param name このクラスの型名
            class_(std::string name):Type::Type(typeid(ClassType), name,sizeof(ClassType)) {
                // std::type_indexを使って型安全性を確保
                TypeManager::_Types[name] = std::move(this);
            }
            
            // 引数を取るコンストラクタを登録するメソッド
            template<typename... Args, typename = std::enable_if_t<std::is_constructible<ClassType, Args...>::value>>
            class_& construct() {
                std::string key = GenerateConstructorKey<Args...>();
                ConstructorDelegate<Args...> delegate = [](Args... args) -> ClassType* {
                    return new ClassType(std::forward<Args>(args)...);
                    };
                _classConstructors[std::type_index(typeid(ClassType))][key] = delegate;
                return *this;
            }

            template<typename MemberType>
            std::enable_if_t<std::is_member_pointer<MemberType ClassType::*>::value, class_&>
            property(const std::string& name, MemberType ClassType::* memberPtr) {
                // std::anyを使って異なる型のPropertyを保存
                _properties[name] = new Property<ClassType, MemberType>(name,memberPtr);
                return *this;
            }

            template<typename BaceClass>
            class_& baceclass()
            {
                static_assert(std::is_base_of<BaceClass,ClassType>::value,"基底クラスがないのでこの宣言は無効です");
                _baceClass = TypeManager::GetType<BaceClass>();
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
            // 引数の型情報を基にキーを生成するヘルパー関数
            template<typename... Args>
            std::string GenerateConstructorKey() {
                return typeid(std::tuple<Args...>).name();
            }

            // コンストラクタ用のデリゲートをテンプレート化
            template <typename... Args>
            using ConstructorDelegate = std::function<ClassType* (Args...)>;

            Type* _baceClass; 
            std::unordered_map<std::type_index, std::unordered_map<std::string, std::any>>  _classConstructors;//コンストラクタのマップ
            std::unordered_map<std::string, PropertyBase*>                                  _properties;//プロパティのマップ
        };

        template<class Type>
        static const Type* GetType()
        {
            std::type_index index(typeid(Type));
            if (_Types.find(index) != _Types.end()) { 
                return _Types[index];
            }
            return nullptr;
        }

        static void* CreateInstanceByName(const std::string& name) {
            if (_Types.find(name) != _Types.end()) {
                return _Types[name]->CreateInstanceByType();
            }
            return nullptr;
        }

    private:
        
        // 型の名前をキーにして型安全にメタデータを保存
        static inline std::unordered_map<std::string, Type*> _Types;
    };
}