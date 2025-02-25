# Define the C compiler to use
CC=gcc

# Define any compile-time flags
CFLAGS=-Wall -g  # -Wall: Enable all warning messages, -g: Add debugging information

# Define the target executable name
TARGET=SJF RR

# 'all' is the default target. It's customary to have it as the first target.
# This target will be executed when you just type 'make' in the terminal.
all: $(TARGET)

# Rule to compile SJF.c into SJF executable
SJF: SJF.c
	$(CC) $(CFLAGS) -o SJF SJF.c

# Rule to compile rr.c into rr executable
RR: RR.c
	$(CC) $(CFLAGS) -o RR RR.c

# Clean up the compiled files
clean:
	rm -f $(TARGETS)