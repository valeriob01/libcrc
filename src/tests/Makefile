#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>
#
# Author: Marco Guerri <marco.guerri.dev@fastmail.com>
#

SOURCES := $(shell find . -name "*.c")

BLOBS := $(shell find bin -name "*.bin")
BLOBS := $(BLOBS:.bin=.bin.o)

OBJECTS := $(SOURCES:.c=.o)

CFLAGS = -Wall -O0 -D_GNU_SOURCE
LDLIBS = -lcrc -lrt
LDFLAGS = -L../../bin
all: tests

tests: $(OBJECTS)
	make -C ../.. libcrc.so
	make -C bin objects
	$(CC) $(OBJECTS) $(BLOBS) -o $@ $(LDFLAGS) $(LDLIBS) $(CFLAGS)

%.o: %.cc
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

run_tests:
	@make -B tests
	@echo "-----------------------------"
	@echo  "------- Running tests -------"
	@echo "-----------------------------"
	@export LD_LIBRARY_PATH=../../bin && ./tests

clean:
	make -C bin $@
	rm -f $(OBJECTS)
	rm -f tests

.PHONY: clean
