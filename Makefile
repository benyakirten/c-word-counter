# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

# Source files
SRCS = word_count.c hashmap.c array_list.c read_file.c
OBJS = $(SRCS:.c=.o)

# Header dependencies
word_count.o: word_count.c hashmap.h array_list.h read_file.h
hashmap.o: hashmap.c hashmap.h array_list.h read_file.h
array_list.o: array_list.c array_list.h
read_file.o: read_file.c read_file.h array_list.h

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
