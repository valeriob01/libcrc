SOURCES := $(shell find . -path ./tests  -prune -o -name "*.c" -print)
OBJECTS := $(SOURCES:.c=.o)

CFLAGS = -Wall -O0 -D_GNU_SOURCE
all: libcrc.so

# Compile for Position Independent Code only if shared library
libcrc.so: CFLAGS += -fPIC
libcrc.so: LDFLAGS += -shared

libcrc.so: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDLIBS) $(LDFLAGS) $(CFLAGS)

libcrc.a: $(OBJECTS)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) $(INCLUDES) -c $< -o $@

run_tests:
	make $@ -C tests

clean:
	make -C tests $@
	rm -f $(OBJECTS)
	rm -f libcrc.so

.PHONY: clean
