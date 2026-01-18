# Compiler and flags
CC = gcc
CFLAGS = -Wall -O2 -I./include
LDFLAGS = -lm

# Directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin
DATADIR = data

# Source files
SOURCES = $(SRCDIR)/main.c $(SRCDIR)/lattice.c $(SRCDIR)/simulation.c \
          $(SRCDIR)/measurements.c $(SRCDIR)/fileio.c
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TARGET = $(BINDIR)/ising

# Ensure directories exist
$(shell mkdir -p $(OBJDIR) $(BINDIR) $(DATADIR))

# Default target
all: $(TARGET)

# Create executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile source files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Clean everything including data
distclean: clean
	rm -rf $(DATADIR) ../plots

.PHONY: all clean distclean