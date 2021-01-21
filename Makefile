SRCS := $(wildcard *.c)
BINS := $(SRCS:%.c=%)

.PHONY = all

CC = gcc                        # compiler to use

LINKERFLAG = -lm
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

all: ${BINS}

%: %.o
	@echo "Checking.."
	${CC} ${LINKERFLAG} $< -o $@

%.o: %.c
	@echo "Creating object.."
	${CC} ${CFLAGS} $<

clean:
	@echo "Cleaning up..."
	rm -rvf *.o ${BINS}