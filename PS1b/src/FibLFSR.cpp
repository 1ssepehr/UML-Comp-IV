#include "FibLFSR.hpp"
#include <stdexcept>

FibLFSR::FibLFSR(std::string seed, std::set<unsigned> tap_values)
{
    N = seed.size();
    if (N == 0)
        throw std::invalid_argument("Given seed is empty.");
    taps = tap_values;
    taps.insert(N - 1); // Add the leftmost index as a tap
    if (N < *taps.rbegin()) // if shorter than largest tap -> exception
        throw std::invalid_argument("Tap index out-of-bounds.");

    reg_list.reserve(N);
    for (char bit: seed)
    {
        if (bit != '0' && bit != '1')
            throw std::invalid_argument("Invalid characters in the initializing seed.");
        reg_list.push_back(bit == '1');
    }
}

int FibLFSR::step()
{
    bool feedback_bit = 0;
    for (unsigned i: taps)
        feedback_bit ^= reg_list[N - 1 - i]; // Since index 0 starts from the right
    reg_list.push_back(feedback_bit); // Add the rightmost bit
    reg_list.erase(reg_list.begin()); // Drop the leftmost bit
    return feedback_bit;
}

int FibLFSR::generate(int k)
{
    int feedback_value = 0;
    while(--k >= 0)
        feedback_value = step() + (feedback_value << 1);
    return feedback_value;
}

std::ostream& operator<<(std::ostream& out, FibLFSR X)
{
    std::string result;
    for (bool bit: X.reg_list)
        result += bit;
    return out << result;
}