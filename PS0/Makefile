CC=g++
LFLAGS= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
CFLAGS= -Wall -Werror -pedantic

sfml-app: game.o asteroid.o spaceship.o
	$(CC) -o $@ $^ $(LFLAGS) $(CFLAGS)

game.o: game.cpp game.hpp asteroid.hpp spaceship.hpp globals.hpp
	$(CC) -o $@ $< $(CFLAGS) -c

asteroid.o: asteroid.cpp asteroid.hpp game.hpp globals.hpp
	$(CC) -o $@ $< $(CFLAGS) -c

spaceship.o: spaceship.cpp spaceship.hpp game.hpp globals.hpp
	$(CC) -o $@ $< $(CFLAGS) -c

clean:
	rm -f *.o
	rm -f sfml-app
