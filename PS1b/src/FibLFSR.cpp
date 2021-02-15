#include "FibLFSR.hpp"
#include <stdexcept>

FibLFSR::FibLFSR(std::string seed, std::set<unsigned> tap_values)
{
    unsigned N = seed.size();

    if (N == 0)
        throw std::invalid_argument("Given seed is empty.");

    taps = tap_values.empty() ? FibonacciValues(N) : tap_values;
    taps.insert(N - 1); // Add the leftmost index as a tap

    if (N < *taps.rbegin()) // if shorter than largest tap -> exception
        throw std::invalid_argument("Tap index out-of-bounds.");

    reg_list.reserve(N);
    for (char bit : seed)
    {
        if (bit != '0' && bit != '1')
            throw std::invalid_argument("Invalid characters in the initializing seed.");
        reg_list.push_back(bit == '1');
    }
}

int FibLFSR::step()
{
    bool feedback_bit = 0;
    unsigned N = reg_list.size();
    for (unsigned i : taps)
        feedback_bit ^= reg_list[N - 1 - i]; // Since index 0 starts from the right
    reg_list.push_back(feedback_bit);        // Add the rightmost bit
    reg_list.erase(reg_list.begin());        // Drop the leftmost bit
    return feedback_bit;
}

int FibLFSR::generate(int k)
{
    int feedback_value = 0;
    while (--k >= 0)
        feedback_value = step() + (feedback_value << 1);
    return feedback_value;
}

std::ostream &operator<<(std::ostream &out, FibLFSR X)
{
    std::string result;
    for (bool bit : X.reg_list)
        result += bit + '0';
    return out << result;
}

std::string FibLFSR::hashToSeed(std::string key)
{
    unsigned hash = 41849243;
    for (auto c : key)
        hash = ((hash << 5) + hash) + c;
    std::string seed{};
    for (unsigned i = 0; i < CHAR_BIT * sizeof(hash); i++)
        seed += ((hash & (1U << i)) > 0) + '0';
    return seed;
}

std::set<unsigned> FibLFSR::FibonacciValues(unsigned n)
{
    std::set<unsigned> list{1};
    if (n <= 2)
        return list;

    unsigned next_val = 2;
    do
    {
        list.insert(next_val);
        next_val = *list.rbegin() + *(--list.rbegin());
    } while (next_val < n);

    return list;
}