# PS3: DNA Sequence Alignment [PS3-README.md]

***Name:** Seyedsepehr Madani*

***Hours to complete assignment:** ???? hours*

## Questions

---

**Explain which approach you decided to use when implementing (either recursive with memoization, recursive without memoization, dynamic programming or Hirschberg's algorithm). Also describe why you chose this approach and what its pros and cons are.**

Assignment directory:

```text
PS2b
├── sequence
│   └─── <files in sequence.zip>
├── src
│   └─── main.cpp
├── README-PS3.md/pdf (this file)
├── OUTPUT-Valgrind.txt
└── Makefile
```

The program can be run via:

```Bash
make all && ./bin/ED < example10.txt
```

---

**Does your code work correctly with the `endgaps7.txt` test file? This example should require you to insert a gap at the beginning of the Y string and the end of the X string.**

---

**For this question assume `M = N`. Look at your code and determine approximately how much memory it uses in bytes, as a function of `N`. Give an answer of the form `a * N^b` for some constants `a` and `b`, where `b` is an integer. Note `char`s are 2 bytes long, and `int`s are 4 bytes long.**

**Provide a brief explanation. What is the largest N that your program can handle if it is limited to 8GB (billion bytes) of memory?**

`a =`
`b =`
`largest N =`

---

**Run valgrind if you can and attach the output file to your submission. If you cannot run it, explain why, and list all errors you're seeing. If you can run it successfully, does the memory usage nearly match that found in the question above? Explain why or why not.**

---

**For each data file, fill in the edit distance computed by your program and the amount of time it takes to compute it. If you get segmentation fault when allocating memory for the last two test cases (`N = 20000` and `N = 28284`), note this, and skip filling out the last rows of the table.**

| data file        |  distance       time (seconds)     memory (MB)
| -----------------|-----------------------------------------------
| ecoli2500.txt    |
| ecoli5000.txt    |
| ecoli7000.txt    |
| ecoli10000.txt   |
| ecoli20000.txt   |
| ecoli28284.txt   |

---

**For this question assume `M = N` (which is true for the sample files above). By applying the doubling method to the data points that you obtained, estimate the running time of your program in seconds as a polynomial function `a * N^b` of `N`, where `b` is an integer. (If your data seems not to work, describe what went wrong and use the sample data instead.) Provide a brief justification/explanation of how you applied the doubling method.**

**What is the largest `N` your program can handle if it is limited to 1 day of computation? Assume you have as much main memory as you need.**
`a =`
`b =`
`largest N =`

---

**Did you use the lambda expression in your assignment? If yes, where? Describe a method or provide lines numbers.**

---

**List whatever help (if any) you received from the instructor, classmates, or anyone else.**

---

**Describe any serious problems you encountered.**

---

**List any other comments here.**
