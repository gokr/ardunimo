# blink.nim compiled to app.vxp
PROJECT = blink
EXECUTABLE = app.vxp

# Various paths
SDK = $(CURDIR)/sdk
GCCARM = gcc-arm-none-eabi-4.8.3-2014q1
MTSDK = mtk-1.1.17
MTSDKFILE = mediatek_linkit_sdk_\(for_arduino_1.6\)-1.1.17.zip
ARDUINO = $(SDK)/$(MTSDK)
ARMBIN = $(SDK)/$(GCCARM)/bin
CC = $(ARMBIN)/arm-none-eabi-gcc
CXX = $(ARMBIN)/arm-none-eabi-g++
AR = $(ARMBIN)/arm-none-eabi-ar
OBJCOPY = $(ARMBIN)/arm-none-eabi-objcopy
CORE = $(ARDUINO)/cores/arduino
VARIANT = $(ARDUINO)/variants/linkit_one
MTK = $(ARDUINO)/system/libmtk/include
PACKTAG = $(SDK)/packtag.py

# Various libraries to search
BASELIBRARIES := system/libmtk system/libmtk/include cores/arduino variants/linkit_one 
BSPLIBRARIES := libraries/LGPRS libraries/LDateTime libraries/LAudio libraries/LAudio/utility libraries/LStorage libraries/LGSM libraries/LGSM/utility 

# Flags picked out from Arduino compilation log
BASECFLAGS = -c -O2 -g -fpic -fvisibility=hidden -mthumb -mlittle-endian -nostdlib -Dprintf=iprintf -mcpu=arm7tdmi-s -DF_CPU=84000000L -DARDUINO=10605 -DARDUINO_MTK_ONE -DARDUINO_ARCH_ARM -D__COMPILER_GCC__ -D__LINKIT_ONE__ -D__LINKIT_ONE_RELEASE__ -DUSB_VID=0x0E8D -DUSB_PID=0x0023 -DUSBCON -DUSB_MANUFACTURER="Unknown" -DUSB_PRODUCT="LinkIt ONE"
CINCLUDES = -I/home/gokr/nim/Nim.devel/lib $(foreach dir,$(BASELIBRARIES),-I$(ARDUINO)/$(dir)/) $(foreach dir,$(BSPLIBRARIES),-I$(ARDUINO)/$(dir)/)
CFLAGS = $(BASECFLAGS) $(CINCLUDES)
CPPFLAGS = $(BASECFLAGS) -fno-non-call-exceptions -fno-rtti -fno-exceptions $(CINCLUDES) 

# Find all .c, .cpp and .ino files to compile in these dirs
CSOURCES += $(foreach dir,$(BASELIBRARIES),$(wildcard $(ARDUINO)/$(dir)/*.c)) 
CSOURCES += $(foreach dir,$(BSPLIBRARIES),$(wildcard $(ARDUINO)/$(dir)/*.c))
CSOURCES += $(CORE)/avr/dtostrf.c
CPPSOURCES += $(foreach dir,$(BASELIBRARIES),$(wildcard $(ARDUINO)/$(dir)/*.cpp))
CPPSOURCES += $(foreach dir,$(BSPLIBRARIES),$(wildcard $(ARDUINO)/$(dir)/*.cpp)) 

# And corresponding .o file list for all the above
OBJECTS = $(CSOURCES:.c=.o) $(CPPSOURCES:.cpp=.o)

# These are our own files produced by Nim compiler
NIMCSOURCES = $(wildcard *.cpp)
NIMOBJECTS = $(NIMCSOURCES:.cpp=.o)

# If we have ardunimo.nim we presume we have all .nim wrappers
ARDUNIMO = wrapper/ardunimo.nim 

# We need to do this in two runs since we do not know
# how many .cpp files we will produce in the first rule.
.PHONY: all
all: sdk
	$(MAKE) $(PROJECT).cpp
	$(MAKE) $(EXECUTABLE)

# Produce wrapper code, semi automated.
$(ARDUNIMO):
	$(MAKE) -C wrapper

# Run Nim compilation only step, see nim.cfg for settings
$(PROJECT).cpp: $(PROJECT).nim $(ARDUNIMO)
	nim cpp -d:release -c $(PROJECT).nim 
	cp nimcache/*.cpp .

# The link and post process binary steps, only "flashing" left manually
$(EXECUTABLE): $(PROJECT).o core.a $(NIMOBJECTS)
	$(CXX) -O2 -Wl,--gc-sections -mcpu=arm7tdmi-s -T$(ARDUINO)/variants/linkit_one/linker_scripts/gcc/scat.ld -Wl,-Map,$@.map -o $@.elf -L. -lm -fpic -pie -Wl,--entry=gcc_entry -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-unresolved-symbols -Wl,--start-group $(CORE)/syscalls_mtk.o $(NIMOBJECTS) $(VARIANT)/variant.o $(VARIANT)/libmtk.a core.a -Wl,--end-group
	$(OBJCOPY) --strip-debug $@.elf 
	$(PACKTAG) $@.elf $@

# When all objects are built, let's stuff them into core.a
core.a: $(OBJECTS)
	$(AR) rcs core.a $(OBJECTS)

# Rules for compiling C and C++
%.o : %.c
	$(CC) $(CFLAGS) $< -o $@

%.o : %.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

clean:
	rm -f $(foreach obj,$(OBJECTS), $(obj)) $(EXECUTABLE)
	rm -f *.c *.cpp *.o *.vxp.map core.a *.vxp.elf
	rm -rf nimcache
	touch $(PROJECT).nim

# Get the SDK parts we want
sdk: $(SDK)/$(GCCARM) $(SDK)/$(MTSDK)

$(SDK)/$(GCCARM):
	wget http://downloads.arduino.cc/$(GCCARM)-linux64.tar.gz
	tar -C $(SDK) -xzf $(GCCARM)-linux64.tar.gz
	rm $(GCCARM)-linux64.tar.gz

$(SDK)/$(MTSDK):
	wget http://download.labs.mediatek.com/$(MTSDKFILE)
	unzip -q -d $(SDK) $(MTSDKFILE)
	rm $(MTSDKFILE)
	mv $(SDK)/mtk $(SDK)/mtk-1.1.17
	cd $(SDK) && patch -s -p0 < sdk-fixes.patch
