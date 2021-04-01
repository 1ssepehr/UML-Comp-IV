# PS5: Recursive Graphs (Triangle Fractal) [PS5-README.md]

***Name:** Seyedsepehr Madani*

***Hours to complete assignment:** 3 hours*

## Questions

---

**Briefly discuss the assignment itself and what you accomplished.**

In this assignment, I implemented a recursive solution for graphing a variation of the famous [Sierpinski's Triangles](https://en.wikipedia.org/wiki/Sierpi%C5%84ski_triangle).

I created a `Triangle` class which was drawn from `sf::Drawable` to represent each triangle. My recursive function of `fTree()`, would take a center coordinate and the recursion depth `N` (along with other parameters) to draw the base triangle, and recursively draw the next depth layer.

There are additional controls for the program to change colors, increase/decrease side length of depth level, change drawing style, and change colors. All controls are shown on the top-left corner of the program window.

Assignment directory:

```text
PS5
├── assets
│   └─── Oxanium.ttf
├── src
│   └─── Triangle.cpp, Triangle.hpp,
│        TFractal.cpp
├── README-PS5.md/pdf (this file)
└── Makefile
```

To run the program, simply run:

```bash
make all && ./TFractal 300 5
```

---

**Discuss one or more key algorithms, data structures, or OO designs that were central to the assignment.**

The central idea to this assignment was understanding the recursion.
First, we make our `Triangle` to be drawn using its center point and side length.
Then, for the call to `fTree()` with depth of `N` and side length of `L`, we draw the base triangle, calculate the center coordinates of each of the three child triangles, then recursively call `fTree()` with `N - 1` and `L/2`.

Finally, we can call `fTree()` to put all these `Triangle` objects into an `std::vector`, draw it on each event loop cycle, clear the vector, and repeat.

---

**Briefly explain the workings of the features you implemented. Describe if and how do you used the smart pointers. Include code excerpts.**

For the `Triangle` class, internally, I would calculate the three vertices of the triangle from the center point and put them in a `sf::VertexArray` of type either `sf::Triangle` (filled triangle) or `sf::LineStrip` (only the outline). I also added colors to it.

I had my `fTree()` take extra parameters such as color and draw type (filled or hollow), and added keyboard controls for playing with the parameters during runtime, as such:

```c++
while (window.pollEvent(event)) switch (event.type) {
    ...
  case sf::Event::KeyPressed:
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) L -= 20;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) L += 20;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) --N;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) ++N;
    ...
  break;
}

// Recalculate the triangles with [potentially new] parameters
triangles.clear();
fTree(&triangles, {0.5 * w_size, 0.5 * w_size}, L, N, drawType, colorKey);
```

---

**Briefly explain what you learned in the assignment.**

I learned how to create custom shape types in SFML, with dynamic options and flexible definitions for vertices, from [SFML's Shapes page](https://www.sfml-dev.org/tutorials/2.0/graphics-shape.php).
This was particularly useful as it made the calculation of the recursive triangle coordinates easy and straightforward.

I also learned about anti-aliasing in computer graphics to make smooth edges in for distorted artifacts of diagonal lines.

---

**List whatever help (if any) you received from the instructor, classmates, or anyone else.**

I did this assignment on my own.

---

**Describe any serious problems you encountered.**

My only problem was cpplint's warning for the virtual function `draw()`. In SFML's API, `draw()`'s first argument is a non-const reference, `target`. cpplint warns against using non-const references in arguments, because it hides mutability of the passed parameter to the caller (as opposed to a pointer, in which case user needs to explicitly pass the address).

I couldn't break SFML's API (rather, I didn't *want* to, only for satisfying cpplint), so I used `// NOLINT` on that specific line.

---

**List any other comments here.**
