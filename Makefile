# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

# Source files
SRCS = word_count.c hashmap.c array_list.c words.c
OBJS = $(SRCS:.c=.o)

# Header dependencies
word_count.o: word_count.c hashmap.h array_list.h words.h
hashmap.o: hashmap.c hashmap.h array_list.h words.h
array_list.o: array_list.c array_list.h
words.o: words.c words.h

# Output binary
TARGET = word_count

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
