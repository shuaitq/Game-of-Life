CC		=g++
SIGN	=-O2 -std=c++0x
OBJS	=main.o cell.o image.o screen.o rules.o
DELETE	=$(OBJS) photo/* main.out
main.out:$(OBJS)
	$(CC) $(SIGN) $(OBJS) -o main.out
main.o:main.cpp
	$(CC) $(SIGN) -c main.cpp
cell.o:src/cell.h src/cell.cpp
	$(CC) $(SIGN) -c src/cell.cpp
image.o:src/image.h src/image.cpp
	$(CC) $(SIGN) -c src/image.cpp
screen.o:src/screen.h src/screen.cpp
	$(CC) $(SIGN) -c src/screen.cpp
rules.o:src/rules.h src/rules.cpp
	$(CC) $(SIGH) -c src/rules.cpp
.PHONY: clean
clean:
	rm $(OBJS)
.PHONY: gitc
gitc:
	rm -f $(DELETE)
