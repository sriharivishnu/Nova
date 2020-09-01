CC := g++
INCLUDES := -Iinclude/
SRCDIR := src
BUILDDIR := build
TARGET := nova

CFLAGS  := -g -Wall -std=c++17
SRCS := $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS := $(SRCS:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(INCLUDES) -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c -MMD $< -o $@

-include $(BUILDDIR)/*.d
clean:
	[ -d $(BUILDDIR) ] && rm -r $(BUILDDIR) 
	[ -e $(TARGET) ] && rm $(TARGET)