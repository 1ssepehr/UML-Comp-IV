#ifndef _FIBLFSR_HPP
#define _FIBLFSR_HPP 1

#include <string>
#include <vector>
#include <set>
#include <iostream>

class FibLFSR
{
public:
    FibLFSR(std::string seed, std::set<unsigned> tap_values);

    int step();

    int generate(int k);

    friend std::ostream& operator<<(std::ostream& out, FibLFSR X);

private:
    std::vector<bool> reg_list;
    std::set<unsigned> taps;
    unsigned N;
};

#endif