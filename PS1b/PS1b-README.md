# Linear Feedback Shift Register: PhotoMagic (Part B) [PS1b-README.md]

***Name:** Seyedsepehr Madani*

***Hours to complete assignment:** 8 hours*

## Questions

---

### Briefly discuss the assignment itself and what you accomplished.

In this assignment, we encode an input image with an LFSR seed, and use the same seed to decode the image back to its original.

I designed an exception-safe simulation of an LFSR using C++ and wrote three unit-tests using the Boost Unit Test Framework.

---

### If you did any implementation for extra credit, describe it here and why it is interesting.

For the extra credit part, I used the well-known [djb2 hash](http://www.cse.yorku.ca/~oz/hash.html) to hash the string value of the keyphrase into a 64-bit `unsigned long long` type, which I would use for my LSFR seed.

In PS1a, I had been using `std::vector<bool>` for emulating the register, which in hindsight was terribly inefficient. Instead, I switched my register container to a `unsigned long long` (guarantee of 64 bits from C++11) with bitwise operations for the linear feedback function. This was simple, safe, and allowed for seeds up to 64 bits. This significantly improved the performace of my program for large pictures.

---

### List whatever help (if any) you received from the instructor,  classmates, or anyone else.

I did this assignment entirely on my own.

---

### Describe any serious problems you encountered.

All resolved!

---

### List any other comments here.