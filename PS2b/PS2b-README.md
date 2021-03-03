# PS2: N-Body Simulation (Part B) [PS2a-README.md]

***Name:** Seyedsepehr Madani*

***Hours to complete assignment:** 11 hours*

## Questions

---

**Briefly discuss the assignment itself and what you accomplished.**

In this assignment, we continue the simulation of the Newtonian gravitational forces between a number of celestial bodies in a universe, building upon PS2a codebase by adding animations, music, timer, and other features.

I used the [Runge-Kutta 4th-order](https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods) method for approximating the position and velocity of the bodies rather than the the simple approximation given on the handout for better accuracy. The increased accuracy of using Runge-Kutta (with the total accumulated of O(h^4) error) would far outweigh the the computational overhead of the `step()` function, and actually result in more accurate simulations.

A comparison between the normal computation and the one carried out using Runge-Kutta methods can be found in `Runge-Kutta.webm`, and `Runge-Kutta.png`.

I programmed the formulas as obtained from [this paper by C.J. Voesenek](http://spiff.rit.edu/richmond/nbody/OrbitRungeKutta4.pdf).

Assignment directory:

```text
PS2b
├── assets
│   └─── <files in nbody.zip>
├── src
│   └─── main.cpp, Universe.hpp, Universe.cpp, CelestialBody.hpp, CelestialBody.cpp
├── PS2b-README.md/pdf (this file)
├── Runge-Kutta.webm/png
└── Makefile
```

The program can be run via:

```bash
make all && ./bin/NBody 157788000.0 25000.0 < ./assets/planets.txt
```

For the sample run of the universe used in the video, use `./assets/dance10.txt`.

---

**If you created your own universe for extra credit, describe it here and why it is interesting.**

---

**List whatever help (if any) you received from the instructor, classmates, or anyone else.**

I had my brother help me understand the mathematics behind the Runge-Kutta method.

---

**Describe any serious problems you encountered.**

---

**List any other comments here.**
