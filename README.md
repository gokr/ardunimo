# Ardunimo
This is a first stab at Arduino programming on the LinkIt ONE development board from MediaTek using the programming language Nim.
In fact, it is a general attack on using `c2nim` to wrap the Arduino libraries (and the MediaTek libraries) in a semiautomated way.

## Installing

1. Install <a href="https://github.com/nim-lang/nim">Nim</a> (compiler and libs), <a href="https://github.com/nim-lang/nimble">nimble</a> (package manager) and <a href="https://github.com/nim-lang/c2nim">c2nim</a> (wrapper generator tool). I recommend following installation instructions on the github repos.
1. Clone this repo to your Linux machine, **only tested on 64 bit Ubuntu 14.04**.
2. Download and install the needed GCC and SDK by running: `cd ardunimo && make sdk`

## Building blink.nim

In the repository there is a single trivial application - `blink.nim`, you probably recognize it. To build it and run on your LinkIt One:

1. Run `make`. If all is well it produces `app.vxp` in a few seconds about 85kb big.
2. Connect your LinkIt ONE **in USB drive mode** - the small switch closest to the USB cord should be towards the USB cable.
3. Press the reset button on the side of the board (where the green LED is lit) and Ubuntu should automount it.
4. Copy `app.vxp` to the MRE directory on the device. Also make sure `autostart.txt` maps to `app.vxp`.
5. Flip the USB mode switch and press the reset button, no need to unplug the USB cable. This will start the application.
6. After a few seconds the green LED on the board should start blinking.


## Background
I begun by following these two tutorials:

* http://www.instructables.com/id/Programming-LinkIt-One-in-Linux-no-WiNE/
* http://www.instructables.com/id/Using-LinkIt-One-with-Arduino-in-Linux/

Then various googling and staring at the Arduino IDE compilation log led me to produce this LinkIt ONE specific Makefile.

After messing around with c2nim for a while I put that into its own Makefile. That Makefile produces a partial Nim wrapper of the Arduino + MediaTek libraries.


## NOTES:

* The wrapper is not complete (I just did what I needed) and in many places probably downright silly, as Andreas mentioned to me. :)
* Currently the GC can not be turned on (see nim.cfg), we don't know yet what is preventing it.
* We compile via Nim's C++ backend since Arduino libraries are C++ based.
* The `ardunimo.nim` is a hack I ended up doing so that setup/loop gets resolved properly. PRs appreciated.
* The wrapper/src directory contains the SDK sources *modified* for c2nim, these are not used when compiling.
* Some modifications I didn't manage to do in the src, then I manually edited the produced nim file and put it in wrapper/fixed.

