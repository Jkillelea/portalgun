CC = avr-g++ -mmcu=atmega88
OBJCOPY = avr-objcopy
LD = avr-ld
PROGTOOL = avrdude -qq -p m88p
PROGPROTOCOL = avrispmkii

CFLAGS = -I/usr/lib/avr/include
CFLAGS += -O3
CFLAGS += -DF_CPU=8000000L
CFLAGS += -D__AVR_ATmega88__

.PHONY: all
all: flash

# don't need to call multiple times
.PHONY: fuses
fuses:
	$(PROGTOOL) -c $(PROGPROTOCOL) -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m -U efuse:w:0xf9:m 

.PHONY: flash
flash: main.hex
	$(PROGTOOL) -c $(PROGPROTOCOL) -U flash:w:$^

main.hex: main.elf
	$(OBJCOPY) -O ihex -R .eeprom $^ $@

main.elf: main.cpp interrupts.c
	$(CC) $(CFLAGS) -o $@ $^
	$(LD) --print-memory-usage $@

.PHONY: clean
clean:
	rm *.elf
	rm *.hex
	rm a.out

