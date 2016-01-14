CC	=g++
SIGN=-O2 -std=c++11
main.out:main.o cell.o image.o screen.o	src/cell.h src/image.h src/screen.h
	$(CC) $(SIGN) main.o cell.o image.o screen.o -o main.out
main.o:main.cpp
	$(CC)  $(SIGN) -c main.cpp
cell.o:src/cell.h src/cell.cpp
	$(CC)  $(SIGN) -c src/cell.cpp
image.o:src/image.h src/image.cpp
	$(CC)  $(SIGN) -c src/image.cpp
screen.o:src/screen.h src/screen.cpp
	$(CC)  $(SIGN) -c src/screen.cpp
clean:
	rm *.o