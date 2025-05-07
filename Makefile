CC = gcc
CFLAGS = -Wall -Wextra -I./src
SRC = src/wukong_engine.c src/stack.c src/main.c
OBJ = $(SRC:.c=.o)
TARGET = chess_engine

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)