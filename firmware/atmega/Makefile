CC = avr-g++ -mmcu=atmega48
OBJCOPY = avr-objcopy
LD = avr-ld
PROGTOOL = avrdude -p m48
PROGPROTOCOL = avrispmkii

CFLAGS = -I/usr/lib/avr/include
CFLAGS += -O3
CFLAGS += -DF_CPU=16000000UL
CFLAGS += -D__AVR_ATmega48__

.PHONY: all
all: flash

# don't need to call multiple times
.PHONY: fuses
fuses:
# ATMega48
	$(PROGTOOL) -c $(PROGPROTOCOL) -U lfuse:w:0xC7:m -U hfuse:w:0xDF:m -U efuse:w:0xFF:m -U lock:w:0xFF:m
# ATMega88p
# 	$(PROGTOOL) -c $(PROGPROTOCOL) -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m -U efuse:w:0xf9:m 

.PHONY: flash
flash: main.hex
	$(PROGTOOL) -c $(PROGPROTOCOL) -U flash:w:$^

main.hex: main.elf
	$(OBJCOPY) -O ihex -R .eeprom $^ $@

main.elf: main.o interrupts.o
	$(CC) $(CFLAGS) -o $@ $^
	$(LD) --print-memory-usage $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

.PHONY: clean
clean:
	rm -f *.o
	rm -f *.elf
	rm -f *.hex
	rm -f a.out

