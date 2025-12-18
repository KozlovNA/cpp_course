#include <iostream>
#include <string>
#include <boost/dll.hpp>
#include <boost/filesystem.hpp> 

int main()
{
    std::string version;
    std::cout << "Enter library version (v1/v2): ";
    std::cin >> version;

    boost::filesystem::path lib_path = boost::filesystem::current_path();
    lib_path /= "libplugin_" + version;
    lib_path += boost::dll::shared_library::suffix();

    auto test_func = boost::dll::import_alias<void()>(lib_path, "test");
    test_func();
}
