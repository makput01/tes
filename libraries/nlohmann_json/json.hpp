//     __ _____ _____ _____
//  __|  |   __|     |   | |  JSON for Modern C++
// |  |  |__   |  |  | | | |  version 3.11.3
// |_____|_____|_____|_|___|  https://github.com/nlohmann/json
//
// SPDX-FileCopyrightText: 2013-2023 Niels Lohmann <https://nlohmann.me>
// SPDX-License-Identifier: MIT

#ifndef INCLUDE_NLOHMANN_JSON_HPP_
#define INCLUDE_NLOHMANN_JSON_HPP_

#include <algorithm> // all_of, find, for_each
#include <cstddef> // nullptr_t, ptrdiff_t, size_t
#include <functional> // hash, less
#include <initializer_list> // initializer_list
#ifndef JSON_NO_IO
    #include <iosfwd> // istream, ostream
#endif  // JSON_NO_IO
#include <iterator> // random_access_iterator_tag
#include <memory> // unique_ptr
#include <string> // string, stoi, to_string
#include <utility> // declval, forward, move, pair, swap
#include <vector> // vector

// #include <nlohmann/adl_serializer.hpp>
//     __ _____ _____ _____
//  __|  |   __|     |   | |  JSON for Modern C++
// |  |  |__   |  |  | | | |  version 3.11.3
// |_____|_____|_____|_|___|  https://github.com/nlohmann/json
//
// SPDX-FileCopyrightText: 2013-2023 Niels Lohmann <https://nlohmann.me>
// SPDX-License-Identifier: MIT



#include <utility>

// #include <nlohmann/detail/abi_macros.hpp>
//     __ _____ _____ _____
//  __|  |   __|     |   | |  JSON for Modern C++
// |  |  |__   |  |  | | | |  version 3.11.3
// |_____|_____|_____|_|___|  https://github.com/nlohmann/json
//
// SPDX-FileCopyrightText: 2013-2023 Niels Lohmann <https://nlohmann.me>
// SPDX-License-Identifier: MIT



// This file contains all macro definitions affecting or depending on the ABI

#ifndef JSON_SKIP_LIBRARY_VERSION_CHECK
    #if defined(NLOHMANN_JSON_VERSION_MAJOR) && defined(NLOHMANN_JSON_VERSION_MINOR) && defined(NLOHMANN_JSON_VERSION_PATCH)
        #if NLOHMANN_JSON_VERSION_MAJOR != 3 || NLOHMANN_JSON_VERSION_MINOR != 11 || NLOHMANN_JSON_VERSION_PATCH != 3
            #warning "Already included a different version of the library!"
        #endif
    #endif
#endif

#define NLOHMANN_JSON_VERSION_MAJOR 3
#define NLOHMANN_JSON_VERSION_MINOR 11
#define NLOHMANN_JSON_VERSION_PATCH 3

#ifndef JSON_DIAGNOSTICS
    #define JSON_DIAGNOSTICS 0
#endif

#ifndef JSON_USE_LEGACY_DISCARDED_VALUE_COMPARISON
    #define JSON_USE_LEGACY_DISCARDED_VALUE_COMPARISON 0
#endif

#if JSON_DIAGNOSTICS
    #define NLOHMANN_JSON_ABI_TAG_DIAGNOSTICS _diag
#else
    #define NLOHMANN_JSON_ABI_TAG_DIAGNOSTICS
#endif

#if JSON_USE_LEGACY_DISCARDED_VALUE_COMPARISON
    #define NLOHMANN_JSON_ABI_TAG_LEGACY_DISCARDED_VALUE_COMPARISON _ldvcmp
#else
    #define NLOHMANN_JSON_ABI_TAG_LEGACY_DISCARDED_VALUE_COMPARISON
#endif

#ifndef NLOHMANN_JSON_NAMESPACE_NO_VERSION
    #define NLOHMANN_JSON_NAMESPACE_NO_VERSION 0
#endif

// Construct the namespace ABI tags component
#define NLOHMANN_JSON_ABI_TAGS_CONCAT_EX(a, b) json_abi ## a ## b
#define NLOHMANN_JSON_ABI_TAGS_CONCAT(a, b) \
    NLOHMANN_JSON_ABI_TAGS_CONCAT_EX(a, b)

#define NLOHMANN_JSON_ABI_TAGS                                       \
    NLOHMANN_JSON_ABI_TAGS_CONCAT(                                   \
            NLOHMANN_JSON_ABI_TAG_DIAGNOSTICS,                       \
            NLOHMANN_JSON_ABI_TAG_LEGACY_DISCARDED_VALUE_COMPARISON)

// Construct the namespace version component
#define NLOHMANN_JSON_NAMESPACE_VERSION_CONCAT_EX(major, minor, patch) \
    _v ## major ## _ ## minor ## _ ## patch
#define NLOHMANN_JSON_NAMESPACE_VERSION_CONCAT(major, minor, patch) \
    NLOHMANN_JSON_NAMESPACE_VERSION_CONCAT_EX(major, minor, patch)

#if NLOHMANN_JSON_NAMESPACE_NO_VERSION
#define NLOHMANN_JSON_NAMESPACE_VERSION
#else
#define NLOHMANN_JSON_NAMESPACE_VERSION                                 \
    NLOHMANN_JSON_NAMESPACE_VERSION_CONCAT(NLOHMANN_JSON_VERSION_MAJOR, \
                                           NLOHMANN_JSON_VERSION_MINOR, \
                                           NLOHMANN_JSON_VERSION_PATCH)
#endif

// Combine namespace components
#define NLOHMANN_JSON_NAMESPACE_CONCAT_EX(a, b) a ## b
#define NLOHMANN_JSON_NAMESPACE_CONCAT(a, b) \
    NLOHMANN_JSON_NAMESPACE_CONCAT_EX(a, b)

#ifndef NLOHMANN_JSON_NAMESPACE
#define NLOHMANN_JSON_NAMESPACE               \
    nlohmann::NLOHMANN_JSON_NAMESPACE_CONCAT( \
            NLOHMANN_JSON_ABI_TAGS,           \
            NLOHMANN_JSON_NAMESPACE_VERSION)
#endif

#ifndef NLOHMANN_JSON_NAMESPACE_BEGIN
#define NLOHMANN_JSON_NAMESPACE_BEGIN                \
    namespace nlohmann                               \
    {                                                \
    inline namespace NLOHMANN_JSON_NAMESPACE_CONCAT( \
                NLOHMANN_JSON_ABI_TAGS,              \
                NLOHMANN_JSON_NAMESPACE_VERSION)     \
    {
#endif

#ifndef NLOHMANN_JSON_NAMESPACE_END
#define NLOHMANN_JSON_NAMESPACE_END                                     \
    }  /* namespace (inline namespace) */ \
    }  // namespace nlohmann
#endif

// #include <nlohmann/detail/conversions/from_json.hpp>
//     __ _____ _____ _____
//  __|  |   __|     |   | |  JSON for Modern C++
// |  |  |__   |  |  | | | |  version 3.11.3
// |_____|_____|_____|_|___|  https://github.com/nlohmann/json
//
// SPDX-FileCopyrightText: 2013-2023 Niels Lohmann <https://nlohmann.me>
// SPDX-License-Identifier: MIT



#include <algorithm> // transform
#include <array> // array
#include <forward_list> // forward_list
#include <iterator> // inserter, front_inserter, end
#include <map> // map
#include <string> // string
#include <tuple> // tuple, make_tuple
#include <type_traits> // is_arithmetic, is_same, is_enum, underlying_type, is_convertible
#include <unordered_map> // unordered_map
#include <utility> // pair, declval
#include <valarray> // valarray

// #include <nlohmann/detail/exceptions.hpp>
//     __ _____ _____ _____
//  __|  |   __|     |   | |  JSON for Modern C++
// |  |  |__   |  |  | | | |  version 3.11.3
// |_____|_____|_____|_|___|  https://github.com/nlohmann/json
//
// SPDX-FileCopyrightText: 2013-2023 Niels Lohmann <https://nlohmann.me>
// SPDX-License-Identifier: MIT



#include <cstddef> // nullptr_t
#include <exception> // exception
#include <stdexcept> // runtime_error
#include <string> // to_string
#include <vector> // vector

// #include <nlohmann/detail/value_t.hpp>
//     __ _____ _____ _____
//  __|  |   __|     |   | |  JSON for Modern C++
// |  |  |__   |  |  | | | |  version 3.11.3
// |_____|_____|_____|_|___|  https://github.com/nlohmann/json
//
// SPDX-FileCopyrightText: 2013-2023 Niels Lohmann <https://nlohmann.me>
// SPDX-License-Identifier: MIT



#include <array> // array
#include <cstddef> // size_t
#include <cstdint> // uint8_t
#include <string> // string

// #include <nlohmann/detail/macro_scope.hpp>
//     __ _____ _____ _____
//  __|  |   __|     |   | |  JSON for Modern C++
// |  |  |__   |  |  | | | |  version 3.11.3
// |_____|_____|_____|_|___|  https://github.com/nlohmann/json
//
// SPDX-FileCopyrightText: 2013-2023 Niels Lohmann <https://nlohmann.me>
// SPDX-License-Identifier: MIT



// This file contains all internal macro definitions (except those affecting ABI)
// You MUST include macro_unscope.hpp at the end of json.hpp to undef all of them

// #include <nlohmann/detail/abi_macros.hpp>


// exclude unsupported compilers
#if !defined(JSON_SKIP_UNSUPPORTED_COMPILER_CHECK)
    #if defined(__clang__)
        #if (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__) < 30400
            #error "unsupported Clang version - see https://github.com/nlohmann/json#supported-compilers"
        #endif
    #elif defined(__GNUC__) && !(defined(__ICC) || defined(__INTEL_COMPILER))
        #if (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) < 40800
            #error "unsupported GCC version - see https://github.com/nlohmann/json#supported-compilers"
        #endif
    #endif
#endif

// C++ language standard detection
// if the user manually specified the used C++ version, this is skipped
#if !defined(JSON_HAS_CPP_11)
    #if (defined(__cplusplus) && __cplusplus >= 201103L) || (defined(_MSC_VER) && _MSC_VER >= 1900)
        #define JSON_HAS_CPP_11 1
    #else
        #define JSON_HAS_CPP_11 0
    #endif
#endif

#if !defined(JSON_HAS_CPP_14)
    #if (defined(__cplusplus) && __cplusplus >= 201402L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 201402L)
        #define JSON_HAS_CPP_14 1
    #else
        #define JSON_HAS_CPP_14 0
    #endif
#endif

#if !defined(JSON_HAS_CPP_17)
    #if (defined(__cplusplus) && __cplusplus >= 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)
        #define JSON_HAS_CPP_17 1
    #else
        #define JSON_HAS_CPP_17 0
    #endif
#endif

#if !defined(JSON_HAS_CPP_20)
    #if (defined(__cplusplus) && __cplusplus >= 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
        #define JSON_HAS_CPP_20 1
    #else
        #define JSON_HAS_CPP_20 0
    #endif
#endif

#if !defined(JSON_HAS_FILESYSTEM) && !defined(JSON_HAS_EXPERIMENTAL_FILESYSTEM)
    #ifdef __has_include
        #if __has_include(<filesystem>)
            #define JSON_HAS_FILESYSTEM 1
        #elif __has_include(<experimental/filesystem>)
            #define JSON_HAS_EXPERIMENTAL_FILESYSTEM 1
        #endif
    #endif
#endif

#if JSON_HAS_CPP_17
    // std::filesystem does not work on MinGW GCC 8: https://sourceforge.net/p/mingw-w64/bugs/737/
    #if defined(__MINGW32__) && defined(__GNUC__) && __GNUC__ == 8
        #undef JSON_HAS_FILESYSTEM
        #undef JSON_HAS_EXPERIMENTAL_FILESYSTEM
    #endif
    // no filesystem support before GCC 8: https://en.cppreference.com/w/cpp/compiler_support
    #if defined(__GNUC__) && !defined(__clang__) && __GNUC__ < 8
        #undef JSON_HAS_FILESYSTEM
        #undef JSON_HAS_EXPERIMENTAL_FILESYSTEM
    #endif
    // no filesystem support before Clang 7: https://en.cppreference.com/w/cpp/compiler_support
    #if defined(__clang_major__) && __clang_major__ < 7
        #undef JSON_HAS_FILESYSTEM
        #undef JSON_HAS_EXPERIMENTAL_FILESYSTEM
    #endif
    // no filesystem support before MSVC 19.14: https://en.cppreference.com/w/cpp/compiler_support
    #if defined(_MSC_VER) && _MSC_VER < 1914
        #undef JSON_HAS_FILESYSTEM
        #undef JSON_HAS_EXPERIMENTAL_FILESYSTEM
    #endif
    // no filesystem support before iOS 13
    #if defined(__IPHONE_OS_VERSION_MIN_REQUIRED) && __IPHONE_OS_VERSION_MIN_REQUIRED < 130000
        #undef JSON_HAS_FILESYSTEM
        #undef JSON_HAS_EXPERIMENTAL_FILESYSTEM
    #endif
    // no filesystem support before macOS Catalina
    #if defined(__MAC_OS_X_VERSION_MIN_REQUIRED) && __MAC_OS_X_VERSION_MIN_REQUIRED < 101500
        #undef JSON_HAS_FILESYSTEM
        #undef JSON_HAS_EXPERIMENTAL_FILESYSTEM
    #endif
#endif

#ifndef JSON_HAS_EXPERIMENTAL_FILESYSTEM
    #define JSON_HAS_EXPERIMENTAL_FILESYSTEM 0
#endif

#ifndef JSON_HAS_FILESYSTEM
    #define JSON_HAS_FILESYSTEM 0
#endif

#ifdef JSON_HAS_CPP_17
    #define JSON_INLINE_VARIABLE inline
#else
    #define JSON_INLINE_VARIABLE
#endif

#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wdocumentation"
    #pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif

// allow disabling exceptions
#if (defined(__cpp_exceptions) || defined(__EXCEPTIONS) || defined(_CPPUNWIND)) && !defined(JSON_NOEXCEPTION)
    #define JSON_THROW(exception) throw exception
    #define JSON_TRY try
    #define JSON_CATCH(exception) catch(exception)
    #define JSON_INTERNAL_CATCH(exception) catch(exception)
#else
    #include <cstdlib>
    #define JSON_THROW(exception) std::abort()
    #define JSON_TRY if(true)
    #define JSON_CATCH(exception) if(false)
    #define JSON_INTERNAL_CATCH(exception) if(false)
#endif

// override exception macros
#if defined(JSON_THROW_USER)
    #undef JSON_THROW
    #define JSON_THROW JSON_THROW_USER
#endif
#if defined(JSON_TRY_USER)
    #undef JSON_TRY
    #define JSON_TRY JSON_TRY_USER
#endif
#if defined(JSON_CATCH_USER)
    #undef JSON_CATCH
    #define JSON_CATCH JSON_CATCH_USER
    #undef JSON_INTERNAL_CATCH
    #define JSON_INTERNAL_CATCH JSON_CATCH_USER
#endif
#if defined(JSON_INTERNAL_CATCH_USER)
    #undef JSON_INTERNAL_CATCH
    #define JSON_INTERNAL_CATCH JSON_INTERNAL_CATCH_USER
#endif

// allow overriding assert
#if !defined(JSON_ASSERT)
    #include <cassert> // assert
    #define JSON_ASSERT(x) assert(x)
#endif

// allow accessing some private functions (needed by the test suite)
#if defined(JSON_TESTS_PRIVATE)
    #define JSON_PRIVATE_UNLESS_TESTED public
#else
    #define JSON_PRIVATE_UNLESS_TESTED private
#endif

/*!
@brief macro to briefly define a mapping between an enum and JSON
@def NLOHMANN_JSON_SERIALIZE_ENUM
@since version 3.4.0
*/
#define NLOHMANN_JSON_SERIALIZE_ENUM(ENUM_TYPE, ...)                                           \
    template<typename BasicJsonType>                                                           \
    inline void to_json(BasicJsonType& j, const ENUM_TYPE& e)                                  \
    {                                                                                          \
        static_assert(std::is_enum<ENUM_TYPE>::value, #ENUM_TYPE " must be an enum!");          \
        static const std::pair<ENUM_TYPE, BasicJsonType> m[] = __VA_ARGS__;                     \
        auto it = std::find_if(std::begin(m), std::end(m),                                      \
                               [e](const std::pair<ENUM_TYPE, BasicJsonType>& ej_pair) -> bool  \
        {                                                                                      \
            return ej_pair.first == e;                                                         \
        });                                                                                    \
        j = ((it != std::end(m)) ? it : std::begin(m))->second;                                 \
    }                                                                                          \
    template<typename BasicJsonType>                                                           \
    inline void from_json(const BasicJsonType& j, ENUM_TYPE& e)                                \
    {                                                                                          \
        static_assert(std::is_enum<ENUM_TYPE>::value, #ENUM_TYPE " must be an enum!");          \
        static const std::pair<ENUM_TYPE, BasicJsonType> m[] = __VA_ARGS__;                     \
        auto it = std::find_if(std::begin(m), std::end(m),                                      \
                               [&j](const std::pair<ENUM_TYPE, BasicJsonType>& ej_pair) -> bool \
        {                                                                                      \
            return ej_pair.second == j;                                                        \
        });                                                                                    \
        e = ((it != std::end(m)) ? it : std::begin(m))->first;                                  \
    }

// Ugly macros to avoid uglier copy-paste when specializing basic_json. They
// may be removed in the future once the class is split.

#define NLOHMANN_BASIC_JSON_TPL_DECLARATION                                \
    template<template<typename, typename, typename...> class ObjectType,   \
             template<typename, typename...> class ArrayType,              \
             class StringType, class BooleanType, class NumberIntegerType, \
             class NumberUnsignedType, class NumberFloatType,              \
             template<typename> class AllocatorType,                       \
             template<typename, typename = void> class JSONSerializer,     \
             class BinaryType,                                             \
             class CustomBaseClass>

#define NLOHMANN_BASIC_JSON_TPL                                            \
    basic_json<ObjectType, ArrayType, StringType, BooleanType,             \
    NumberIntegerType, NumberUnsignedType, NumberFloatType,                \
    AllocatorType, JSONSerializer, BinaryType, CustomBaseClass>

// Macros to simplify conversion from/to types

#define NLOHMANN_JSON_EXPAND( x ) x
#define NLOHMANN_JSON_GET_MACRO(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, NAME,...) NAME
#define NLOHMANN_JSON_PASTE(...) NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_GET_MACRO(__VA_ARGS__, \
        NLOHMANN_JSON_PASTE64, \
        NLOHMANN_JSON_PASTE63, \
        NLOHMANN_JSON_PASTE62, \
        NLOHMANN_JSON_PASTE61, \
        NLOHMANN_JSON_PASTE60, \
        NLOHMANN_JSON_PASTE59, \
        NLOHMANN_JSON_PASTE58, \
        NLOHMANN_JSON_PASTE57, \
        NLOHMANN_JSON_PASTE56, \
        NLOHMANN_JSON_PASTE55, \
        NLOHMANN_JSON_PASTE54, \
        NLOHMANN_JSON_PASTE53, \
        NLOHMANN_JSON_PASTE52, \
        NLOHMANN_JSON_PASTE51, \
        NLOHMANN_JSON_PASTE50, \
        NLOHMANN_JSON_PASTE49, \
        NLOHMANN_JSON_PASTE48, \
        NLOHMANN_JSON_PASTE47, \
        NLOHMANN_JSON_PASTE46, \
        NLOHMANN_JSON_PASTE45, \
        NLOHMANN_JSON_PASTE44, \
        NLOHMANN_JSON_PASTE43, \
        NLOHMANN_JSON_PASTE42, \
        NLOHMANN_JSON_PASTE41, \
        NLOHMANN_JSON_PASTE40, \
        NLOHMANN_JSON_PASTE39, \
        NLOHMANN_JSON_PASTE38, \
        NLOHMANN_JSON_PASTE37, \
        NLOHMANN_JSON_PASTE36, \
        NLOHMANN_JSON_PASTE35, \
        NLOHMANN_JSON_PASTE34, \
        NLOHMANN_JSON_PASTE33, \
        NLOHMANN_JSON_PASTE32, \
        NLOHMANN_JSON_PASTE31, \
        NLOHMANN_JSON_PASTE30, \
        NLOHMANN_JSON_PASTE29, \
        NLOHMANN_JSON_PASTE28, \
        NLOHMANN_JSON_PASTE27, \
        NLOHMANN_JSON_PASTE26, \
        NLOHMANN_JSON_PASTE25, \
        NLOHMANN_JSON_PASTE24, \
        NLOHMANN_JSON_PASTE23, \
        NLOHMANN_JSON_PASTE22, \
        NLOHMANN_JSON_PASTE21, \
        NLOHMANN_JSON_PASTE20, \
        NLOHMANN_JSON_PASTE19, \
        NLOHMANN_JSON_PASTE18, \
        NLOHMANN_JSON_PASTE17, \
        NLOHMANN_JSON_PASTE16, \
        NLOHMANN_JSON_PASTE15, \
        NLOHMANN_JSON_PASTE14, \
        NLOHMANN_JSON_PASTE13, \
        NLOHMANN_JSON_PASTE12, \
        NLOHMANN_JSON_PASTE11, \
        NLOHMANN_JSON_PASTE10, \
        NLOHMANN_JSON_PASTE9, \
        NLOHMANN_JSON_PASTE8, \
        NLOHMANN_JSON_PASTE7, \
        NLOHMANN_JSON_PASTE6, \
        NLOHMANN_JSON_PASTE5, \
        NLOHMANN_JSON_PASTE4, \
        NLOHMANN_JSON_PASTE3, \
        NLOHMANN_JSON_PASTE2, \
        NLOHMANN_JSON_PASTE1)(__VA_ARGS__))
#define NLOHMANN_JSON_PASTE2(func, v1) func(v1)
#define NLOHMANN_JSON_PASTE3(func, v1, v2) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE2(func, v2)
#define NLOHMANN_JSON_PASTE4(func, v1, v2, v3) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE3(func, v2, v3)
#define NLOHMANN_JSON_PASTE5(func, v1, v2, v3, v4) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE4(func, v2, v3, v4)
#define NLOHMANN_JSON_PASTE6(func, v1, v2, v3, v4, v5) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE5(func, v2, v3, v4, v5)
#define NLOHMANN_JSON_PASTE7(func, v1, v2, v3, v4, v5, v6) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE6(func, v2, v3, v4, v5, v6)
#define NLOHMANN_JSON_PASTE8(func, v1, v2, v3, v4, v5, v6, v7) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE7(func, v2, v3, v4, v5, v6, v7)
#define NLOHMANN_JSON_PASTE9(func, v1, v2, v3, v4, v5, v6, v7, v8) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE8(func, v2, v3, v4, v5, v6, v7, v8)
#define NLOHMANN_JSON_PASTE10(func, v1, v2, v3, v4, v5, v6, v7, v8, v9) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE9(func, v2, v3, v4, v5, v6, v7, v8, v9)
#define NLOHMANN_JSON_PASTE11(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE10(func, v2, v3, v4, v5, v6, v7, v8, v9, v10)
#define NLOHMANN_JSON_PASTE12(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE11(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11)
#define NLOHMANN_JSON_PASTE13(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE12(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12)
#define NLOHMANN_JSON_PASTE14(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE13(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13)
#define NLOHMANN_JSON_PASTE15(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE14(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14)
#define NLOHMANN_JSON_PASTE16(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE15(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15)
#define NLOHMANN_JSON_PASTE17(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE16(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16)
#define NLOHMANN_JSON_PASTE18(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE17(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17)
#define NLOHMANN_JSON_PASTE19(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE18(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18)
#define NLOHMANN_JSON_PASTE20(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE19(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19)
#define NLOHMANN_JSON_PASTE21(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE20(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20)
#define NLOHMANN_JSON_PASTE22(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE21(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21)
#define NLOHMANN_JSON_PASTE23(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE22(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22)
#define NLOHMANN_JSON_PASTE24(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE23(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23)
#define NLOHMANN_JSON_PASTE25(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE24(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24)
#define NLOHMANN_JSON_PASTE26(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE25(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25)
#define NLOHMANN_JSON_PASTE27(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE26(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26)
#define NLOHMANN_JSON_PASTE28(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE27(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27)
#define NLOHMANN_JSON_PASTE29(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE28(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28)
#define NLOHMANN_JSON_PASTE30(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE29(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29)
#define NLOHMANN_JSON_PASTE31(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE30(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30)
#define NLOHMANN_JSON_PASTE32(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE31(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31)
#define NLOHMANN_JSON_PASTE33(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE32(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32)
#define NLOHMANN_JSON_PASTE34(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE33(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33)
#define NLOHMANN_JSON_PASTE35(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE34(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34)
#define NLOHMANN_JSON_PASTE36(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE35(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35)
#define NLOHMANN_JSON_PASTE37(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE36(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36)
#define NLOHMANN_JSON_PASTE38(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE37(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37)
#define NLOHMANN_JSON_PASTE39(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE38(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38)
#define NLOHMANN_JSON_PASTE40(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE39(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39)
#define NLOHMANN_JSON_PASTE41(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE40(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40)
#define NLOHMANN_JSON_PASTE42(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE41(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41)
#define NLOHMANN_JSON_PASTE43(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE42(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42)
#define NLOHMANN_JSON_PASTE44(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE43(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43)
#define NLOHMANN_JSON_PASTE45(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE44(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44)
#define NLOHMANN_JSON_PASTE46(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE45(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45)
#define NLOHMANN_JSON_PASTE47(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE46(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46)
#define NLOHMANN_JSON_PASTE48(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE47(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47)
#define NLOHMANN_JSON_PASTE49(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE48(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48)
#define NLOHMANN_JSON_PASTE50(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE49(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49)
#define NLOHMANN_JSON_PASTE51(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE50(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50)
#define NLOHMANN_JSON_PASTE52(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE51(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51)
#define NLOHMANN_JSON_PASTE53(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE52(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52)
#define NLOHMANN_JSON_PASTE54(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE53(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53)
#define NLOHMANN_JSON_PASTE55(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE54(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54)
#define NLOHMANN_JSON_PASTE56(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE55(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55)
#define NLOHMANN_JSON_PASTE57(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE56(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56)
#define NLOHMANN_JSON_PASTE58(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE57(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57)
#define NLOHMANN_JSON_PASTE59(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE58(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58)
#define NLOHMANN_JSON_PASTE60(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE59(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59)
#define NLOHMANN_JSON_PASTE61(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE60(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60)
#define NLOHMANN_JSON_PASTE62(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE61(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61)
#define NLOHMANN_JSON_PASTE63(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61, v62) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE62(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61, v62)
#define NLOHMANN_JSON_PASTE64(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61, v62, v63) NLOHMANN_JSON_PASTE2(func, v1) NLOHMANN_JSON_PASTE63(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61, v62, v63)

#define NLOHMANN_JSON_TO(v1) nlohmann_json_j[#v1] = nlohmann_json_t.v1;
#define NLOHMANN_JSON_FROM(v1) nlohmann_json_j.at(#v1).get_to(nlohmann_json_t.v1);
#define NLOHMANN_JSON_FROM_WITH_DEFAULT(v1) nlohmann_json_t.v1 = nlohmann_json_j.value(#v1, nlohmann_json_default_obj.v1);

/*!
@brief macro
@def NLOHMANN_DEFINE_TYPE_INTRUSIVE
@since version 3.9.0
@sa https://json.nlohmann.me/api/macros/nlohmann_define_type_intrusive/
*/
#define NLOHMANN_DEFINE_TYPE_INTRUSIVE(Type, ...)  \
    friend void to_json(nlohmann::json& nlohmann_json_j, const Type& nlohmann_json_t) { NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_TO, __VA_ARGS__)) } \
    friend void from_json(const nlohmann::json& nlohmann_json_j, Type& nlohmann_json_t) { NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_FROM, __VA_ARGS__)) }

/*!
@brief macro
@def NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT
@since version 3.11.0
@sa https://json.nlohmann.me/api/macros/nlohmann_define_type_intrusive/
*/
#define NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Type, ...)  \
    friend void to_json(nlohmann::json& nlohmann_json_j, const Type& nlohmann_json_t) { NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_TO, __VA_ARGS__)) } \
    friend void from_json(const nlohmann::json& nlohmann_json_j, Type& nlohmann_json_t) { const Type nlohmann_json_default_obj{}; NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_FROM_WITH_DEFAULT, __VA_ARGS__)) }

/*!
@brief macro
@def NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE
@since version 3.9.0
@sa https://json.nlohmann.me/api/macros/nlohmann_define_type_non_intrusive/
*/
#define NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Type, ...)  \
    inline void to_json(nlohmann::json& nlohmann_json_j, const Type& nlohmann_json_t) { NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_TO, __VA_ARGS__)) } \
    inline void from_json(const nlohmann::json& nlohmann_json_j, Type& nlohmann_json_t) { NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_FROM, __VA_ARGS__)) }

/*!
@brief macro
@def NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT
@since version 3.11.0
@sa https://json.nlohmann.me/api/macros/nlohmann_define_type_non_intrusive/
*/
#define NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Type, ...)  \
    inline void to_json(nlohmann::json& nlohmann_json_j, const Type& nlohmann_json_t) { NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_TO, __VA_ARGS__)) } \
    inline void from_json(const nlohmann::json& nlohmann_json_j, Type& nlohmann_json_t) { const Type nlohmann_json_default_obj{}; NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_FROM_WITH_DEFAULT, __VA_ARGS__)) }

// inspired from https://stackoverflow.com/a/26745591
// allows calling any std function as if (e.g., with begin):
// using std::begin; begin(x);
//
// it allows using the detected idiom to retrieve the return type
// of such an expression
#define NLOHMANN_CAN_CALL_STD_FUNC_IMPL(std_name) \
    namespace detail { \
    using std::std_name; \
    \
    template<typename... T> \
    using result_of_##std_name = decltype(std_name(std::declval<T>()...)); \
    } \
    \
    namespace detail2 { \
    struct std_name##_tag {}; \
    \
    template<typename... T> \
    std_name##_tag std_name(T&&...); \
    \
    template<typename... T> \
    using result_of_##std_name = decltype(std_name(std::declval<T>()...)); \
    \
    template<typename... T> \
    struct would_call_std_##std_name { \
        static constexpr auto const value = ::nlohmann::detail:: \
                                            is_detected_exact<std_name##_tag, result_of_##std_name, T...>::value; \
    }; \
    } /* namespace detail2 */ \
    \
    template<typename... T> \
    struct would_call_std_##std_name : detail2::would_call_std_##std_name<T...> \
    {}

#ifndef JSON_USE_IMPLICIT_CONVERSIONS
    #define JSON_USE_IMPLICIT_CONVERSIONS 1
#endif

#if JSON_USE_IMPLICIT_CONVERSIONS
    #define JSON_EXPLICIT
#else
    #define JSON_EXPLICIT explicit
#endif

#ifndef JSON_DISABLE_ENUM_SERIALIZATION
    #define JSON_DISABLE_ENUM_SERIALIZATION 0
#endif

#ifndef JSON_USE_GLOBAL_UDLS
    #define JSON_USE_GLOBAL_UDLS 1
#endif

NLOHMANN_JSON_NAMESPACE_BEGIN
namespace detail
{

///////////////////////////
// JSON type enumeration //
///////////////////////////

/*!
@brief the JSON type enumeration

This enumeration collects the different JSON types. It is internally used to
distinguish the stored values, and the functions @ref basic_json::is_null(),
@ref basic_json::is_object(), @ref basic_json::is_array(),
@ref basic_json::is_string(), @ref basic_json::is_boolean(),
@ref basic_json::is_number() (with @ref basic_json::is_number_integer(),
@ref basic_json::is_number_unsigned(), and @ref basic_json::is_number_float()),
@ref basic_json::is_discarded(), @ref basic_json::is_primitive(), and
@ref basic_json::is_structured() rely on it.

@note There are three enumeration entries (number_integer, number_unsigned, and
number_float), because the library distinguishes these three types for numbers:
@ref basic_json::number_unsigned_t is used for unsigned integers,
@ref basic_json::number_integer_t is used for signed integers, and
@ref basic_json::number_float_t is used for floating-point numbers or to
approximate integers which do not fit in the limits of their respective type.

@sa see @ref basic_json::basic_json(const value_t value_type) -- create a JSON
value with the default value for a given type

@since version 1.0.0
*/
enum class value_t : std::uint8_t
{
    null,             ///< null value
    object,           ///< object (unordered set of name/value pairs)
    array,            ///< array (ordered collection of values)
    string,           ///< string value
    boolean,          ///< boolean value
    number_integer,   ///< number value (signed integer)
    number_unsigned,  ///< number value (unsigned integer)
    number_float,     ///< number value (floating-point)
    binary,           ///< binary array (ordered collection of bytes)
    discarded         ///< discarded by the parser callback function
};

/*!
@brief comparison operator for JSON types

Returns an ordering that is similar to Python:
- order: null < boolean < number < object < array < string < binary
- furthermore, each type is not smaller than itself
- discarded values are not comparable
- binary is represented as a b"" string in python and directly comparable to a
  string; however, making a binary array directly comparable with a string would
  be surprising behavior in a JSON file.

@since version 1.0.0
*/
inline bool operator<(const value_t lhs, const value_t rhs) noexcept
{
    static constexpr std::array<std::uint8_t, 9> order = {{
            0 /* null */, 3 /* object */, 4 /* array */, 5 /* string */,
            1 /* boolean */, 2 /* integer */, 2 /* unsigned */, 2 /* float */,
            6 /* binary */
        }
    };

    const auto l_index = static_cast<std::size_t>(lhs);
    const auto r_index = static_cast<std::size_t>(rhs);

    return l_index < order.size() && r_index < order.size() && order[l_index] < order[r_index];
}

}  // namespace detail
NLOHMANN_JSON_NAMESPACE_END

// #include <nlohmann/detail/string_escape.hpp>
//     __ _____ _____ _____
//  __|  |   __|     |   | |  JSON for Modern C++
// |  |  |__   |  |  | | | |  version 3.11.3
// |_____|_____|_____|_|___|  https://github.com/nlohmann/json
//
// SPDX-FileCopyrightText: 2013-2023 Niels Lohmann <https://nlohmann.me>
// SPDX-License-Identifier: MIT



// #include <nlohmann/detail/abi_macros.hpp>


NLOHMANN_JSON_NAMESPACE_BEGIN
namespace detail
{

/*!
@brief replace all occurrences of a substring by another string

@param[in,out] s  the string to manipulate; changed so that all
               occurrences of @a f are replaced with @a t
@param[in]     f  the substring to replace with @a t
@param[in]     t  the string to replace @a f

@pre The search string @a f must not be empty. **This precondition is
enforced with an assertion.**

@since version 2.0.0
*/
template<typename StringType>
inline void replace_substring(StringType& s, const StringType& f,
                              const StringType& t)
{
    JSON_ASSERT(!f.empty());
    for (auto pos = s.find(f);                // find the first occurrence of f
            pos != StringType::npos;          // make sure f was found
            s.replace(pos, f.size(), t),      // replace with t, and
            pos = s.find(f, pos + t.size()))  // find the next occurrence of f
    {}
}

/*!
 * @brief string escaping as described in RFC 6901 (Sect. 4)
 * @param[in] s string to escape
 * @return    escaped string
 *
 * Note the order of escaping "~" to "~0" and "/" to "~1" is important.
 */
template<typename StringType>
inline StringType escape(StringType s)
{
    replace_substring(s, StringType{"~"}, StringType{"~0"});
    replace_substring(s, StringType{"/"}, StringType{"~1"});
    return s;
}

/*!
 * @brief string unescaping as described in RFC 6901 (Sect. 4)
 * @param[in] s string to unescape
 * @return    unescaped string
 *
 * Note the order of escaping "~1" to "/" and "~0" to "~" is important.
 */
template<typename StringType>
inline void unescape(StringType& s)
{
    replace_substring(s, StringType{"~1"}, StringType{"/"});
    replace_substring(s, StringType{"~0"}, StringType{"~"});
}

}  // namespace detail
NLOHMANN_JSON_NAMESPACE_END

// #include <nlohmann/detail/input/position_t.hpp>
//     __ _____ _____ _____
//  __|  |   __|     |   | |  JSON for Modern C++
// |  |  |__   |  |  | | | |  version 3.11.3
// |_____|_____|_____|_|___|  https://github.com/nlohmann/json
//
// SPDX-FileCopyrightText: 2013-2023 Niels Lohmann <https://nlohmann.me>
// SPDX-License-Identifier: MIT



#include <cstddef> // size_t

// #include <nlohmann/detail/abi_macros.hpp>


NLOHMANN_JSON_NAMESPACE_BEGIN
namespace detail
{

/// struct to capture the start position of the current token
struct position_t
{
    /// the total number of characters read
    std::size_t chars_read_total = 0;
    /// the number of characters read in the current line
    std::size_t chars_read_current_line = 0;
    /// the number of lines read
    std::size_t lines_read = 0;

    /// conversion to size_t to preserve SAX interface
    constexpr operator size_t() const
    {
        return chars_read_total;
    }
};

}  // namespace detail
NLOHMANN_JSON_NAMESPACE_END

// #include <nlohmann/detail/macro_scope.hpp>

// #include <nlohmann/detail/meta/cpp_future.hpp>
//     __ _____ _____ _____
//  __|  |   __|     |   | |  JSON for Modern C++
// |  |  |__   |  |  | | | |  version 3.11.3
// |_____|_____|_____|_|___|  https://github.com/nlohmann/json
//
// SPDX-FileCopyrightText: 2013-2023 Niels Lohmann <https://nlohmann.me>
// SPDX-FileCopyrightText: 2018 The Abseil Authors
// SPDX-License-Identifier: MIT



#include <cstddef> // size_t
#include <type_traits> // conditional, enable_if, false_type, integral_constant, is_constructible, is_integral, is_same, remove_cv, remove_reference, true_type
#include <utility> // index_sequence, make_index_sequence, index_sequence_for

// #include <nlohmann/detail/macro_scope.hpp>


NLOHMANN_JSON_NAMESPACE_BEGIN
namespace detail
{

template<typename T>
using uncvref_t = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

#if JSON_HAS_CPP_14

// the following utilities are natively available in C++14
using std::enable_if_t;
using std::index_sequence;
using std::make_index_sequence;
using std::index_sequence_for;

#else

// alias templates to reduce boilerplate
template<bool B, typename T = void>
using enable_if_t = typename std::enable_if<B, T>::type;

// The following code is taken from https://github.com/abseil/abseil-cpp/blob/10cb35e459f5ecca5b2ff107635da0bfa41011b4/absl/utility/utility.h
// which is part of Google Abseil (https://github.com/abseil/abseil-cpp), licensed under the Apache License 2.0.

//// START OF CODE FROM GOOGLE ABSEIL

// integer_sequence
//
// Class template representing a compile-time integer sequence. An instantiation
// of `integer_sequence<T, Ints...>` has a sequence of integers encoded in its
// type through its template arguments (which is a common need when
// working with C++11 variadic templates). `absl::integer_sequence` is designed
// to be a drop-in replacement for C++14's `std::integer_sequence`.
//
// Example:
//
//   template< class T, T... Ints >
//   void user_function(integer_sequence<T, Ints...>);
//
//   int main()
//   {
//     // user_function's `T` will be deduced to `int` and `Ints...`
//     // will be deduced to `0, 1, 2, 3, 4`.
//     user_function(make_integer_sequence<int, 5>());
//   }
template <typename T, T... Ints>
struct integer_sequence
{
    using value_type = T;
    static constexpr std::size_t size() noexcept
    {
        return sizeof...(Ints);
    }
};

// index_sequence
//
// A helper template for an `integer_sequence` of `size_t`,
// `absl::index_sequence` is designed to be a drop-in replacement for C++14's
// `std::index_sequence`.
template <size_t... Ints>
using index_sequence = integer_sequence<size_t, Ints...>;

namespace utility_internal
{

template <typename Seq, size_t SeqSize, size_t Rem>
struct Extend;

// Note that SeqSize == sizeof...(Ints). It's passed explicitly for efficiency.
template <typename T, T... Ints, size_t SeqSize>
struct Extend<integer_sequence<T, Ints...>, SeqSize, 0>
{
    using type = integer_sequence < T, Ints..., (Ints + SeqSize)... >;
};

template <typename T, T... Ints, size_t SeqSize>
struct Extend<integer_sequence<T, Ints...>, SeqSize, 1>
{
    using type = integer_sequence < T, Ints..., (Ints + SeqSize)..., 2 * SeqSize >;
};

// Recursion helper for 'make_integer_sequence<T, N>'.
// 'Gen<T, N>::type' is an alias for 'integer_sequence<T, 0, 1, ... N-1>'.
template <typename T, size_t N>
struct Gen
{
    using type =
        typename Extend < typename Gen < T, N / 2 >::type, N / 2, N % 2 >::type;
};

template <typename T>
struct Gen<T, 0>
{
    using type = integer_sequence<T>;
};

}  // namespace utility_internal

// Compile-time sequences of integers

// make_integer_sequence
//
// This template alias is equivalent to
// `integer_sequence<int, 0, 1, ..., N-1>`, and is designed to be a drop-in
// replacement for C++14's `std::make_integer_sequence`.
template <typename T, T N>
using make_integer_sequence = typename utility_internal::Gen<T, N>::type;

// make_index_sequence
//
// This template alias is equivalent to `index_sequence<0, 1, ..., N-1>`,
// and is designed to be a drop-in replacement for C++14's
// `std::make_index_sequence`.
template <size_t N>
using make_index_sequence = make_integer_sequence<size_t, N>;

// index_sequence_for
//
// Converts a typename pack into an index sequence of the same length, and
// is designed to be a drop-in replacement for C++14's
// `std::index_sequence_for()`
template <typename... Ts>
using index_sequence_for = make_index_sequence<sizeof...(Ts)>;

//// END OF CODE FROM GOOGLE ABSEIL

#endif

// dispatch utility (taken from ranges-v3)
template<unsigned N> struct priority_tag : priority_tag < N - 1 > {};
template<> struct priority_tag<0> {};

// taken from ranges-v3
template<typename T>
struct static_const
{
    static constexpr T value{};
};

template<typename T>
constexpr T static_const<T>::value;

}  // namespace detail
NLOHMANN_JSON_NAMESPACE_END

// #include <nlohmann/detail/meta/type_traits.hpp>
//     __ _____ _____ _____
//  __|  |   __|     |   | |  JSON for Modern C++
// |  |  |__   |  |  | | | |  version 3.11.3
// |_____|_____|_____|_|___|  https://github.com/nlohmann/json
//
// SPDX-FileCopyrightText: 2013-2023 Niels Lohmann <https://nlohmann.me>
// SPDX-License-Identifier: MIT



#include <limits> // numeric_limits
#include <type_traits> // false_type, is_constructible, is_integral, is_same, true_type
#include <utility> // declval
#if defined(__cpp_lib_byte) && __cpp_lib_byte >= 201603L
    #include <cstddef> // byte
#endif
// #include <nlohmann/detail/iterators/iterator_traits.hpp>
//     __ _____ _____ _____
//  __|  |   __|     |   | |  JSON for Modern C++
// |  |  |__   |  |  | | | |  version 3.11.3
// |_____|_____|_____|_|___|  https://github.com/nlohmann/json
//
// SPDX-FileCopyrightText: 2013-2023 Niels Lohmann <https://nlohmann.me>
// SPDX-License-Identifier: MIT



#include <iterator> // random_access_iterator_tag

// #include <nlohmann/detail/abi_macros.hpp>

// #include <nlohmann/detail/meta/void_t.hpp>
//     __ _____ _____ _____
//  __|  |   __|     |   | |  JSON for Modern C++
// |  |  |__   |  |  | | | |  version 3.11.3
// |_____|_____|_____|_|___|  https://github.com/nlohmann/json
//
// SPDX-FileCopyrightText: 2013-2023 Niels Lohmann <https://nlohmann.me>
// SPDX-License-Identifier: MIT



// #include <nlohmann/detail/abi_macros.hpp>


NLOHMANN_JSON_NAMESPACE_BEGIN
namespace detail
{

template<typename ...Ts> struct make_void
{
    using type = void;
};
template<typename ...Ts> using void_t = typename make_void<Ts...>::type;

}  // namespace detail
NLOHMANN_JSON_NAMESPACE_END


NLOHMANN_JSON_NAMESPACE_BEGIN
namespace detail
{

template<typename It, typename = void>
struct iterator_types {};

template<typename It>
struct iterator_types <
    It,
    void_t<typename It::difference_type, typename It::value_type, typename It::pointer,
    typename It::reference, typename It::iterator_category >>
{
    using difference_type = typename It::difference_type;
    using value_type = typename It::value_type;
    using pointer = typename It::pointer;
    using reference = typename It::reference;
    using iterator_category = typename It::iterator_category;
};

// This is required as some compilers implement std::iterator_traits in a way that
// doesn't work with SFINAE. See https://github.com/nlohmann/json/issues/1341.
template<typename T, typename = void>
struct iterator_traits
{
};

template<typename T>
struct iterator_traits<T, enable_if_t<!std::is_pointer<T>::value>>
    : iterator_types<T>
{
};

template<typename T>
struct iterator_traits<T*, enable_if_t<std::is_object<T>::value>>
{
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = T*;
    using reference = T&;
};

}  // namespace detail
NLOHMANN_JSON_NAMESPACE_END

// #include <nlohmann/detail/macro_scope.hpp>

// #include <nlohmann/detail/meta/call_std/begin.hpp>
//     __ _____ _____ _____
//  __|  |   __|     |   | |  JSON for Modern C++
// |  |  |__   |  |  | | | |  version 3.11.3
// |_____|_____|_____|_|___|  https://github.com/nlohmann/json
//
// SPDX-FileCopyrightText: 2013-2023 Niels Lohmann <https://nlohmann.me>
// SPDX-License-Identifier: MIT



// #include <nlohmann/detail/macro_scope.hpp>


NLOHMANN_JSON_NAMESPACE_BEGIN

NLOHMANN_CAN_CALL_STD_FUNC_IMPL(begin);

NLOHMANN_JSON_NAMESPACE_END

// #include <nlohmann/detail/meta/call_std/end.hpp>
//     __ _____ _____ _____
//  __|  |   __|     |   | |  JSON for Modern C++
// |  |  |__   |  |  | | | |  version 3.11.3
// |_____|_____|_____|_|___|  https://github.com/nlohmann/json
//
// SPDX-FileCopyrightText: 2013-2023 Niels Lohmann <https://nlohmann.me>
// SPDX-License-Identifier: MIT



// #include <nlohmann/detail/macro_scope.hpp>


NLOHMANN_JSON_NAMESPACE_BEGIN

NLOHMANN_CAN_CALL_STD_FUNC_IMPL(end);

NLOHMANN_JSON_NAMESPACE_END

// #include <nlohmann/detail/meta/cpp_future.hpp>

// #include <nlohmann/detail/meta/detected.hpp>
//     __ _____ _____ _____
//  __|  |   __|     |   | |  JSON for Modern C++
// |  |  |__   |  |  | | | |  version 3.11.3
// |_____|_____|_____|_|___|  https://github.com/nlohmann/json
//
// SPDX-FileCopyrightText: 2013-2023 Niels Lohmann <https://nlohmann.me>
// SPDX-License-Identifier: MIT



#include <type_traits>

// #include <nlohmann/detail/meta/void_t.hpp>


NLOHMANN_JSON_NAMESPACE_BEGIN
namespace detail
{

// https://en.cppreference.com/w/cpp/experimental/is_detected
struct nonesuch
{
    nonesuch() = delete;
    ~nonesuch() = delete;
    nonesuch(nonesuch const&) = delete;
    nonesuch(nonesuch const&&) = delete;
    void operator=(nonesuch const&) = delete;
    void operator=(nonesuch&&) = delete;
};

template<class Default,
         class AlwaysVoid,
         template<class...> class Op,
         class... Args>
struct detector
{
    using value_t = std::false_type;
    using type = Default;
};

template<class Default, template<class...> class Op, class... Args>
struct detector<Default, void_t<Op<Args...>>, Op, Args...>
{
    using value_t = std::true_type;
    using type = Op<Args...>;
};

template<template<class...> class Op, class... Args>
using is_detected = typename detector<nonesuch, void, Op, Args...>::value_t;

template<template<class...> class Op, class... Args>
using detected_t = typename detector<nonesuch, void, Op, Args...>::type;

template<class Default, template<class...> class Op, class... Args>
using detected_or = detector<Default, void, Op, Args...>;

template<class Default, template<class...> class Op, class... Args>
using detected_or_t = typename detected_or<Default, Op, Args...>::type;

template<class Expected, template<class...> class Op, class... Args>
using is_detected_exact = std::is_same<Expected, detected_t<Op, Args...>>;

template<class To, template<class...> class Op, class... Args>
using is_detected_convertible = std::is_convertible<detected_t<Op, Args...>, To>;

}  // namespace detail
NLOHMANN_JSON_NAMESPACE_END

// #include <nlohmann/json_fwd.hpp>
//     __ _____ _____ _____
//  __|  |   __|     |   | |  JSON for Modern C++
// |  |  |__   |  |  | | | |  version 3.11.3
// |_____|_____|_____|_|___|  https://github.com/nlohmann/json
//
// SPDX-FileCopyrightText: 2013-2023 Niels Lohmann <https://nlohmann.me>
// SPDX-License-Identifier: MIT

#ifndef INCLUDE_NLOHMANN_JSON_FWD_HPP_
    #define INCLUDE_NLOHMANN_JSON_FWD_HPP_

    #include <cstdint> // int64_t, uint64_t
    #include <map> // map
    #include <memory> // allocator
    #include <string> // string
    #include <vector> // vector

    // #include <nlohmann/detail/abi_macros.hpp>


    /*!
    @brief namespace for Niels Lohmann
    @see https://github.com/nlohmann
    @since version 1.0.0
    */
    NLOHMANN_JSON_NAMESPACE_BEGIN

    /*!
    @brief default JSONSerializer template argument

    This serializer ignores the template arguments and uses ADL
    ([argument-dependent lookup](https://en.cppreference.com/w/cpp/language/adl))
    for serialization.
    */
    template<typename T = void, typename SFINAE = void>
    struct adl_serializer;

    /// a class to store JSON values
    /// @sa https://json.nlohmann.me/api/basic_json/
    template<template<typename U, typename V, typename... Args> class ObjectType =
    std::map,
    template<typename U, typename... Args> class ArrayType = std::vector,
    class StringType = std::string, class BooleanType = bool,
    class NumberIntegerType = std::int64_t,
    class NumberUnsignedType = std::uint64_t,
    class NumberFloatType = double,
    template<typename U> class AllocatorType = std::allocator,
    template<typename T, typename SFINAE = void> class JSONSerializer =
    adl_serializer,
    class BinaryType = std::vector<std::uint8_t>, // cppcheck-suppress syntaxError
    class CustomBaseClass = void>
    class basic_json;

    /// @brief JSON Pointer defines a string syntax for identifying a specific value within a JSON document
    /// @sa https://json.nlohmann.me/api/json_pointer/
    template<typename RefStringType>
    class json_pointer;

    /*!
    @brief default specialization
    @sa https://json.nlohmann.me/api/json/
    */
    using json = basic_json<>;

    /// @brief a minimal map-like container that preserves insertion order
    /// @sa https://json.nlohmann.me/api/ordered_map/
    template<class Key, class T, class IgnoredLess, class Allocator>
    struct ordered_map;

    /// @brief specialization that maintains the insertion order of object keys
    /// @sa https://json.nlohmann.me/api/ordered_json/
    using ordered_json = basic_json<nlohmann::ordered_map>;

    NLOHMANN_JSON_NAMESPACE_END

#endif  // INCLUDE_NLOHMANN_JSON_FWD_HPP_


NLOHMANN_JSON_NAMESPACE_BEGIN
/*!
@brief detail namespace with internal helper functions

This namespace collects functions that should not be exposed,
implementations of some @ref basic_json methods, and meta-programming helpers.

@since version 2.1.0
*/
namespace detail
{

/////////////
// helpers //
/////////////

// Note to maintainers:
//
// Every trait in this file expects a non-CV-qualified type.
// The only exceptions are in the 'aliases for detected' section
// (i.e., those of the form: decltype(T::member_function(std::declval<T>())))
//
// In this case, T has to be properly CV-qualified to constraint the function arguments
// (e.g., to_json(BasicJsonType&, const T&))

template<typename> struct is_basic_json : std::false_type {};

NLOHMANN_BASIC_JSON_TPL_DECLARATION
struct is_basic_json<NLOHMANN_BASIC_JSON_TPL> : std::true_type {};

//////////////////////
// json_ref helpers //
//////////////////////

template<typename>
class json_ref;

template<typename>
struct is_json_ref : std::false_type {};

template<typename T>
struct is_json_ref<json_ref<T>> : std::true_type {};

//////////////////////////
// aliases for detected //
//////////////////////////

template<typename T>
using mapped_type_t = typename T::mapped_type;

template<typename T>
using key_type_t = typename T::key_type;

template<typename T>
using value_type_t = typename T::value_type;

template<typename T>
using difference_type_t = typename T::difference_type;

template<typename T>
using pointer_t = typename T::pointer;

template<typename T>
using reference_t = typename T::reference;

template<typename T>
using iterator_category_t = typename T::iterator_category;

template<typename T, typename... Args>
using to_json_function = decltype(T::to_json(std::declval<Args>()...));

template<typename T, typename... Args>
using from_json_function = decltype(T::from_json(std::declval<Args>()...));

template<typename T, typename U>
using get_template_function = decltype(std::declval<T>().template get<U>());

// trait checking if JSONSerializer<T>::from_json(json const&, udt&) exists
template<typename BasicJsonType, typename T, typename = void>
struct has_from_json : std::false_type {};

template<typename BasicJsonType, typename T>
struct has_from_json<BasicJsonType, T, enable_if_t<!is_basic_json<T>::value>>
{
    using serializer = typename BasicJsonType::template json_serializer<T, void>;

    static constexpr bool value =
        is_detected_exact<void, from_json_function, serializer,
        const BasicJsonType&, T&>::value;
};

// This trait checks if JSONSerializer<T>::from_json(json const&) exists
// this overload is used for non-default-constructible user-defined-types
template<typename BasicJsonType, typename T, typename = void>
struct has_non_default_from_json : std::false_type {};

template<typename BasicJsonType, typename T>
struct has_non_default_from_json<BasicJsonType, T, enable_if_t<!is_basic_json<T>::value>>
{
    using serializer = typename BasicJsonType::template json_serializer<T, void>;

    static constexpr bool value =
        is_detected_exact<T, from_json_function, serializer,
        const BasicJsonType&>::value;
};

// This trait checks if BasicJsonType::json_serializer<T>::to_json exists
// Do not evaluate the trait when T is a basic_json type, to avoid template instantiation infinite recursion.
template<typename BasicJsonType, typename T, typename = void>
struct has_to_json : std::false_type {};

template<typename BasicJsonType, typename T>
struct has_to_json<BasicJsonType, T, enable_if_t<!is_basic_json<T>::value>>
{
    using serializer = typename BasicJsonType::template json_serializer<T, void>;

    static constexpr bool value =
        is_detected_exact<void, to_json_function, serializer, BasicJsonType&,
        T>::value;
};

///////////////////
// is_ functions //
///////////////////

// https://en.cppreference.com/w/cpp/types/conjunction
template<class...> struct conjunction : std::true_type { };
template<class B> struct conjunction<B> : B { };
template<class B, class... Bn>
struct conjunction<B, Bn...>
    : std::conditional<static_cast<bool>(B::value), conjunction<Bn...>, B>::type {};

// https://en.cppreference.com/w/cpp/types/negation
template<class B> struct negation : std::integral_constant<bool, !B::value> { };

template<typename T>
struct is_iterator_traits : std::false_type {};

template<typename T>
struct is_iterator_traits<iterator_traits<T>>
{
  private:
    using traits = iterator_traits<T>;

  public:
    static constexpr auto value =
        is_detected<value_type_t, traits>::value &&
        is_detected<difference_type_t, traits>::value &&
        is_detected<pointer_t, traits>::value &&
        is_detected<iterator_category_t, traits>::value &&
        is_detected<reference_t, traits>::value;
};

template<typename T>
struct is_range
{
  private:
    using t_ref = typename std::add_lvalue_reference<T>::type;

    using iterator = detected_t<result_of_begin, t_ref>;
    using sentinel = detected_t<result_of_end, t_ref>;

    static constexpr auto is_iterator_begin =
        is_iterator_traits<iterator_traits<iterator>>::value;

  public:
    static constexpr bool value = !std::is_same<iterator, nonesuch>::value && !std::is_same<sentinel, nonesuch>::value && is_iterator_begin;
};

template<typename R>
using iterator_t = enable_if_t<is_range<R>::value, detected_t<result_of_begin, decltype(std::declval<R&>())>>;

template<typename T>
using range_value_t = value_type_t<iterator_traits<iterator_t<T>>>;

// The following implementation of is_complete_type is taken from
// https://blogs.msdn.microsoft.com/vcblog/2015/12/02/partial-support-for-expression-sfinae-in-vs-2015-update-1/
// and is written by Xiang Fan who agreed to use it in this library.

template<typename T, typename = void>
struct is_complete_type : std::false_type {};

template<typename T>
struct is_complete_type<T, decltype(void(sizeof(T)))> : std::true_type {};

template<typename BasicJsonType, typename CompatibleObjectType,
         typename = void>
struct is_compatible_object_type_impl : std::false_type {};

template<typename BasicJsonType, typename CompatibleObjectType>
struct is_compatible_object_type_impl<
    BasicJsonType, CompatibleObjectType,
    void_t<mapped_type_t<CompatibleObjectType>,
           key_type_t<CompatibleObjectType>>>
{
    using object_t = typename BasicJsonType::object_t;

    static constexpr bool value =
        std::is_constructible<typename object_t::key_type,
        typename CompatibleObjectType::key_type>::value &&
        std::is_constructible<typename object_t::mapped_type,
        typename CompatibleObjectType::mapped_type>::value;
};

template<typename BasicJsonType, typename CompatibleObjectType>
struct is_compatible_object_type
    : is_compatible_object_type_impl<BasicJsonType, CompatibleObjectType> {};

template<typename BasicJsonType, typename CompatibleArrayType, typename = void>
struct is_compatible_array_type_impl : std::false_type {};

template<typename BasicJsonType, typename CompatibleArrayType>
struct is_compatible_array_type_impl<
    BasicJsonType, CompatibleArrayType,
    enable_if_t<is_range<CompatibleArrayType>::value &&
// special case for types like std::filesystem::path whose iterator's value_type are themselves
// c.f. https://github.com/nlohmann/json/pull/3073
                !std::is_same<CompatibleArrayType, range_value_t<CompatibleArrayType>>::value>>
{
    static constexpr bool value =
        std::is_constructible<BasicJsonType,
        range_value_t<CompatibleArrayType>>::value;
};

template<typename BasicJsonType, typename CompatibleArrayType>
struct is_compatible_array_type
    : is_compatible_array_type_impl<BasicJsonType, CompatibleArrayType> {};

template<typename RealIntegerType, typename CompatibleNumberIntegerType,
         typename = void>
struct is_compatible_integer_type_impl : std::false_type {};

template<typename RealIntegerType, typename CompatibleNumberIntegerType>
struct is_compatible_integer_type_impl<
    RealIntegerType, CompatibleNumberIntegerType,
    enable_if_t<std::is_integral<RealIntegerType>::value&&
                std::is_integral<CompatibleNumberIntegerType>::value &&
                !std::is_same<bool, CompatibleNumberIntegerType>::value>>
{
    // is there an assert somewhere on overflows?
    using RealLimits = std::numeric_limits<RealIntegerType>;
    using CompatibleLimits = std::numeric_limits<CompatibleNumberIntegerType>;

    static constexpr auto value =
        std::is_constructible<RealIntegerType,
        CompatibleNumberIntegerType>::value &&
        CompatibleLimits::is_integer &&
        RealLimits::is_signed == CompatibleLimits::is_signed;
};

template<typename RealIntegerType, typename CompatibleNumberIntegerType>
struct is_compatible_integer_type
    : is_compatible_integer_type_impl<RealIntegerType,
      CompatibleNumberIntegerType> {};

template<typename BasicJsonType, typename CompatibleType, typename = void>
struct is_compatible_type_impl: std::false_type {};

template<typename BasicJsonType, typename CompatibleType>
struct is_compatible_type_impl<
    BasicJsonType, CompatibleType,
    enable_if_t<is_complete_type<CompatibleType>::value>>
{
    static constexpr bool value =
        has_to_json<BasicJsonType, CompatibleType>::value;
};

template<typename BasicJsonType, typename CompatibleType>
struct is_compatible_type
    : is_compatible_type_impl<BasicJsonType, CompatibleType> {};

template<typename T>
using is_json_pointer = is_specialization_of<::nlohmann::json_pointer, uncvref_t<T>>;

}  // namespace detail
NLOHMANN_JSON_NAMESPACE_END

// #include <nlohmann/detail/string_concat.hpp>
//     __ _____ _____ _____
//  __|  |   __|     |   | |  JSON for Modern C++
// |  |  |__   |  |  | | | |  version 3.11.3
// |_____|_____|_____|_|___|  https://github.com/nlohmann/json
//
// SPDX-FileCopyrightText: 2013-2023 Niels Lohmann <https://nlohmann.me>
// SPDX-License-Identifier: MIT



#include <string> // string
#include <utility> // forward

// #include <nlohmann/detail/meta/cpp_future.hpp>

// #include <nlohmann/detail/meta/detected.hpp>


NLOHMANN_JSON_NAMESPACE_BEGIN
namespace detail
{

template<typename... Args>
std::string concat(Args&& ... args)
{
    std::string s;
    (s.append(std::forward<Args>(args)), ...);
    return s;
}

}  // namespace detail
NLOHMANN_JSON_NAMESPACE_END


// include after macro_scope.hpp
#ifdef JSON_HAS_CPP_17
    #include <optional>
#endif

#if JSON_HAS_FILESYSTEM || JSON_HAS_EXPERIMENTAL_FILESYSTEM
    #include <filesystem>
#endif

NLOHMANN_JSON_NAMESPACE_BEGIN
namespace detail
{

template<typename BasicJsonType>
inline void from_json(const BasicJsonType& j, typename std::nullptr_t& n)
{
    if (JSON_HEDLEY_UNLIKELY(!j.is_null()))
    {
        JSON_THROW(type_error::create(302, concat("type must be null, but is ", j.type_name()), &j));
    }
    n = nullptr;
}

#ifdef JSON_HAS_CPP_17
template<typename BasicJsonType, typename T>
void from_json(const BasicJsonType& j, std::optional<T>& opt)
{
    if (j.is_null())
    {
        opt = std::nullopt;
    }
    else
    {
        opt = j.template get<T>();
    }
}
#endif // JSON_HAS_CPP_17

// overloads for basic_json template parameters
template<typename BasicJsonType, typename ArithmeticType,
         enable_if_t<std::is_arithmetic<ArithmeticType>::value&&
                     !std::is_same<ArithmeticType, typename BasicJsonType::boolean_t>::value,
                     int> = 0>
void get_arithmetic_value(const BasicJsonType& j, ArithmeticType& val)
{
    switch (static_cast<value_t>(j))
    {
        case value_t::number_unsigned:
        {
            val = static_cast<ArithmeticType>(*j.template get_ptr<const typename BasicJsonType::number_unsigned_t*>());
            break;
        }
        case value_t::number_integer:
        {
            val = static_cast<ArithmeticType>(*j.template get_ptr<const typename BasicJsonType::number_integer_t*>());
            break;
        }
        case value_t::number_float:
        {
            val = static_cast<ArithmeticType>(*j.template get_ptr<const typename BasicJsonType::number_float_t*>());
            break;
        }

        case value_t::null:
        case value_t::object:
        case value_t::array:
        case value_t::string:
        case value_t::boolean:
        case value_t::binary:
        case value_t::discarded:
        default:
            JSON_THROW(type_error::create(302, concat("type must be number, but is ", j.type_name()), &j));
    }
}

template<typename BasicJsonType>
inline void from_json(const BasicJsonType& j, typename BasicJsonType::boolean_t& b)
{
    if (JSON_HEDLEY_UNLIKELY(!j.is_boolean()))
    {
        JSON_THROW(type_error::create(302, concat("type must be boolean, but is ", j.type_name()), &j));
    }
    b = *j.template get_ptr<const typename BasicJsonType::boolean_t*>();
}

template<typename BasicJsonType>
inline void from_json(const BasicJsonType& j, typename BasicJsonType::string_t& s)
{
    if (JSON_HEDLEY_UNLIKELY(!j.is_string()))
    {
        JSON_THROW(type_error::create(302, concat("type must be string, but is ", j.type_name()), &j));
    }
    s = *j.template get_ptr<const typename BasicJsonType::string_t*>();
}

template<typename BasicJsonType>
inline void from_json(const BasicJsonType& j, typename BasicJsonType::number_float_t& val)
{
    get_arithmetic_value(j, val);
}

template<typename BasicJsonType>
inline void from_json(const BasicJsonType& j, typename BasicJsonType::number_unsigned_t& val)
{
    get_arithmetic_value(j, val);
}

template<typename BasicJsonType>
inline void from_json(const BasicJsonType& j, typename BasicJsonType::number_integer_t& val)
{
    get_arithmetic_value(j, val);
}

#if !JSON_DISABLE_ENUM_SERIALIZATION
template<typename BasicJsonType, typename EnumType,
         enable_if_t<std::is_enum<EnumType>::value, int> = 0>
inline void from_json(const BasicJsonType& j, EnumType& e)
{
    typename std::underlying_type<EnumType>::type val;
    get_arithmetic_value(j, val);
    e = static_cast<EnumType>(val);
}
#endif // JSON_DISABLE_ENUM_SERIALIZATION

// forward_list doesn't have an insert method
template<typename BasicJsonType, typename T, typename Allocator,
         enable_if_t<is_detected<get_template_function, const BasicJsonType&, T>::value, int> = 0>
inline void from_json(const BasicJsonType& j, std::forward_list<T, Allocator>& l)
{
    if (JSON_HEDLEY_UNLIKELY(!j.is_array()))
    {
        JSON_THROW(type_error::create(302, concat("type must be array, but is ", j.type_name()), &j));
    }
    l.clear();
    std::transform(j.rbegin(), j.rend(),
                   std::front_inserter(l), [](const BasicJsonType & i)
    {
        return i.template get<T>();
    });
}

// valarray doesn't have an insert method
template<typename BasicJsonType, typename T,
         enable_if_t<is_detected<get_template_function, const BasicJsonType&, T>::value, int> = 0>
inline void from_json(const BasicJsonType& j, std::valarray<T>& l)
{
    if (JSON_HEDLEY_UNLIKELY(!j.is_array()))
    {
        JSON_THROW(type_error::create(302, concat("type must be array, but is ", j.type_name()), &j));
    }
    l.resize(j.size());
    std::transform(j.begin(), j.end(), std::begin(l),
                   [](const BasicJsonType & elem)
    {
        return elem.template get<T>();
    });
}

template<typename BasicJsonType, typename T, std::size_t N>
auto from_json(const BasicJsonType& j, T (&arr)[N])
-> decltype(j.template get<T>(), void())
{
    for (std::size_t i = 0; i < N; ++i)
    {
        arr[i] = j.at(i).template get<T>();
    }
}

template<typename BasicJsonType>
inline void from_json_array_impl(const BasicJsonType& j, typename BasicJsonType::array_t& arr, priority_tag<3> /*unused*/)
{
    arr = *j.template get_ptr<const typename BasicJsonType::array_t*>();
}

template<typename BasicJsonType, typename T, std::size_t N>
auto from_json_array_impl(const BasicJsonType& j, std::array<T, N>& arr,
                          priority_tag<2> /*unused*/)
-> decltype(j.template get<T>(), void())
{
    for (std::size_t i = 0; i < N; ++i)
    {
        arr[i] = j.at(i).template get<T>();
    }
}

template<typename BasicJsonType, typename ConstructibleArrayType,
         enable_if_t<
             std::is_assignable<ConstructibleArrayType&, ConstructibleArrayType>::value,
             int> = 0>
auto from_json_array_impl(const BasicJsonType& j, ConstructibleArrayType& arr, priority_tag<1> /*unused*/)
-> decltype(
    arr.reserve(std::declval<typename ConstructibleArrayType::size_type>()),
    j.template get<typename ConstructibleArrayType::value_type>(),
    void())
{
    using std::end;

    ConstructibleArrayType ret;
    ret.reserve(j.size());
    std::transform(j.begin(), j.end(),
                   std::inserter(ret, end(ret)), [](const BasicJsonType & i)
    {
        // get<BasicJsonType>() returns *this, this won't call a from_json
        // method when value_type is BasicJsonType
        return i.template get<typename ConstructibleArrayType::value_type>();
    });
    arr = std::move(ret);
}

template<typename BasicJsonType, typename ConstructibleArrayType,
         enable_if_t<
             std::is_assignable<ConstructibleArrayType&, ConstructibleArrayType>::value,
             int> = 0>
inline void from_json_array_impl(const BasicJsonType& j, ConstructibleArrayType& arr,
                                 priority_tag<0> /*unused*/)
{
    using std::end;

    ConstructibleArrayType ret;
    std::transform(
        j.begin(), j.end(), std::inserter(ret, end(ret)),
        [](const BasicJsonType & i)
    {
        // get<BasicJsonType>() returns *this, this won't call a from_json
        // method when value_type is BasicJsonType
        return i.template get<typename ConstructibleArrayType::value_type>();
    });
    arr = std::move(ret);
}

template<typename BasicJsonType, typename ConstructibleArrayType,
         enable_if_t<
             !is_compatible_object_type<BasicJsonType, ConstructibleArrayType>::value &&
             std::is_constructible<typename ConstructibleArrayType::value_type, BasicJsonType>::value &&
             !std::is_same<ConstructibleArrayType, typename BasicJsonType::string_t>::value &&
             !std::is_same<ConstructibleArrayType, typename BasicJsonType::binary_t>::value &&
             !is_basic_json<ConstructibleArrayType>::value,
             int> = 0>
auto from_json(const BasicJsonType& j, ConstructibleArrayType& arr)
-> decltype(from_json_array_impl(j, arr, priority_tag<3> {}),
j.template get<typename ConstructibleArrayType::value_type>(),
void())
{
    if (JSON_HEDLEY_UNLIKELY(!j.is_array()))
    {
        JSON_THROW(type_error::create(302, concat("type must be array, but is ", j.type_name()), &j));
    }

    from_json_array_impl(j, arr, priority_tag<3> {});
}

template<typename BasicJsonType>
inline void from_json(const BasicJsonType& j, typename BasicJsonType::binary_t& bin)
{
    if (JSON_HEDLEY_UNLIKELY(!j.is_binary()))
    {
        JSON_THROW(type_error::create(302, concat("type must be binary, but is ", j.type_name()), &j));
    }

    bin = *j.template get_ptr<const typename BasicJsonType::binary_t*>();
}

template<typename BasicJsonType, typename ConstructibleObjectType,
         enable_if_t<is_compatible_object_type<BasicJsonType, ConstructibleObjectType>::value, int> = 0>
inline void from_json(const BasicJsonType& j, ConstructibleObjectType& obj)
{
    if (JSON_HEDLEY_UNLIKELY(!j.is_object()))
    {
        JSON_THROW(type_error::create(302, concat("type must be object, but is ", j.type_name()), &j));
    }

    obj = *j.template get_ptr<const typename BasicJsonType::object_t*>();
}

// overload for arithmetic types, not chosen for basic_json template arguments
// (BooleanType, etc.); note: Is it really necessary to provide explicit
// overloads for boolean_t etc. in case of a custom BooleanType which is not
// an arithmetic type?
template<typename BasicJsonType, typename ArithmeticType,
         enable_if_t<
             std::is_arithmetic<ArithmeticType>::value&&
             !std::is_same<ArithmeticType, typename BasicJsonType::number_unsigned_t>::value&&
             !std::is_same<ArithmeticType, typename BasicJsonType::number_integer_t>::value&&
             !std::is_same<ArithmeticType, typename BasicJsonType::number_float_t>::value&&
             !std::is_same<ArithmeticType, typename BasicJsonType::boolean_t>::value,
             int> = 0>
inline void from_json(const BasicJsonType& j, ArithmeticType& val)
{
    switch (static_cast<value_t>(j))
    {
        case value_t::number_unsigned:
        {
            val = static_cast<ArithmeticType>(*j.template get_ptr<const typename BasicJsonType::number_unsigned_t*>());
            break;
        }
        case value_t::number_integer:
        {
            val = static_cast<ArithmeticType>(*j.template get_ptr<const typename BasicJsonType::number_integer_t*>());
            break;
        }
        case value_t::number_float:
        {
            val = static_cast<ArithmeticType>(*j.template get_ptr<const typename BasicJsonType::number_float_t*>());
            break;
        }
        case value_t::boolean:
        {
            val = static_cast<ArithmeticType>(*j.template get_ptr<const typename BasicJsonType::boolean_t*>());
            break;
        }

        case value_t::null:
        case value_t::object:
        case value_t::array:
        case value_t::string:
        case value_t::binary:
        case value_t::discarded:
        default:
            JSON_THROW(type_error::create(302, concat("type must be number, but is ", j.type_name()), &j));
    }
}

template<typename BasicJsonType, typename... Args, std::size_t... Idx>
std::tuple<Args...> from_json_tuple_impl_base(const BasicJsonType& j, index_sequence<Idx...> /*unused*/)
{
    return std::make_tuple(j.at(Idx).template get<Args>()...);
}

template<typename BasicJsonType>
std::tuple<> from_json_tuple_impl_base(const BasicJsonType& /*j*/, index_sequence<> /*unused*/)
{
    return {};
}

template<typename BasicJsonType, typename... Args>
inline void from_json_tuple_impl(const BasicJsonType& j, std::tuple<Args...>& t)
{
    t = from_json_tuple_impl_base<BasicJsonType, Args...>(j, index_sequence_for<Args...> {});
}

template<typename BasicJsonType, typename T,
         enable_if_t<std::is_constructible<T, BasicJsonType>::value, int> = 0>
inline void from_json(const BasicJsonType& j, T& val)
{
    val = j;
}

template<typename BasicJsonType, typename T1, typename T2>
inline void from_json(const BasicJsonType& j, std::pair<T1, T2>& p)
{
    p.first = j.at(0);
    p.second = j.at(1);
}

template < typename BasicJsonType, typename Key, typename Value, typename Compare, typename Allocator,
           typename = enable_if_t < !std::is_constructible <
                                        typename BasicJsonType::string_t, Key >::value >>
inline void from_json(const BasicJsonType& j, std::map<Key, Value, Compare, Allocator>& m)
{
    if (JSON_HEDLEY_UNLIKELY(!j.is_array()))
    {
        JSON_THROW(type_error::create(302, concat("type must be array, but is ", j.type_name()), &j));
    }
    m.clear();
    for (const auto& p : j)
    {
        if (JSON_HEDLEY_UNLIKELY(!p.is_array()))
        {
            JSON_THROW(type_error::create(302, concat("type must be array, but is ", p.type_name()), &j));
        }
        m.emplace(p.at(0).template get<Key>(), p.at(1).template get<Value>());
    }
}

template < typename BasicJsonType, typename Key, typename Value, typename Hash, typename KeyEqual, typename Allocator,
           typename = enable_if_t < !std::is_constructible <
                                        typename BasicJsonType::string_t, Key >::value >>
inline void from_json(const BasicJsonType& j, std::unordered_map<Key, Value, Hash, KeyEqual, Allocator>& m)
{
    if (JSON_HEDLEY_UNLIKELY(!j.is_array()))
    {
        JSON_THROW(type_error::create(302, concat("type must be array, but is ", j.type_name()), &j));
    }
    m.clear();
    for (const auto& p : j)
    {
        if (JSON_HEDLEY_UNLIKELY(!p.is_array()))
        {
            JSON_THROW(type_error::create(302, concat("type must be array, but is ", p.type_name()), &j));
        }
        m.emplace(p.at(0).template get<Key>(), p.at(1).template get<Value>());
    }
}

#if JSON_HAS_FILESYSTEM || JSON_HAS_EXPERIMENTAL_FILESYSTEM
template<typename BasicJsonType>
inline void from_json(const BasicJsonType& j, std::filesystem::path& p)
{
    if (JSON_HEDLEY_UNLIKELY(!j.is_string()))
    {
        JSON_THROW(type_error::create(302, concat("type must be string, but is ", j.type_name()), &j));
    }
    p = *j.template get_ptr<const typename BasicJsonType::string_t*>();
}
#endif

struct from_json_fn
{
  private:
    template<typename BasicJsonType, typename T>
    auto call(const BasicJsonType& j, T&& val, priority_tag<1> /*unused*/) const
    noexcept(noexcept(from_json(j, std::forward<T>(val))))
    -> decltype(from_json(j, std::forward<T>(val)))
    {
        return from_json(j, std::forward<T>(val));
    }

    template<typename BasicJsonType, typename T>
    auto call(const BasicJsonType& j, T&& val, priority_tag<0> /*unused*/) const
    noexcept(noexcept(std::forward<T>(val).from_json(j)))
    -> decltype(std::forward<T>(val).from_json(j))
    {
        return std::forward<T>(val).from_json(j);
    }

  public:
    template<typename BasicJsonType, typename T>
    auto operator()(const BasicJsonType& j, T&& val) const
    noexcept(noexcept(std::declval<from_json_fn>().call(j, std::forward<T>(val), priority_tag<1> {})))
    -> decltype(std::declval<from_json_fn>().call(j, std::forward<T>(val), priority_tag<1> {}))
    {
        return call(j, std::forward<T>(val), priority_tag<1> {});
    }
};

}  // namespace detail

#if !JSON_HAS_CPP_17
/// namespace to hold default `from_json` function
/// to see why this is required:
/// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4381.html
namespace
{
#endif
JSON_INLINE_VARIABLE constexpr const auto& from_json =
    detail::static_const<detail::from_json_fn>::value;
#if !JSON_HAS_CPP_17
}  // namespace
#endif

NLOHMANN_JSON_NAMESPACE_END
