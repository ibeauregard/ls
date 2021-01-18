CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
TARGET = my_ls

$(TARGET):
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) my_ls