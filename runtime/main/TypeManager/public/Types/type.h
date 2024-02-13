#pragma once
#include <string>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <string>
#include <memory>

namespace HARMONY
{
    namespace DETAIL {
        struct Type_Data; // 前方宣言
        class ItemCreator;
    }
    // 型の種類を表す列挙体
    enum class TYPE_CATEGORY {
        TYPE_ARITHMETIC,//int,floatなどの算術型
        TYPE_ARRAY,     // 配列型
        TYPE_ENUM,      // Enum型
        TYPE_OBJECT,    // classやstructなどの規定値以外
        MAX
    };
    ///@brief 型情報を保存するクラス
    class TYPEMANAGER_API Type {
    public:
        Type();
        /// @brief 型の名前を取得する関数
        /// @return 型の名前
        /// 
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

        /// @brief 
        /// @tparam T 
        /// @return 
        template<typename T>
        static Type FindByType() {
            std::type_index typeIndex(typeid(T));
            return FindByTypeInfo(typeIndex);
        }

        /// @brief 型の名前からType型を探す関数
        /// @param name 型名
        /// @return Type
        static Type FindByName(const std::string& name);

        /// @brief 実行時型情報からTypeを探す関数
        /// @param info type_info
        /// @return Type型
        static Type FindByTypeInfo(const std::type_index& info);
    private:
        friend DETAIL::ItemCreator;
        std::shared_ptr<struct DETAIL::Type_Data> _data;
    };
}