SOURCES := $(shell find . -path ./tests  -prune -o -name "*.c" -print)
OBJECTS := $(SOURCES:.c=.o)

CFLAGS = -Wall -O0 -D_GNU_SOURCE -fPIC
all: libcrc.so

libcrc.so: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDLIBS) $(LDFLAGS) -shared $(CFLAGS)

libcrc.a: $(OBJECTS)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

run_tests:
	make $@ -C tests

clean:
	make -C tests $@
	rm -f $(OBJECTS)
	rm -f libcrc.so

.PHONY: clean
