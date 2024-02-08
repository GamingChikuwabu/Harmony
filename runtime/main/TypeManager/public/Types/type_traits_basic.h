#include <type_traits>
#include <cstdint> // uint32_t, int64_t, uint64_tなどのため

//=======================================================================================================
// 特殊化用の定義
//=======================================================================================================
// is_intの定義
template<typename T>
struct is_int : std::false_type {};
template<typename T>
struct is_uint : std::false_type {};
// is_longの定義
template<typename T>
struct is_long : std::false_type {};
// is_longlongの定義
template<typename T>
struct is_longlong : std::false_type {};
// is_ulongの定義
template<typename T>
struct is_ulong : std::false_type {};
// is_ulonglongの定義
template<typename T>
struct is_ulonglong : std::false_type {};
// is_floatの定義
template<typename T>
struct is_float : std::false_type {};
// is_doubleの定義
template<typename T>
struct is_double : std::false_type {};

template<typename T>
struct remove_pointer {
    using type = T;
}; 

template<typename T>
struct remove_pointer<T*> {
    using type = T;
};

//=======================================================================================================
// 特殊化の定義
//=======================================================================================================
// int型に対する特殊化
template<>
struct is_int<int32_t> : std::true_type {};

// unsigned int型に対する特殊化
template<>
struct is_uint<uint32_t> : std::true_type {};

template<>
struct is_float<float> : std::true_type {};

template<>
struct is_double<double> : std::true_type {};

// int64_tおよびuint64_tに対する特殊化
template<>
struct is_int<int64_t> : std::true_type {};
template<>
struct is_uint<uint64_t> : std::true_type {};

