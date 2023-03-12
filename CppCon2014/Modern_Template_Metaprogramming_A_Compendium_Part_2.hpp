// CppCon 2014 Template Metaprogramming: A Compendium, Part 2

#include<climits>
#include<cstddef>
#include<type_traits>







// Compile-time absolute value matefunction
template<int N>
struct abs {
	static_assert(N != INT_MIN);
	static constexpr int value = (N < 0) ? -N : N;
};
/*
   int const/constexpr n = _;
   abs<n>::value
*/

// In comparison: a compile-time absolute value function
//constexpr int abs(int N) { return (N < 0) ? -N : N; }

// Compile-time recursion with specialization as base
template<unsigned M, unsigned N>
struct gcd {
	static int const value = gcd<N, M%N>::value;
};

template<unsigned M>
struct gcd<M, 0> {
	static_assert(M != 0); // gcd(0,0) undefined
	static int const value = M; // using const instead constexpr works with older compilers
};

// Compile-time rank of array
template<class T>
struct rank { static size_t const value = 0u; }; // for scalars
template<class U, size_t N>
struct rank<U[N]> { static size_t const value = 1u + rank<U>::value; };
/*
   using array_t = int[10][20][30];
   rank<array_t>::value
*/

// "Remove" const qualifier and return the type passed as parameter
template<class T>
struct type_is { using type = T; };
template<class T>
struct remove_const : type_is<T> {};
template<class T>
struct remove_const<T const> : type_is<T> {}; // same with volatile qualifier
/*
   remove_const<T>::type t;
   C++14: remove_const_t<T> t;
*/

// IF compile-time configuration
template<bool, class T, class>
struct IF : type_is<T> {};
template<class T, class F>
struct IF<false, T, F> : type_is<F> {};
/*
   C++14: conditional_t
*/

// enable_if
template<bool, class T = void>
struct enable_if : type_is<T> {};
template<class T>
struct enable_if<false, T> {};
/*
   enable_if<false, _>::type t; // ? -> SFINAE, instantiaton is discarded but does not produce error
*/

// SFINEA usage
using maxint_t = long long;
template<bool B, class T = void>
using enable_if_t = typename enable_if<B,T>::type; // for convenience
template<class T>
enable_if_t<std::is_integral<T>::value, maxint_t> f(T val) {};
template<class T>
enable_if_t<std::is_floating_point<T>::value, long double> f(T val) { return val; };
//const long double a = f(4.0); // OK
//const long long a = f(4); // OK
//const int a = f(true); // NOTOK

template<class T, T v>
struct integral_constant {
	static constexpr T value = v;
	constexpr operator T () const noexcept { return value; }
	constexpr T operator () () const noexcept { return value; }
}; // overloading T and () operators
// E.g.
template<class T>
struct rank_new : integral_constant<size_t, 0u> {};
template<class U, size_t N>
struct rank_new<U[N]> : integral_constant<size_t, 1u + rank<U>::value> {};
template<class U>
struct rank_new<U[]> : integral_constant<size_t, 1u + rank<U>::value> {};
// conveniences
template<bool b>
using bool_constant = integral_constant<bool, b>; 
using true_type = bool_constant<true>;
using false_type = bool_constant<false>;
