# PS6: Kronos [PS6-README.md]

***Name:** Seyedsepehr Madani*

***Hours to complete assignment:** ???? hours*

## Questions

---

**Did you complete the whole assignment? Successfully or not? Indicate which parts you think are working, and describe how you know that they're working.**

Yes, I completed this assignment completely. I compared the output of my program agianst the given file, `device5_intouch.log_BOOT.rpt` (although I removed the extra diagnostics info regarding *services* from it) and made sure that the outputs match perfectly.

Assignment directory:

```text
PS6
├── kronos
│   ├─── device1_intouch.log.rpt
│   ├─── device2_intouch.log.rpt
│   ├─── device3_intouch.log.rpt
│   ├─── device4_intouch.log.rpt
│   ├─── device5_intouch.log.rpt
│   └─── device6_intouch.log.rpt
├── src
│   ├─── intouch_boot.hpp
│   └─── main.cpp
├── README-PS6.md/pdf (this file)
└── Makefile
```

To run the program, simply run:

```bash
make all && ./ps6 [input-log-file-for-intouch-device]
```

---

**Copy here all regex's you created for parsing the file, and explain individually what each ones does.**

I had the following regular expressions:
* `\(log\.c\.166\) server started`: For marking the start of a booting sequence, and
* `oejs\.AbstractConnector:Started SelectChannelConnector`: For observing the successful completion of a booting sequence attempt.

For extracting the timestamps, I simply used a substring of the first 19 characters of the log entry line with `boost::posix_time::time_from_string()`, rather than a possibly complicated regex.

---

**Describe your overall approach for solving the problem. 100-200 words.**

The approach was simple: read the log file line by line, and see whether that line reports a boot starting event, a boot completion event, or something else. With keeping track of whether the machine is in the process of booting or not, we can create a simple report from parsing the log file linearly in a top-down fashion. 

---

**Did you use lambda expression? If yes describe there.**
Yes, I used the follwing lambda expression:

```c++
// Lambda expression to extract the timestamp substring from log entries
auto extract_time = [](std::string x) { return x.substr(0, 19); };
```

This was a simple calculation with a magic number that I didn't want to duplicate throughout the report-generation code, so I made it into a lambda expression. I used this over a function because it's easier to inline the calculation, and it wasn't necessary to expose the API to any other scope.

---

**List whatever help (if any) you received from the instructor, classmates, or anyone else.**

I did this assignment on my own.

---

**Describe any serious problems you encountered.**

---

**List any other comments here.**
