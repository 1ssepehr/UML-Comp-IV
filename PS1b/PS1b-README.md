# Linear Feedback Shift Register: PhotoMagic (Part B) [PS1b-README.md]

***Name:** Seyedsepehr Madani*

***Hours to complete assignment:** 8 hours*

## Questions

---

**Briefly discuss the assignment itself and what you accomplished.**

In this assignment, we encode an input image with an LFSR seed, and use the same seed to decode the image back to its original.

The encoding process is to XOR every pixel's RGB value with the 8-bit code generated from the LFSR. If given the same seed to the encoded image, we will receive the original photo since `A ^ B ^ B == A`.

I wrote a revised unit test for this assignment as well.

Assignment directory:

```text
PS1b
├── screenshots
│   └─── encode.png, decode.png
├── src
│   └─── main.cpp, FibLFSR.hpp, FibLFSR.cpp, PhotoMagic.hpp, PhotoMagic.cpp
├── test
│   └─── test.cpp (Boost's Unit Test)
├── PS1b-README.md/pdf (this file)
├── wolf.png, juggernaut.png
└── Makefile
```

The test can be run via:

```Bash
make test && ./bin/boost_test
```

The program can be run via:

```Bash
make all && ./bin/PhotoMagic wolf.png wolf_out.png [Your_Passphrase]
```

---

**If you did any implementation for extra credit, describe it here and why it is interesting.**

For the extra credit part, I use the well-known [djb2 hash algorithm](http://www.cse.yorku.ca/~oz/hash.html) to hash the string value of the keyphrase into a 64-bit `unsigned long long` hash value, which I direcly use to create a 64-bit-long LSFR.

In PS1a, I had been using `std::vector<bool>` for emulating the register, which in hindsight was terribly inefficient. Instead, I switched my register container to a `unsigned long long` (guarantee of 64 bits from C++11) and used bitwise operations for the linear feedback function in `step()`. This was simple, safe, memory-efficient, and allowed for seeds up to 64 bits (good enough!). This significantly improved the performace of my program for large pictures.

---

**List whatever help (if any) you received from the instructor,  classmates, or anyone else.**

I did this assignment entirely on my own.

---

**Describe any serious problems you encountered.**

All resolved!

---

**List any other comments here.**
