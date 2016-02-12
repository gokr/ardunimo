# Our modified tree of headers plus some shortcuts into it
SRC = $(CURDIR)/src
CORE = $(SRC)/cores/arduino
VARIANT = $(SRC)/variants/linkit_one
LSTORAGE = $(SRC)/libraries/LStorage
MTK = $(SRC)/system/libmtk/include

# Tried --nep1 but it led to messy complications 
C2NIMFLAGS = --cdecl --header --staticlib:core.a --cpp

# Make the wrapper. We list each file manually since we don't want to
# wrap just all of them.
.PHONY: wrapper
wrapper:
	c2nim $(C2NIMFLAGS) --out:arduino.nim config.c2nim $(CORE)/Arduino.h
	c2nim $(C2NIMFLAGS) --out:binary.nim config.c2nim $(CORE)/binary.h
	c2nim $(C2NIMFLAGS) --out:itoa.nim config.c2nim $(CORE)/itoa.h
	c2nim $(C2NIMFLAGS) --out:vmdcl.nim config.c2nim $(MTK)/vmdcl.h
	c2nim $(C2NIMFLAGS) --out:vmsys.nim config.c2nim $(MTK)/vmsys.h
	c2nim $(C2NIMFLAGS) --out:vmpwr.nim config.c2nim $(MTK)/vmpwr.h
	c2nim $(C2NIMFLAGS) --out:vmota.nim config.c2nim $(MTK)/vmota.h
	c2nim $(C2NIMFLAGS) --out:vmappmgr.nim config.c2nim $(MTK)/vmappmgr.h
	c2nim $(C2NIMFLAGS) --out:vmpromng.nim config.c2nim $(MTK)/vmpromng.h
	# A bug in c2nim causes pragmas to not merge
	sed -i 's/\.}\ {\./\,\ /g' vmpromng.nim
	c2nim $(C2NIMFLAGS) --out:vmdatetime.nim config.c2nim $(MTK)/vmdatetime.h
	c2nim $(C2NIMFLAGS) --out:vmuimisc.nim config.c2nim $(MTK)/vmuimisc.h
	c2nim $(C2NIMFLAGS) --out:vmthread.nim config.c2nim $(MTK)/vmthread.h
	c2nim $(C2NIMFLAGS) --out:wiring.nim config.c2nim $(CORE)/wiring.h
	c2nim $(C2NIMFLAGS) --out:wiring_digital.nim config.c2nim $(CORE)/wiring_digital.h
	c2nim $(C2NIMFLAGS) --out:wiring_analog.nim config.c2nim $(CORE)/wiring_analog.h
	c2nim $(C2NIMFLAGS) --out:wiring_shift.nim config.c2nim $(CORE)/wiring_shift.h
	c2nim $(C2NIMFLAGS) --out:winterrupts.nim config.c2nim $(CORE)/WInterrupts.h
	c2nim $(C2NIMFLAGS) --out:message.nim config.c2nim $(CORE)/message.h
	c2nim $(C2NIMFLAGS) --out:wiring_constants.nim config.c2nim $(CORE)/wiring_constants.h
	c2nim $(C2NIMFLAGS) --out:uartclass.nim config.c2nim $(CORE)/UARTClass.h
	c2nim $(C2NIMFLAGS) --out:hardwareserial.nim config.c2nim $(CORE)/HardwareSerial.h
	c2nim $(C2NIMFLAGS) --out:stream.nim config.c2nim $(CORE)/Stream.h
	c2nim $(C2NIMFLAGS) --out:print.nim config.c2nim $(CORE)/Print.h
	c2nim $(C2NIMFLAGS) --out:wstring.nim config.c2nim $(CORE)/WString.h
	c2nim $(C2NIMFLAGS) --out:lflash.nim config.c2nim $(LSTORAGE)/LFlash.h
	c2nim $(C2NIMFLAGS) --out:lstorage.nim config.c2nim $(LSTORAGE)/LStorage.h
	c2nim $(C2NIMFLAGS) --out:ltask.nim config.c2nim $(CORE)/LTask.h
	# Integrated printable into print.nim to avoid cycles: c2nim $(C2NIMFLAGS) --out:printable.nim config.c2nim $(CORE)/Printable.h
	c2nim $(C2NIMFLAGS) --out:variant.nim config.c2nim $(VARIANT)/variant.h
	# Copy fixed versions overwriting the stock C2NIM output... last resort I know.
	cp fixed/*.nim .

clean:
	rm -f *.nim
