#include "FibLFSR.hpp"
#include <stdexcept>

FibLFSR::FibLFSR(std::string seed, std::set<unsigned> tap_values)
    : _register(0), N(seed.size())
{
    if (N == 0)
        throw std::invalid_argument("Given seed is empty.");

    if (N >= _MAX_SIZE)
    {
        std::cerr << "Warning: given seed \"" << seed << "\" is too long, only evaluating the first ";
        std::cerr << _MAX_SIZE << " bits.\n";
        N = _MAX_SIZE;
    }
    
    for (unsigned i = 0; i < N; i++)
    {
        int c = seed[N - 1 - i] - '0';
        if (c == 1)
            _register |= 1LLU << i;
        else if (c != 0)
            throw std::invalid_argument("Invalid characters in seed.");
    }

    _taps = tap_values.empty() ? FibonacciValues(N) : tap_values;
    _taps.insert(N - 1); // Add the leftmost index as a tap
    if (*_taps.rbegin() > N) // if shorter than largest tap -> exception
        throw std::invalid_argument("Tap index out-of-bounds.");
}

FibLFSR::FibLFSR(std::string keyphrase)
{
    // Hashes a keyphrase to a 64-bit long seed for the register.
    unsigned long long hash = _HASH_CONST;
    for (auto c : keyphrase)
        hash = _HASH_MULT * hash + c;

    N = 64;
    _register = hash;
    _taps = FibonacciValues(N);
}

int FibLFSR::step()
{
    bool feedback_bit = 0;
    for (unsigned i : _taps)
        feedback_bit ^= (_register & (1LLU << i)) && true;
    _register <<= 1;
    _register |= feedback_bit;
    return feedback_bit;
}

int FibLFSR::generate(int k)
{
    int feedback_value = 0;
    while (--k >= 0)
        feedback_value = step() + (feedback_value << 1);
    return feedback_value;
}

std::ostream &operator<<(std::ostream &out, FibLFSR &L)
{
    std::string result;
    for (unsigned i = 0; i < L.N; i++)
        result += '0' + ((L._register & (1LLU << i)) && true);
    return out << result;
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