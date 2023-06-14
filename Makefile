CC := g++
CFLAGS := -Wall -std=c++17
LDFLAGS := -lstdc++ -lglfw -lGL -lGLEW

SRCDIR := src
SOURCES := $(wildcard $(SRCDIR)/**/*.cpp $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:.cpp=.o)

TARGET := app

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)