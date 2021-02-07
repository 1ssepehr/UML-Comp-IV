# Linear Feedback Shift Register (Part A) [PS1a-README.md]

***Name:** Seyedsepehr Madani*

***Hours to complete assignment:** 6 hours*

## Questions

---

### Briefly discuss the assignment itself and what you accomplished.

This assignment consists of implementing and unit-testing a [simulation of a] Linear Feedback Shift Register (LFSR) for generating pseudo-random bits.

An LFSR is a register that generates the next state of the vacant bit after shifting via a linear function of the current bits (in this case, we use a selection of bits and XOR them to obtain the next bit).

I designed an exception-safe simulation of an LFSR using C++ and wrote three unit-tests using the Boost Unit Test Framework.

---

### Explain the representation you used for the register bits (how it works, and why you selected it).

A lot of students were suggesting using std::bitset for the internal
representation of the register; I disagreed, as the size of the seed (and ergo,the size of the register) is not known until run-time. There was the option of boost::dynamic_bitset, but I passed.

I simply used `std::vector<bool>` for emulating the register. This allows for *O(1)* random access for the taps, and *O(1)* insertion/removal at the ends (shifting).

Also, as an STL container, using `std::vector` eliminates the need for manual dynamic memory allocation.

---

### Discuss what's being tested in your two additional Boost unit tests

The first test I wrote tests the return values for `FibLFSR::step()` and `FibLFSR::generate()` functions.

The second test I wrote examines the exception-safety of the FibLFSR module by testing different invalid arguments for a seed (i.e. a seed with invalid characters or a tap position beyond the length of the seed).

---

### List whatever help (if any) you received from the instructor,  classmates, or anyone else.

I did this assignment entirely on my own.

---

### Describe any serious problems you encountered.

All resolved!

---

### List any other comments here.