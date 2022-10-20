EXES = main
OBJS = main.o player.o playerManager.o
CC = g++
CFLAG = -c -g
LFLAG = -pthread

All: $(EXES)
$(EXES): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LFLAG)
.cpp.o:
	$(CC) $(CFLAG) $<
clean:
	rm $(EXES) $(OBJS)