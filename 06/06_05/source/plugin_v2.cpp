#include <iostream>
#include <boost/dll/alias.hpp>

void test_implementation() {
    std::cout << "  plugin_v2 hello\n";
}

BOOST_DLL_ALIAS(test_implementation, test)
