CC = cl65
ASSET_TOOL = c1541
TARGET = c64
PROGRAM = diskspeed.prg
DISK = diskspeed.d64
SOURCE = diskspeed.c
TESTDATA = testdata

.PHONY: all clean

all: $(DISK)

$(PROGRAM): $(SOURCE)
	$(CC) -O -t $(TARGET) $(SOURCE) -o $(PROGRAM)

$(DISK): $(PROGRAM) $(TESTDATA)
	rm -f $(DISK)
	$(ASSET_TOOL) -format "diskspeed,01" d64 $(DISK)
	$(ASSET_TOOL) -attach $(DISK) -write $(PROGRAM) diskspeed
	@echo "Writing testdata to disk..."
	$(ASSET_TOOL) -attach $(DISK) -write $(TESTDATA) testdata

clean:
	rm -f $(PROGRAM) $(DISK) *.o
