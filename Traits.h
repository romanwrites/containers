#pragma once

namespace ft {
struct type_false {};
struct type_true {};

template<class T>
struct type_is_primitive : public type_false {};

template<>
struct type_is_primitive<bool> : public type_true {};

template<>
struct type_is_primitive<char> : public type_true {};

template<>
struct type_is_primitive<char16_t> : public type_true {};

template<>
struct type_is_primitive<char32_t> : public type_true {};

template<>
struct type_is_primitive<wchar_t> : public type_true {};

template<>
struct type_is_primitive<signed char> : public type_true {};

template<>
struct type_is_primitive<short int> : public type_true {};

template<>
struct type_is_primitive<int> : public type_true {};

template<>
struct type_is_primitive<long int> : public type_true {};

template<>
struct type_is_primitive<long long int> : public type_true {};

template<>
struct type_is_primitive<unsigned char> : public type_true {};

template<>
struct type_is_primitive<unsigned short int> : public type_true {};

template<>
struct type_is_primitive<unsigned int> : public type_true {};

template<>
struct type_is_primitive<unsigned long int> : public type_true {};

template<>
struct type_is_primitive<unsigned long long int> : public type_true {};

}
