SOURCES := $(shell find . -path ./src/tests -prune -o -name "*.c" -print)
SOURCES_TESTS := $(shell find ./src/tests -name "*.c" -print)

OBJECTS := $(SOURCES:.c=.o)
OBJECTS_TESTS := $(SOURCES_TESTS:.c=.o)

CFLAGS = -Wall -O0 -fPIC -D_GNU_SOURCE -Isrc -Isrc/tests -g
LDFLAGS = -shared
LDFLAGS_TESTS = -Lbin
LDLIBS_TESTS = -lcrc

all: libcrc.so

libcrc.so: $(OBJECTS)
	@install -d bin -m 755
	$(CC) $(OBJECTS) -o bin/$@ $(LDLIBS) $(LDFLAGS) $(CFLAGS)

%.o: %.cc
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

tests: libcrc.so
	make -C src/tests

run_tests: tests
	@export LD_LIBRARY_PATH=bin && ./src/tests/tests


clean:
	rm -f $(OBJECTS)
	rm -f bin/*
	make -C src/tests clean

.PHONY: clean
