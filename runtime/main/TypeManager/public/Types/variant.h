#pragma once
#include <type_traits>
#include <string>
#include <memory>

namespace HARMONY
{
    class Type;
    struct variant_data;
    class variant {
    public:
        // 汎用コンストラクタ
        template<typename T>
        variant(T& arg);

        variant& operator=(variant arg);

        bool operator==(const variant& arg) const;

        template<typename T>
        T convert()const;

        Type GetType()const;

        bool to_bool()const;

        int8_t to_int8()const;

        int16_t to_int16()const;

        int32_t to_int32()const;

        int64_t to_int64()const;

        uint8_t to_uint8()const;

        uint16_t to_uint16()const;

        uint32_t to_uint32()const;

        uint64_t to_uint64()const;

        float to_float()const;

        double to_double()const;

        std::string to_string()const;

    private:
        std::unique_ptr<variant_data>  _data;
    };
}
#include"Types/impls/variant_impl.h"