SOURCES := $(shell find . -name "*.c")
BLOBS := $(shell find bin -name "*.bin")
OBJECTS := $(SOURCES:.c=.o)

CFLAGS = -Wall -O0 -D_GNU_SOURCE
LDLIBS = -lcrc
LDFLAGS = -L..
all: tests

tests: $(OBJECTS)
	make -C .. libcrc.so
	$(CC) $(OBJECTS) $(BLOBS) -o $@ $(LDFLAGS) $(LDLIBS) $(CFLAGS)

%.o: %.cc
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

run_tests:
	@make -B tests
	@echo "*** Running tests ***"
	@export LD_LIBRARY_PATH=./.. && ./tests

clean:
	rm -f $(OBJECTS)
	rm -f tests

.PHONY: clean
