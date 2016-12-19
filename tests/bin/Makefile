BLOBS := $(shell find . -name "*.bin")
OBJECTS := $(BLOBS:.bin=.bin.o)

objects:
	$(foreach blob, $(BLOBS), objcopy --input-target binary --output-target elf64-x86-64 --binary-architecture i386:x86-64  $(blob) $(blob).o;)

showarch:
	objdump -f /bin/sh

clean:
	rm $(OBJECTS)

.PHONY: showarch




