# Compiler
CC = g++

# Compiler flags
CFLAGS = -std=c++2a -Wno-narrowing

# Linker flags
LDFLAGS =

# Executable names
EXE1 = one
EXE2 = two

# Default target
all: $(EXE1) $(EXE2)

# Executable files
$(EXE1): partOne.o
	$(CC) $(LDFLAGS) -o $@ $^

$(EXE2): partTwo.o
	$(CC) $(LDFLAGS) -o $@ $^

# Object files
partOne.o: One.cc
	$(CC) $(CFLAGS) -c $< -o $@

partTwo.o: Two.cc
	$(CC) $(CFLAGS) -c $< -o $@
