CC := g++
CFLAGS := -Wall -std=c++17
LDFLAGS := -lstdc++ -lglfw -lGL -lGLEW
CLIB = -I./lib/portaudio/include ./lib/portaudio/lib/.libs/libportaudio.a -lrt -lasound -ljack -pthread

SRCDIR := src
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:.cpp=.o)

TARGET := app

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS) $(CLIB)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	
install-deps:
	mkdir -p lib

	curl  http://files.portaudio.com/archives/pa_stable_v190700_20210406.tgz | tar -zx -C lib
	cd lib/portaudio && ./configure && $(MAKE) -j

.PHONY: install-deps

uninstall-deps:
	cd lib/portaudio && $(MAKE) uninstall
	rm -rf lib/portaudio
.PHONY: uninstall-deps
