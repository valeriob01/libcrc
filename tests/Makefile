SOURCES := $(shell find . -name "*.c")

BLOBS := $(shell find bin -name "*.bin")
BLOBS := $(BLOBS:.bin=.bin.o)

OBJECTS := $(SOURCES:.c=.o)

CFLAGS = -Wall -O0 -D_GNU_SOURCE
LDLIBS = -lcrc
LDFLAGS = -L..
all: tests

tests: $(OBJECTS)
 # Making the library
	make -C .. libcrc.so
	# Making the object files from binary blobs
	make -C bin objects
 # Compiling everything together
	$(CC) $(OBJECTS) $(BLOBS) -o $@ $(LDFLAGS) $(LDLIBS) $(CFLAGS)

%.o: %.cc
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

run_tests:
	@make -B tests
	@echo "-----------------------------"
	@echo  "------- Running tests -------"
	@echo "-----------------------------"
	@export LD_LIBRARY_PATH=./.. && ./tests

clean:
	make -C bin $@
	rm -f $(OBJECTS)
	rm -f tests

.PHONY: clean
