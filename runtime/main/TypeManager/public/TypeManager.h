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
#include<cstddef>

//========================================================================
// Mylib
//========================================================================


namespace HARMONY
{     
    namespace DETAIL
    {
        struct type_data;
    }
    class TYPEMANAGER_API TypeManager {
    public:
        /// @brief 
        /// @return 
        static bool Init();

        /// @brief 
        /// @tparam ClassType 
        template<class ClassType>
        class class_{
        public:
            /// @brief コンストラクタ
            /// @param name このクラスの型名
            class_(std::string name);
            ~class_();
            
            // 引数を取るコンストラクタを登録するメソッドの宣言
            template<typename... Args>
            typename std::enable_if<std::is_constructible<ClassType, Args...>::value, class_&>::type
            construct();

            template<typename MemberType>
            auto property(const std::string& name, MemberType ClassType::* memberPtr)
                -> std::enable_if_t<std::is_member_pointer<MemberType ClassType::*>::value, class_&>;
        private:
            
        };
    private:
        static inline std::unordered_map<>;
        static inline std::unordered_map<std::string,std::unique_ptr<DETAIL::type_data>> _typeData;
    };
}

#include"reflection/impl/TypeManager_impl.h"