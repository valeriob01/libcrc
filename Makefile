SOURCES := $(shell find . -path ./tests  -prune -o -name "*.c" -print)
OBJECTS := $(SOURCES:.c=.o)

CFLAGS = -Wall -O0 -fPIC -D_GNU_SOURCE
LDFLAGS = -shared
all: libcrc.so

libcrc.so: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDLIBS) $(LDFLAGS) $(CFLAGS)

%.o: %.cc
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f libcrc.so

.PHONY: clean
