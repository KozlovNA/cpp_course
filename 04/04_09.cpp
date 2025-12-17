#include <type_traits> 

// =========================================================
//  Conditional
// =========================================================

template <bool B, typename T, typename F>
struct conditional {
    using type = T;
};

template <typename T, typename F>
struct conditional<false, T, F> {
    using type = F;
};

template <bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;

// =========================================================
//  Add Const / Remove Const / Remove Volatile
// =========================================================

// add_const
template <typename T>
struct add_const {
    using type = const T;
};

template <typename T>
using add_const_t = typename add_const<T>::type;

// remove_const
template <typename T>
struct remove_const {
    using type = T;
};

template <typename T>
struct remove_const<const T> {
    using type = T;
};

template <typename T>
using remove_const_t = typename remove_const<T>::type;

// remove_volatile 
template <typename T>
struct remove_volatile {
    using type = T;
};

template <typename T>
struct remove_volatile<volatile T> {
    using type = T;
};

template <typename T>
using remove_volatile_t = typename remove_volatile<T>::type;

// =========================================================
//  Is Class
// =========================================================

template <typename T>
struct is_class_tester {
    template <typename U>
    static std::true_type test(int U::*);

    template <typename U>
    static std::false_type test(...);

    using result_type = decltype(test<T>(nullptr));
};

template <typename T>
struct is_class : is_class_tester<T>::result_type {};

template <typename T>
inline constexpr bool is_class_v = is_class<T>::value;

// =========================================================
// Decay 
// =========================================================

template <typename T> struct remove_reference { using type = T; };
template <typename T> struct remove_reference<T&> { using type = T; };
template <typename T> struct remove_reference<T&&> { using type = T; };
template <typename T> using remove_reference_t = typename remove_reference<T>::type;

template <typename T>
struct decay_impl {
    using type = remove_const_t<remove_volatile_t<T>>; 
};

template <typename T>
struct decay_impl<T[]> {
    using type = T*;
};

template <typename T, std::size_t N>
struct decay_impl<T[N]> {
    using type = T*;
};

template <typename Ret, typename... Args>
struct decay_impl<Ret(Args...)> {
    using type = Ret(*)(Args...);
};

template <typename Ret, typename... Args>
struct decay_impl<Ret(Args..., ...)> {
    using type = Ret(*)(Args..., ...);
};

template <typename T>
struct decay {
    using type = typename decay_impl<remove_reference_t<T>>::type;
};

template <typename T>
using decay_t = typename decay<T>::type;

// =========================================================
// Tests
// =========================================================

class MyClass {};

void func(int) {}

int main() {
    // --- conditional ---
    static_assert(std::is_same_v<conditional_t<true, int, double>, int>, "conditional true fail");
    static_assert(std::is_same_v<conditional_t<false, int, double>, double>, "conditional false fail");

    // --- add_const ---
    static_assert(std::is_same_v<add_const_t<int>, const int>, "add_const fail");
    
    // --- remove_const ---
    static_assert(std::is_same_v<remove_const_t<const int>, int>, "remove_const fail");
    static_assert(std::is_same_v<remove_const_t<int>, int>, "remove_const (no const) fail");

    // --- is_class ---
    static_assert(is_class_v<MyClass> == true, "struct is a class");
    static_assert(is_class_v<int> == false, "int is not a class");

    // --- decay ---
    static_assert(std::is_same_v<decay_t<const int&>, int>, "decay const int& fail");
    static_assert(std::is_same_v<decay_t<volatile int&&>, int>, "decay volatile int&& fail");

    static_assert(std::is_same_v<decay_t<int[10]>, int*>, "decay array[N] fail");
    static_assert(std::is_same_v<decay_t<int[]>, int*>, "decay array[] fail");

    static_assert(std::is_same_v<decay_t<decltype(func)>, void(*)(int)>, "decay func fail");

    return 0;
}
