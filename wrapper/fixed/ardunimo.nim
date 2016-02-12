# Some reasonable set of imports for a sketch
import arduino, wiring, wiring_digital, wiring_constants

# I couldn't figure out how to get this include into the
# sketch, it is needed in order to get setup/loop resolved
# from Arduino's main.cpp.
{.emit: """
#include "Arduino.h"
""".}

# Convenience templates, nifty
template setup(code: untyped): untyped =
  proc setup*() {.exportc.} =
    code

template loop(code: untyped): untyped =
  proc loop*() {.exportc.} =
    code

# Initialize Nim since Arduino will not do it
proc NimMain() {.importc.}
NimMain()
