#Jessica Valenzuela
#I pledge my honor that I have abided by the Stevens Honors System

CC = gcc
OBJS = cs392_thread.o
RM = rm -rf
LDFLAGS = -pthread

cs392_thread: $(OBJS)

cs392_thread.o: cs392_thread.c 
	$(CC) -o cs392_thread.o -c cs392_thread.c -pthread

	
clean: 
	$(RM) *.o 
	$(RM) cs392_thread

re: clean cs392_thread