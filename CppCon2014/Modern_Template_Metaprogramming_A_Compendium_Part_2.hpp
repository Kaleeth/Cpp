// CppCon 2014 Template Metaprogramming: A Compendium, Part 2

#include<utility>
#include "Modern_Template_Metaprogramming_A_Compendium_Part_1.hpp"

// Metafunctions + inheritance
template<class T> struct is_void : false_type {};
template<> struct is_void<void> : true_type {};
template<> struct is_void<void const> : true_type {};
// etc...
template<class T, class U> struct is_same : false_type {};
template<class T> struct is_same<T, T> : true_type {};

template<class T>
using remove_cv = std::remove_volatile<std::remove_const_t<T>>; // std::remove_cv_t
template<class T>
using remove_cv_t = typename remove_cv<T>::type;

template<class T>
using is_void2 = is_same<remove_cv<T>, void>;

template<class T, class... TOther>
struct is_one_of; 
template<class T>
struct is_one_of<T> : false_type {}; 
template<class T, class... TRest>
struct is_one_of<T, T, TRest...> : true_type {};
template<class T, class U, class... TRest>
struct is_one_of<T, U, TRest...> : is_one_of<T, TRest...> {};

template<class T>
using is_void3 = is_one_of<T, void, void const, void volatile, void const volatile>;

/*
   sizeof, typeid, decltype, noexcept
   work on un-evaluated operands, they inspect them
   so previous definition of these operands is not needed
   declaration is necessary and sufficient
   e.g. decltype( foo( std::declval<T>() ) ); // returns foo type so its return type
   // declval<T>() for rvalue T, declval<T&>() for lvalue T
*/

template<class T>
struct is_copy_assignable {
private:
	template<class U, class = decltype( std::declval<U&>() = std::declval<U const&> )>
	static true_type try_assignment(U&&);
	static false_type try_assignment(...);
public:
	using type = decltype( try_assignment( std::declval<T>() ) );
};
// need also to ensure that the assignment's return type is T&

/*
   Earlier, without the prior:
   typedef char (&yes) [1]; typedef char (&no) [2]; // yes == reference to array of chars of size 1
   sizeof( try_assignment(_) );
   typedef bool_constant<sizeof(_) == sizeof(yes)> type;
*/

// void_t - works only for -well-formed- types
template<class ...>
using void_t = void;
// detect the presence/absence of a type member named e.g. T::type
template<class, class = void>
struct has_type_member : false_type {};
template<class T>
struct has_type_member<T, void_t<typename T::type> > : true_type {}; 
// has_type_member<T>::value

// other, for is_copy_assignable
template<class T>
using copy_assignment_t = decltype( std::declval<T&>() = std::declval<T const&>() );
template<class, class = void>
struct is_copy_assignable2 : false_type {};
template<class T>
struct is_copy_assignable2< T, void_t<copy_assignment_t<T>> > : is_same<copy_assignment_t<T>, T&> {};
// for is_move_assignable, only change in:
template<class T>
using move_assignment_t = decltype( std::declval<T&>() = std::declval<T&&>() );
