# PS2: N-Body Simulation (Part A) [PS2a-README.md]

***Name:** Seyedsepehr Madani*

***Hours to complete assignment:** 4 hours*

## Questions

---

**Briefly discuss the assignment itself and what you accomplished.**

In this assignment, we lay the basic groundwork for a physical simulation of a, N-body gravitational system.
As of the requirements of the assignment, we will not be concerned with animating the bodies.

I created two classes: `Universe` and `CelestialBody`. The names are expressive in what each class does.
The `Universe` class inherits from `sf::RenderWindow` to internally manage the event loop of the window. It also has a vector `std::vector<std::unique_ptr<CelestialBody>>` as the container for the bodies in the universe.

Assignment directory:

```text
PS2a
├── assets
│   └─── <files in nbody.zip>
├── src
│   └─── main.cpp, Universe.hpp, Universe.cpp, CelestialBody.hpp, CelestialBody.cpp
├── PS2a-README.md/pdf (this file)
└── Makefile
```

The program can be run via:

```Bash
make all && ./PS2a < ./assets/planets.txt
```

---

**Discuss one or more key algorithms, data structures, or OO designs that were central to the assignment.**

Rather than having my `main` program manage the `sf::RenderWindow` and grab the information from the `Universe`, I decided to have the `Universe` class inherit directly from `sf::RenerWindow`. This way, there was no need to write getter functions for the `std::vector` container of `CelestialBody`s in the `Universe` class to access them in `main`. This significantly simplified the design of the `Universe`.

---

**Briefly explain the workings of the features you implemented. Describe if and how do you used the smart pointers. Include code excerpts.**

For smart pointers, I used a `std::vector` of `unique_ptr<CelestialBody>` pointers. I would make a `unique_ptr<CelestialBody>` pointing to an empty `CelestialBody` object, extract the information from `std::cin` (and initialize the object), and push it to the vector via move semantics, i.e. `std::move()`.

```c++
for (unsigned i = 0; i < N; i++)
{
    std::unique_ptr<CelestialBody> thisBody(new CelestialBody());
    std::cin >> *thisBody;  // After std::cin, the state of *thisBody will be initialized.
    bodyVec.push_back(std::move(thisBody));
}
```

Given that I had `Universe` inherit directly from the `sf::RenderWindow` class, I'd simple do the following for drawing the bodies in the universe.

```c++
for (auto& body: bodyVec)
{
    float x_display = center_x + (body->getX() / (2*R) * width);
    float y_display = center_y + (body->getY() / (2*R) * height);
    body->setPosition(x_display, y_display);
    draw(*body);
}
```

---

**List whatever help (if any) you received from the instructor, classmates, or anyone else.**

I did this assignment entirely on my own.

---

**Describe any serious problems you encountered.**

---

**List any other comments here.**

Choosing to have `CelestialBody` inherit from `sf::Drawable` didn't seem like the best design idea. Since I wanted to do `setPosition()` on the sprite of the `CelestialBody` object, it would make sense to also inherit from `sf::Transformable`. But in fact, `sf::Sprite` is already a better choice since it already inherits from `sf::Drawable` and `sf::Transformable`. So it would make much more sense to extend `sf::Sprite` to `CelestialBody`.
