#pragma once
#include <string>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <string>
#include <memory>

namespace HARMONY
{
    // 型情報を保存する基底クラス
    class TYPEMANAGER_API Type {
    public:
        /// @brief 初回登録用のコンストラクタ
        /// @param info 型のtypeid情報
        /// @param name 型の名前
        /// @param size 型のサイズ
        Type(const std::type_info& info, const std::string& name, size_t size);

        /// @brief コピーコンストラクタ
        /// @param other 
        Type(const Type& other) = default;

        /// @brief ムーブコンストラクタ
        /// @param other 
        Type(Type&& other) noexcept = default;

        /// @brief 型の名前を取得する関数
        /// @return 型の名前
        const std::string& GetName() const;

        /// @brief 
        /// @return 型のサイズ 
        size_t GetSize() const;

        /// @brief 型のタイプを比べる用のオペレータ
        /// @param other 比較対象
        /// @return 結果
        bool operator==(const Type& other) const;


        /// @brief 型のタイプを比べる用のオペレータ(不当演算子バージョン)
        /// @param other 比較対象
        /// @return 結果
        bool operator!=(const Type& other) const;
        

        static Type* FindByName(const std::string& name);

        template<typename T>
        static Type* FindByType() {
            std::type_index typeIndex(typeid(T));
            auto it = _typeMap.find(typeIndex);
            return it != _typeMap.end() ? it->second : nullptr;
        }

        /// @brief この型が算術系かを判定する
        /// @return 結果
        bool IsArithmetic();

        /// @brief この型がenumかを判定する
        /// @return 結果
        bool IsEnum();

        /// @brief この型が配列かを判定する
        /// @return 結果
        bool IsArray();

        /// @brief この型がクラス型かを判定する
        /// @return 結果
        bool IsClass();

        /// @brief このタイプ型のインスタンスを作成する関数
        /// @return インスタンス
        void* CreateInstanceByType();

    private:
        // 型情報からTypeBaseオブジェクトへのマッピングを保持するためのマップ
        static inline std::unordered_map<std::type_index, Type*> _typeMap;
        struct Type_Data* _data;
    };
}