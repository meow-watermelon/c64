CC = cl65
ASSET_TOOL = c1541
TARGET = c64
PROGRAM = snoopy.prg
DISK = snoopy.d64
SOURCE = snoopy.c

ASSETS = $(shell printf 's%d.bin ' {1..12})

.PHONY: all clean

all: $(DISK)

$(PROGRAM): $(SOURCE)
	$(CC) -O -t $(TARGET) $(SOURCE) -o $(PROGRAM)

$(DISK): $(PROGRAM) $(ASSETS)
	rm -f $(DISK)
	$(ASSET_TOOL) -format "snoopy,01" d64 $(DISK)
	$(ASSET_TOOL) -attach $(DISK) -write $(PROGRAM) snoopy
	@for file in $(ASSETS); do \
		echo "Writing $$file to disk..."; \
		$(ASSET_TOOL) -attach $(DISK) -write $$file $$file; \
	done

clean:
	rm -f $(PROGRAM) $(DISK) *.o
