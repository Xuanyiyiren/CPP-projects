## Version 5
CC = gcc
CFLAGS = -c -Wall
TARGET = mat_mul
SRC = $(wildcard *.c) 
# wildcard function will search all the matched files and stored their name
OBJ = $(patsubst %.c, %.o, $(SRC))
# patsubst will substitute ".c" to ".o" for all files in $(SRC)
DEP = $(patsubst %.c, %.d, $(SRC))
# patsubst will substitute ".c" to ".d" for all files in $(SRC)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^
# $@ stand for target
# $^ stand for objects

%.o: %.c
	$(CC) -c $(CFLAGS) -MMD -MP $< -o $@
# $< stand for the first object
# -MMD: Generate dependency file
# -MP: Create phony targets for each header file

-include $(DEP)
# Include dependency files

.PHONY: clean
clean:
	rm -f *.o *.d $(TARGET)