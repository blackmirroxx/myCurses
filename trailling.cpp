#include <iostream>
#include <string>
#include <cstdint>

template <typename M, typename N>
auto multiply(M const& m, N const& n) -> decltype(m * n)
{
    return m * n;
}

auto main(int argc, char** argv) -> int
{
    std::cout << "hello world of trailling return types!" << std::endl;
    std::cout << std::endl;
    std::cout << "the product of " << argv[1] << " times " << argv[2] << " = " << multiply(std::stof(argv[1]), std::stof(argv[2])) << std::endl;
    return EXIT_SUCCESS;
}


// g++ -std=c++17 -o trailling trailling.cpp
