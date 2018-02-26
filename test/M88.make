## General Flags
MCU = atmega88
CC = avr-gcc
CPP = avr-g++
F_CPU = 8000000
## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -DF_CPU=$(F_CPU)UL
CFLAGS += -Wall -gdwarf-2 -std=gnu99 -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
# CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
# LDFLAGS += -Wl,-u,vfprintf  -Wl,-u,vfscanf
LDFLAGS += -Wl,-Map=$*.map

## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature
HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings

## Libraries
# LIBS = -lm -lprintf_flt -lscanf_flt

## Objects that must be built in order to link
LIBSRC = $(wildcard ../*.c)
LIBOBJS = $(patsubst %.c,%.o,$(LIBSRC))

## Objects explicitly added by the user
LINKONLYLIBOBJS =

VPATH =

## Build

## LIB LIBOBJS Compile

## project

##Link
%.elf: %.o $(LIBOBJS)
	 $(CC) $(LDFLAGS) $< $(LIBOBJS) $(LINKONLYLIBOBJS) $(LIBDIRS) $(LIBS) -o $@

%.hex: %.elf
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: %.elf
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: %.elf
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(LIBOBJS) *.elf *.hex ./hex/*
