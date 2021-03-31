# PS4b: StringSound implementation and SFML Audio output [README-PS4b.md]

***Name:** Seyedsepehr Madani*

***Hours to complete assignment:** 7 hours*

---

## Questions

**Did you complete the whole assignment? Successfully or not? Indicate which parts you think are working, and describe how you know that they're working.**

This assignment was successfully finished. I made the simulator for the guitar to work, with proper sounds and controls. The unit test also functions properly. The only missing component (which is left for future attempts) is highlighting the pressed key on the simulator display.

I also configured my Makefile to be able to make two different targets; (1) `test` for Boost's unit testing of `StringSound`, and (2) `build` for our guitar simulator.

Assignment directory:

```text
PS4b
├── src
│   └─── boosttest.cpp, Guitar.hpp,
│        CircularBuffer.cpp, CircularBuffer.hpp,
│        StringSound.cpp, StringSound.hpp,
│        KSGuitarSim.cpp 
├── README-PS4b.md/pdf (this file)
└── Makefile
```

For building the program, run:

```Bash
make build && ./KSGuitarSim
```

For running the unit test module for `StringSound`, run:

```Bash
make test && ./boosttest --log_level=all
```

---

**Did you attempt the extra credit parts? Which one(s)? Successfully or not?**

I made an attempt at making out a piano sound, as per the information I found on [Mike Moreno's project](https://forum.pdpatchrepo.info/topic/12331/karplus-strong-piano-pure-data-instrument), a demo of different instrument sounds from pure data. Unfortunately, I could not finish it by the assignment deadline, and as such, I am leaving this for future development.

---

**Did you implement exceptions to check your `StringSound` implementation? Indicate yes or no, and explain how you did it.**

Yes, I did. I also tested these exceptions through a unit test module under Boost's Unit Testing Framework. This test can be run with:

```Bash
make test && ./boosttest --log_level=all
```

---

**Did you implement lambda expression? Indicate yes or no, and explain how you did it.**

Yes. For the formula of calculating frequency in `KSGuitarSim.cpp`, I decided to use a lambda expression function to make the code more readable. This made the argument list for the `makeSamplesFromString` function become clear.

---

**Did your code pass cpplint? Indicate yes or no, and explain how you did it.**

Yes. I installed [cpplint v1.5.4 from PyPI](https://pypi.org/project/cpplint/), then used the \[unofficial\] [cpplint extension for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=mine.cpplint) for looking through my code. All errors from cpplint would be visible as warnings in the editor. This made for a very pleasing experience in linting my code.

I also used `clang-format` for formatting the spaces in my code using Google's style (again, through the [clangd extension for VSCode](https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd)).

---

**List whatever help (if any) you received from the instructor, classmates, or anyone else.**

I did this assignment on my own.

---

**Describe any serious problems you encountered.**

I had no problems during this assignment.

---

**List any other comments here.**
