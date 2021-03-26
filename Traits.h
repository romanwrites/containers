#pragma once

namespace ft {
struct false_type {};
struct true_type {};

template<class T>
struct is_primitive_type : public false_type {};

template<>
struct is_primitive_type<bool> : public true_type {};

template<>
struct is_primitive_type<char> : public true_type {};

template<>
struct is_primitive_type<char16_t> : public true_type {};

template<>
struct is_primitive_type<char32_t> : public true_type {};

template<>
struct is_primitive_type<wchar_t> : public true_type {};

template<>
struct is_primitive_type<signed char> : public true_type {};

template<>
struct is_primitive_type<short int> : public true_type {};

template<>
struct is_primitive_type<int> : public true_type {};

template<>
struct is_primitive_type<long int> : public true_type {};

template<>
struct is_primitive_type<long long int> : public true_type {};

template<>
struct is_primitive_type<unsigned char> : public true_type {};

template<>
struct is_primitive_type<unsigned short int> : public true_type {};

template<>
struct is_primitive_type<unsigned int> : public true_type {};

template<>
struct is_primitive_type<unsigned long int> : public true_type {};

template<>
struct is_primitive_type<unsigned long long int> : public true_type {};

}
