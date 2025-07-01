# AVR makefile for C/C++

# Paths
#==============================================================================================================================================================
SOURCE_PATH = ./src/
LIB_PATH = ./lib/
INCLUDE_PATH = ./inc/
BIN_PATH = ./bin/
LOG_PATH = ./log/
DUMP_PATH = ./dump/
#==============================================================================================================================================================

# Compiler varaibles
#==============================================================================================================================================================
MCU = atxmega256a3bu
C_STD = c11
CC_FLAGS = -Wall -O1 -g
OUTPUT = main
#==============================================================================================================================================================

# Uploader variables
#==============================================================================================================================================================
CONFIG_FILE = /etc/avrdude.conf
LOG = avrdude
BOOTLOADER = main.hex
EEPROM = main.hex

DUDE_MCU = x256a3bu
PROG = avrispmkII
PORT = /dev/ttyACM0
BAUD = 19200

# Fuse bytes
F0 = 0b11111111
F1 = 0b00000000
F2 = 0b11111111
F4 = 0b11111110
F5 = 0b11111110
# ATXmega E series only
F6 = 0b11111111
# LOCKBITS! 
LOCK = 0b11111111
#==============================================================================================================================================================

# Actions
#==============================================================================================================================================================

# Compile source code to .hex and .elf binary format (change avr-gcc to avr-g++ if using C++)
compile:
	avr-gcc $(SOURCE_PATH)*.c -o $(BIN_PATH)$(OUTPUT).elf -mmcu=$(MCU) -I $(INCLUDE_PATH) -L $(LIB_PATH) -std=$(C_STD) $(CC_FLAGS)
	avr-objcopy $(BIN_PATH)$(OUTPUT).elf -O ihex $(BIN_PATH)$(OUTPUT).hex

# Remove compiled output files and logs
clean:
	rm $(BIN_PATH)*.elf && rm $(BIN_PATH)*.hex && rm $(LOG_PATH)*.log

# Setup fuses
fuse:
	avrdude -v -c $(PROG) -p $(DUDE_MCU) -b $(BAUD) -l $(LOG_PATH)$(LOG).log \
	-U fuse0:w:$(F0):m \
	-U fuse1:w:$(F1):m \
	-U fuse2:w:$(F2):m \
	-U fuse4:w:$(F4):m \
	-U fuse5:w:$(F5):m \
	-U fuse6:w:$(F6):m \
	-U lock:w:$(LOCK):m

# Burn bootloader
boot:
	avrdude -v -c $(PROG) -p $(DUDE_MCU) -b $(BAUD) -l $(LOG_PATH)$(LOG).log \
	-U boot:w:"$(BIN_PATH)$(BOOTLOADER).hex":i

# Upload application
upload: compile
	avrdude -v  -c $(PROG) -p $(DUDE_MCU) -b $(BAUD) -l $(LOG_PATH)$(LOG).log \
	-U application:w:"$(BIN_PATH)$(OUTPUT).hex":i

# Upload EEPROM
eeprom:
	avrdude -v  -c $(PROG) -p $(DUDE_MCU) -b $(BAUD) -l $(LOG_PATH)$(LOG).log \
	-U eeprom:w:"$(BIN_PATH)$(EEPROM).hex":i

# Chip erase
erase:
	avrdude -v  -c $(PROG) -p $(DUDE_MCU) -b $(BAUD) -l $(LOG_PATH)$(LOG).log \
	-e

# Read and dump all memories
read:
	avrdude -v -c $(PROG) -p $(DUDE_MCU) -b $(BAUD) -l $(LOG_PATH)$(LOG).log \
	-U fuses:r:$(DUMP_PATH)fuses.dump:b \
	-U application:r:$(DUMP_PATH)application.dump:i \
	-U apptable:r:$(DUMP_PATH)apptable.dump:i \
	-U boot:r:$(DUMP_PATH)boot.dump:i \
	-U eeprom:r:$(DUMP_PATH)eeprom.dump:i \
	-U signature:r:$(DUMP_PATH)signature.dump:h \
	-U sernum:r:$(DUMP_PATH)sernum.dump:h \
	-U tempsense:r:$(DUMP_PATH)tempsense.dump:h \
	-U calibration:r:$(DUMP_PATH)calibration.dump:h
#==============================================================================================================================================================