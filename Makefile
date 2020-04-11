TARGET=main

SRC_DIR=src
OUT_DIR=out
REL_OUT_DIR=$(OUT_DIR)/release
REL_OBJ_DIR=$(REL_OUT_DIR)/obj
REL_TARGET_PATH=$(REL_OUT_DIR)/$(TARGET)
DBG_OUT_DIR=$(OUT_DIR)/debug
DBG_OBJ_DIR=$(DBG_OUT_DIR)/obj
DBG_TARGET_PATH=$(DBG_OUT_DIR)/$(TARGET)

CPP_SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
S_SRC_FILES = $(wildcard $(SRC_DIR)/*.s)
REL_OBJ_FILES  = $(patsubst $(SRC_DIR)/%.cpp,$(REL_OBJ_DIR)/%.o,$(CPP_SRC_FILES))
REL_OBJ_FILES += $(patsubst $(SRC_DIR)/%.s,$(REL_OBJ_DIR)/%.o,$(S_SRC_FILES))
DBG_OBJ_FILES  = $(patsubst $(SRC_DIR)/%.cpp,$(DBG_OBJ_DIR)/%.o,$(CPP_SRC_FILES))
DBG_OBJ_FILES += $(patsubst $(SRC_DIR)/%.s,$(DBG_OBJ_DIR)/%.o,$(S_SRC_FILES))

LD_SCRIPT=stm32f411ve.ld

TARGET_CPU=cortex-m4

CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wwrite-strings
CFLAGS += -std=c++17
CFLAGS += -mthumb
CFLAGS += -mcpu=$(TARGET_CPU)
CFLAGS += -fdata-sections
CFLAGS += -ffunction-sections
CFLAGS += -fno-exceptions

LDFLAGS  = $(CFLAGS)
LDFLAGS += -nodefaultlibs
LDFLAGS += -Wl,--gc-sections

REL_CFLAGS  = $(CFLAGS)
REL_CFLAGS += -O3
REL_LDFLAGS  = $(LDFLAGS)
REL_LDFLAGS += $(REL_CFLAGS)

DBG_CFLAGS  = $(CFLAGS)
DBG_CFLAGS += -g3
DBG_CFLAGS += -Og
DBG_LDFLAGS  = $(LDFLAGS)
DBG_LDFLAGS += $(DBG_CFLAGS)

TOOLCHAIN_PREFIX=arm-none-eabi-
CC=$(TOOLCHAIN_PREFIX)g++
LD=$(TOOLCHAIN_PREFIX)g++
OBJCOPY=$(TOOLCHAIN_PREFIX)objcopy
OBJDUMP=$(TOOLCHAIN_PREFIX)objdump
SIZE=$(TOOLCHAIN_PREFIX)size

RELEASE_TARGETS  = $(REL_TARGET_PATH).elf
RELEASE_TARGETS += $(REL_TARGET_PATH).bin
RELEASE_TARGETS += $(REL_TARGET_PATH).hex
RELEASE_TARGETS += $(REL_TARGET_PATH).lst

DEBUG_TARGETS  = $(DBG_TARGET_PATH).elf
DEBUG_TARGETS += $(DBG_TARGET_PATH).bin
DEBUG_TARGETS += $(DBG_TARGET_PATH).hex
DEBUG_TARGETS += $(DBG_TARGET_PATH).lst

all: $(RELEASE_TARGETS) $(DEBUG_TARGETS) stats stats-debug

%.hex: %.elf
	$(OBJCOPY) -O ihex $< $@

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

$(REL_TARGET_PATH).elf: $(REL_OBJ_FILES) | $(REL_OUT_DIR)
	$(LD) $(REL_LDFLAGS) -T$(LD_SCRIPT) $^ -o $@ -Wl,-Map=$(REL_TARGET_PATH).map

$(REL_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(REL_OBJ_DIR)
	$(CC) $(REL_CFLAGS) -c $< -o $@

$(REL_OBJ_DIR)/%.o: $(SRC_DIR)/%.s | $(REL_OBJ_DIR)
	$(CC) $(REL_CFLAGS) -c $< -o $@

$(REL_OBJ_DIR): $(REL_OUT_DIR)
	mkdir -p $(REL_OBJ_DIR)

$(REL_OUT_DIR): $(OUT_DIR)
	mkdir -p $(REL_OUT_DIR)

$(DBG_TARGET_PATH).elf: $(DBG_OBJ_FILES) | $(DBG_OUT_DIR)
	$(LD) $(DBG_LDFLAGS) -T$(LD_SCRIPT) $^ -o $@ -Wl,-Map=$(DBG_TARGET_PATH).map

$(DBG_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(DBG_OBJ_DIR)
	$(CC) $(DBG_CFLAGS) -c $< -o $@

$(DBG_OBJ_DIR)/%.o: $(SRC_DIR)/%.s | $(DBG_OBJ_DIR)
	$(CC) $(DBG_CFLAGS) -c $< -o $@

$(DBG_OBJ_DIR): $(DBG_OUT_DIR)
	mkdir -p $(DBG_OBJ_DIR)

$(DBG_OUT_DIR): $(OUT_DIR)
	mkdir -p $(DBG_OUT_DIR)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

stats: $(REL_TARGET_PATH).elf
	$(SIZE) --format=berkeley $<

dump: $(REL_TARGET_PATH).elf
	$(OBJDUMP) -d -S $<

dump-all: $(REL_TARGET_PATH).elf
	$(OBJDUMP) -D $<

flash: $(REL_TARGET_PATH).bin
	openocd -f board/stm32f4discovery.cfg -c "program $< exit 0x08000000"

stats-debug: $(DBG_TARGET_PATH).elf
	$(SIZE) --format=berkeley $<

dump-debug: $(DBG_TARGET_PATH).elf
	$(OBJDUMP) -d -S $<

dump-all-debug: $(DBG_TARGET_PATH).elf
	$(OBJDUMP) -D $<

flash-debug: $(DBG_TARGET_PATH).bin
	openocd -f board/stm32f4discovery.cfg -c "program $< exit 0x08000000"

debugserver:
	openocd -f interface/stlink-v2.cfg -f target/stm32f4x_stlink.cfg

debug: $(DBG_TARGET_PATH).elf
	(echo "target remote localhost:3333"; cat) | arm-none-eabi-gdb $(DBG_TARGET_PATH).elf

clean:
	rm -rf $(OUT_DIR)

-include $($(OBJ_FILES):.o=.d)
