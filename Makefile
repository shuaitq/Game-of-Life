CC		=g++
SIGN	=-O2 -std=c++0x -fopenmp
OBJS	=game.o image.o screen.o
NAME	=game.out
$(NAME):$(OBJS)
	$(CC) $(SIGN) $(OBJS) -o $(NAME)
game.o:game.cpp
	$(CC) $(SIGN) -c game.cpp
image.o:src/image.h src/image.cpp
	$(CC) $(SIGN) -c src/image.cpp
screen.o:src/screen.h src/screen.cpp
	$(CC) $(SIGN) -c src/screen.cpp
.PHONY: clean
clean:
	rm -f $(OBJS)