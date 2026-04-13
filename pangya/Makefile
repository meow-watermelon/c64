CC = cl65
ASSET_TOOL = c1541
TARGET = c64
PROGRAM = pangya.prg
DISK = pangya.d64
SOURCE = pangya.c

ASSETS = $(shell printf 'p%d.bin ' {1..7})

.PHONY: all clean

all: $(DISK)

$(PROGRAM): $(SOURCE)
	$(CC) -O -t $(TARGET) $(SOURCE) -o $(PROGRAM)

$(DISK): $(PROGRAM) $(ASSETS)
	rm -f $(DISK)
	$(ASSET_TOOL) -format "pangya,01" d64 $(DISK)
	$(ASSET_TOOL) -attach $(DISK) -write $(PROGRAM) pangya
	@for file in $(ASSETS); do \
		echo "Writing $$file to disk..."; \
		$(ASSET_TOOL) -attach $(DISK) -write $$file $$file; \
	done

clean:
	rm -f $(PROGRAM) $(DISK) *.o
