# Windows Makefile for image_processor project using MinGW

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Source files
SRCS = main.c bmp_io.c resize.c enhance.c otsu.c save_h_file.c

# Object files
OBJS = main.o bmp_io.o resize.o enhance.o otsu.o save_h_file.o

# Output executable
TARGET = image_processor.exe

# Default rule
all: $(TARGET)

# Link object files to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the executable (Windows syntax)
run: all
	$(TARGET)

# Remove build artifacts (Windows-friendly clean)
clean:
	del /Q $(OBJS) $(TARGET) 2>nul || exit 0

.PHONY: all run clean