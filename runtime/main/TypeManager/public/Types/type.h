#pragma once
#include <string>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <string>
#include <memory>

namespace HARMONY
{
    // 型の種類を表す列挙体
    enum class TYPE_CATEGORY {
        TYPE_ARITHMETIC,//int,floatなどの算術型
        TYPE_ARRAY,     // 配列型
        TYPE_ENUM,      // Enum型
        TYPE_STRING,    //文字列型
        TYPE_OBJECT,    // classやstructなどの規定値以外
        MAX
    };

    //TYPE_INT32,    // 32ビット整数値
    //    TYPE_FLOAT32,  // 32ビット浮動小数点
    //    TYPE_LONG64,   // 64ビット整数値
    //    TYPE_DOUBLE64, // 64ビット浮動小数点
    //    TYPE_STRING,   // 文字列型

    // 型情報を保存する基底クラス
    class TYPEMANAGER_API TypeBase {
    public:
        /// @brief 初回登録用のコンストラクタ
        /// @param info 型のtypeid情報
        /// @param name 型の名前
        /// @param size 型のサイズ
        TypeBase(const std::type_info& info, const std::string& name, size_t size);

        /// @brief 型を使用したコンストラクタ
        /// @tparam T 
        template<typename T>
        TypeBase(const std::string& name);

        /// @brief コピーコンストラクタ
        /// @param other 
        TypeBase(const TypeBase& other) = default;

        /// @brief ムーブコンストラクタ
        /// @param other 
        TypeBase(TypeBase&& other) noexcept = default;

        /// @brief 型の名前を取得する関数
        /// @return 型の名前
        const std::string& GetName() const {
            return _name;
        }

        /// @brief 
        /// @return 型のサイズ 
        size_t GetSize() const {
            return _size;
        }

        /// @brief 
        /// @return 型のTypeInfo
        std::type_index GetTypeInfo() const {
            return _info;
        }

        /// @brief 型のタイプを比べる用のオペレータ
        /// @param other 比較対象
        /// @return 結果
        bool operator==(const TypeBase& other) const {
            return (_info == other._info) &&
                (_name == other._name) &&
                (_size == other._size);
        }

        /// @brief 型のタイプを比べる用のオペレータ(不当演算子バージョン)
        /// @param other 比較対象
        /// @return 結果
        bool operator!=(const TypeBase& other) const
        {
            return !(*this == other);
        }

        static TypeBase* FindByName(const std::string& name) {
            for (auto type_bace : _typeMap)
            {
                if (name == type_bace.second->_name)
                {
                    return type_bace.second;
                }
            }
            return nullptr;
        }

        template<typename T>
        static TypeBase* FindByType() {
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
        template<typename T>
        TYPE_CATEGORY DetermineTypeCategory() {
            // 算術型のチェック
            if constexpr (std::is_arithmetic_v<T>) {
                return TYPE_CATEGORY::TYPE_ARITHMETIC;
            }
            // 列挙型のチェック
            else if constexpr (std::is_enum_v<T>) {
                return TYPE_CATEGORY::TYPE_ENUM;
            }
            // 配列型のチェック（固定長配列のみ）
            else if constexpr (std::is_array_v<T>) {
                return TYPE_CATEGORY::TYPE_ARRAY;
            }
            // 文字列型のチェック
            else if constexpr (std::is_same_v<T, std::string>) {
                // 文字列型を特別なケースとして扱う
                return TYPE_CATEGORY::TYPE_STRING;
            }
            // クラス型（structも含む）のチェック
            else if constexpr (std::is_class_v<T>) {
                return TYPE_CATEGORY::TYPE_OBJECT;
            }
            // どの条件にも当てはまらない場合のデフォルト
            else {
                return TYPE_CATEGORY::MAX; // あるいは、より適切なデフォルト値
            }
        }
        // 型情報からTypeBaseオブジェクトへのマッピングを保持するためのマップ
        static inline std::unordered_map<std::type_index, TypeBase*> _typeMap;
        TYPE_CATEGORY _typeCategory = TYPE_CATEGORY::MAX;//型のカテゴリー
        std::type_index _info; // 型情報
        std::string     _name; // 型の名前
        size_t          _size; // 型のサイズ
    };
    template<typename T>
    inline TypeBase::TypeBase(const std::string& name)
        :_name(name), _size(sizeof(T), _info(typeid(T))), _typeCategory(DetermineTypeCategory<T>())
    {
        // このオブジェクトを_typeListに登録
        _typeList[name] = this;
    };
}