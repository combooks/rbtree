OBJECTS = main.o rbtree.o
TARGET = test
CC = gcc
CFLAGS = -W -Wall -Wextra -Werror -g -Wno-unused-parameter

$(TARGET):$(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

.c.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f $(TARGET) $(OBJECTS)
