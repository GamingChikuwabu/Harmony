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
                
            }
            
            // 引数を取るコンストラクタを登録するメソッド
            template<typename... Args, typename = std::enable_if_t<std::is_constructible<ClassType, Args...>::value>>
            class_& construct() {
                return *this;
            }

            template<typename MemberType>
            auto property(const std::string& name, MemberType ClassType::* memberPtr)
                -> std::enable_if_t<std::is_member_pointer<MemberType ClassType::*>::value, class_&>
            {
                return *this;
            }
        };
    };
}