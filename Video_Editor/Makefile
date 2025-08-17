
CC = gcc
CFLAGS = -O3 -fsanitize=address -fsanitize=undefined -fsanitize=leak -fsanitize=pointer-subtract -fsanitize=pointer-compare -Wall -Wextra -march=native -mavx2 -pedantic -std=c11 -g
SRCS = libFilmMaster2000.c main.c
OBJS = $(SRCS:.c=.o)
HEADERS = libFilmMaster2000.h
LIB = libFilmMaster2000.a
EXEC = runme
TEST = test.bin

all: $(LIB) $(EXEC)

$(LIB): libFilmMaster2000.o
	@echo "Creating static library: $@"
	ar rcs $@ $^

$(EXEC): $(OBJS)
	@echo "Creating executable: $@"
	$(CC) $(CFLAGS) -o $@ $^

libFilmMaster2000.o: libFilmMaster2000.c $(HEADERS)
main.o: main.c $(HEADERS)

clean:
	@echo "Cleaning up "
	rm -f $(OBJS) $(LIB) $(EXEC)

test: $(EXEC)
	@echo "Running tests "
	./$(EXEC) $(TEST) reverse.bin -O reverse
	./$(EXEC) $(TEST) reverse_S.bin -S reverse
	./$(EXEC) $(TEST) reverse_M.bin -M reverse
	./$(EXEC) $(TEST) swap.bin -O swap_channel 1,2
	./$(EXEC) $(TEST) swap_S.bin -S swap_channel 1,2
	./$(EXEC) $(TEST) swap_M.bin -M swap_channel 1,2
	./$(EXEC) $(TEST) clip.bin -O clip_channel 1 [10,20]
	./$(EXEC) $(TEST) clip_S.bin -S clip_channel 1 [10,20]
	./$(EXEC) $(TEST) clip_M.bin -M clip_channel 1 [10,20]
	./$(EXEC) $(TEST) scale.bin -O scale_channel 1 2.0
	./$(EXEC) $(TEST) scale_S.bin -S scale_channel 1 2.0
	./$(EXEC) $(TEST) scale_M.bin -M scale_channel 1 2.0

	@echo "Tests completed."

.PHONY: all clean test
