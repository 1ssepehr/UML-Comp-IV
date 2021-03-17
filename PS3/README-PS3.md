# PS3: DNA Sequence Alignment [PS3-README.md]

***Name:** Seyedsepehr Madani*

***Hours to complete assignment:** 6 hours*

## Questions

---

**Explain which approach you decided to use when implementing (either recursive with memoization, recursive without memoization, dynamic programming or Hirschberg's algorithm). Also describe why you chose this approach and what its pros and cons are.**

I used the dynamic programming approach since it was the most reasonable method (with the same running-time as Hirschberg's algorithm). For memory allocation I used a `std::unique_ptr` array of `std::unique_ptr` with type `std::int16_t`, so that memory management would be simple and safe.

This approach has the best order of running time (that is, `O(m*n)`, same as Hirschberg's algorithm) and is relatively easy to implement. It will however use too much memory (as during each stage in the algorithm, we only need the most recent row and most recent column, so memory usage can be reduced from `O(m*n)` to `O(m+n)`).

Assignment directory:

```text
PS2b
├── sequence
│   └─── <files in sequence.zip>
├── src
│   └─── main.cpp ED.cpp ED.hpp
├── README-PS3.md/pdf (this file)
└── Makefile
```

The program can be run via:

```Bash
make all && ./bin/ED < example10.txt
```

⚠ It's advised to redirect the output to a file rather than the terminal for large inputs, like so:

```Bash
make all && ./bin/ED < ecoli2500.txt > output
```

---

**Does your code work correctly with the `endgaps7.txt` test file? This example should require you to insert a gap at the beginning of the Y string and the end of the X string.**

Yes, the program correctly identifies. The output is as follows:

```text
Edit distance = 4
a - 2
t t 0
a a 0
t t 0
t t 0
a a 0
t t 0
- a 2
```

---

**For this question assume `M = N`. Look at your code and determine approximately how much memory it uses in bytes, as a function of `N`. Give an answer of the form `a * N^b` for some constants `a` and `b`, where `b` is an integer. Note `char`s are 2 bytes long, and `int`s are 4 bytes long.**

**Provide a brief explanation. What is the largest `N` that your program can handle if it is limited to 8GB (billion bytes) of memory?**

Since I'm using `std::int16_t` for matrix element type, it will be 2 bytes per element. We have `N^2` elements, so that gives us `a = 2` and `b = 2`, or `2N^2` bytes of memory in total.

The largest `N` that the program can handle is about 70000 on my machine (with 10 GB of free RAM).
My Ubuntu on idle has around 10 GB of free RAM, which using the estimation above, gives us a string size of 70000.
For 8 GB, the number would be about 63250.

---

**Run `valgrind` if you can and attach the output file to your submission. If you cannot run it, explain why, and list all errors you're seeing. If you can run it successfully, does the memory usage nearly match that found in the question above? Explain why or why not.**

Yes! The memory allocation matches what I expected for `ecoli2500.txt`, which is `2 * 2500 * 2500 = 12,500,000 = 11.9 MiB`.
The `massif-visualizer` tool shows `12.1 MiB` of used memory for the same program (which is expected, as the entirety of the program uses more heap allocations, possibly with string constants).

---

**For each data file, fill in the edit distance computed by your program and the amount of time it takes to compute it. If you get segmentation fault when allocating memory for the last two test cases (`N = 20000` and `N = 28284`), note this, and skip filling out the last rows of the table.**

| data file          |  distance   |  time (seconds)   | memory (MB)
| -------------------|-------------|-------------------|-------------
| `ecoli2500.txt`    | 118         | 1.08s             | 12.7 MB
| `ecoli5000.txt`    | 160         | 4.49s             | 50.3 MB
| `ecoli7000.txt`    | 194         | 8.13s             | 201.6 MB
| `ecoli10000.txt`   | 223         | 16.04s            | ~800 MB (?)
| `ecoli20000.txt`   | ?           | ?                 | ?
| `ecoli28284.txt`   | ?           | ?                 | ?

* My CPU is an Intel Core i7 9750H, with a clock speed of 2.60 GHz, on native Ubuntu 20.04 (not VM).

* For entries with question mark, I could not get a result within a reasonable amount of time. Particularly for the memory, `valgrind` would simply take too long.

---

**For this question assume `M = N` (which is true for the sample files above). By applying the doubling method to the data points that you obtained, estimate the running time of your program in seconds as a polynomial function `a * N^b` of `N`, where `b` is an integer. (If your data seems not to work, describe what went wrong and use the sample data instead.) Provide a brief justification/explanation of how you applied the doubling method.**

**What is the largest `N` your program can handle if it is limited to 1 day of computation? Assume you have as much main memory as you need.**

The ration of time and `N` from the data shows a clear quadratic relation between `N` and running time, meaning that the algorithm runs in `O(N^2)` time (or `a = 2`). Putting `N = 10,000` gives us `b = 1.6e-9`.

One day is 86400 seconds, giving us `N` = about 73400.

---

**Did you use the lambda expression in your assignment? If yes, where? Describe a method or provide lines numbers.**

I did not use lambda expressions for this assignment.

---

**List whatever help (if any) you received from the instructor, classmates, or anyone else.**

I did this assignment on my own.

---

**Describe any serious problems you encountered.**

I had no problems during this assignment.

---

**List any other comments here.**
