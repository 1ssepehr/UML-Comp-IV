CC=g++
SFML_FLAG= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
FLAGS= -Wall -Werror -pedantic

sfml-app: game.o
	$(CC) -o $@ $^ $(SFML_FLAG) $(FLAGS)

game.o: game.cpp game.hpp
	$(CC) -o $@ $< $(FLAGS) -c

clean:
	rm -f *.o
	rm -f sfml-app
