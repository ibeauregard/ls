CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -g3
LINKERFLAG = -lm
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
MAIN = my_ls
.PHONY = all clean fclean re

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(LINKERFLAG) $^

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(MAIN)

re: fclean all
