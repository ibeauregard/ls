CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
LINKERFLAG = -lm
SRCS = _string.c my_ls.c
OBJS = $(SRCS:.c=.o)
MAIN = my_ls
.PHONY = all clean

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(LINKERFLAG) $(OBJS)
	$(RM) *.o

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) $(MAIN)
