#include <iostream>
#include <boost/dll/alias.hpp> 

void test_implementation() {
    std::cout << "  plugin_v1 hello\n";
}

BOOST_DLL_ALIAS(test_implementation, test)
