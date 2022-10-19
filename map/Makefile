EXES = test_main
OBJS = test_main.o map.o
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