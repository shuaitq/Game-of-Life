CC      =g++
SIGN    =-O2 -std=c++11
OBJS    =Game.o RLEFile.o PPMFile.o
NAME    =Game.out
$(NAME):$(OBJS)
	$(CC) $(SIGN) $(OBJS) -o $(NAME)
Game.o:Game.cpp
	$(CC) $(SIGN) -c Game.cpp
RLEFile.o:Utility/RLEFile.h Utility/RLEFile.cpp
	$(CC) $(SIGN) -c Utility/RLEFile.cpp
PPMFile.o:Utility/PPMFile.h Utility/PPMFile.cpp
	$(CC) $(SIGN) -c Utility/PPMFile.cpp
.PHONY: clean
clean:
	rm -f $(OBJS)