#include "ED.hpp"
#include <string>
#include <iostream>
#include <chrono>

int main(int argc, char* argv[])
{
    std::string A, B;
    std::cin >> A >> B;
    ED ed(A, B);

    auto t_start = std::chrono::high_resolution_clock::now();

    auto dist = ed.OptDistance();
    auto alignment = ed.Alignment();

    auto t_end = std::chrono::high_resolution_clock::now();

    std::cout << "Edit distance = " << dist << std::endl;
    std::cout << alignment << std::endl;
    std::cout << "Elapsed time: " << std::chrono::duration<double>(t_end - t_start).count() << "s." << std::endl;
    return 0;
}