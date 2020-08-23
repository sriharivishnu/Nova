# the compiler: gcc for C program, define as g++ for C++
CC := g++
INCLUDES := -Iinclude/ -I../include/
SRCDIR := src
BUILDDIR := build
TARGET := nova

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  := -g -Wall -std=c++11
SRCS := $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS := $(SRCS:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(INCLUDES) -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(BUILDDIR)
	cd $(BUILDDIR) && $(CC) $(CFLAGS) $(INCLUDES) -c ../$< && cd ..

clean:
	[ -d $(BUILDDIR) ] && rm -r $(BUILDDIR) 
	[ -e $(TARGET) ] && rm $(TARGET)