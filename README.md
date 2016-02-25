# Ardunimo
This is a first stab at Arduino programming on the <a href="https://www.hackster.io/mediateklabs/products/linkit-one">LinkIt ONE development board</a> from MediaTek using the brilliant <a href="http://nim-lang.org">programming language Nim</a>.

This project basically consists of two Makefiles, one in the `wrapper`subdirectory that can semi automatically generate the Nim wrapper of the Arduino and MediaTek libraries for the LinkIt ONE using the very useful `c2nim` tool. The other Makefile in the root directory is for compiling a Nim program using the wrapper and the SDK from MediaTek to produce a .vxp binary file that can be dropped into the USB disk on the board.

## Installing Nim, nimble and c2nim

First we need to install <a href="https://github.com/nim-lang/nim">Nim</a> (compiler and libs), <a href="https://github.com/nim-lang/nimble">nimble</a> (package manager) and <a href="https://github.com/nim-lang/c2nim">c2nim</a> (wrapper generator tool). I recommend following installation instructions on the github repos but if you want that information condensed, below is the recipe. And for the **ultra lazy** there is also a VagrantFile with this shell provisioning script, so you can just do `vagrant up && vagrant ssh` to have a working environment.

```
# If in a fresh Ubuntu
sudo apt-get update && sudo apt-get upgrade
sudo apt-get install git unzip build-essential

# Install Nim and bootstrap it
git clone https://github.com/nim-lang/Nim.git
cd Nim
git clone --depth 1 https://github.com/nim-lang/csources
cd csources && sh build.sh
cd ..
bin/nim c koch
./koch boot -d:release

# Execute and also put the following line last in ~/.profile
export PATH="$HOME/Nim/bin:$HOME/.nimble/bin:$PATH"

# Then install nimble
nim e install_nimble.nims

# Let it refresh the package list
nimble refresh

# Use nimble to install c2nim
nimble install c2nim
```

## Get Ardunimo
1. Clone this repo to your machine (or in the vagrant box), **only tested on 64 bit Ubuntu 14.04**. The Makefile presumes Nim was cloned to `$HOME/Nim`.
2. Download and install the needed ARM GCC and SDK by running: `cd ardunimo && make sdk`

## Patch Nim
For the moment Ardunimo needs a patched Nim, copy the alloc.nim file to replace the one in your Nim installation:
```
cp wrapper/fixed/alloc.nim <whereverNimLives>/lib/system/alloc.nim
```
This enables GC to work using malloc.

## Building blink.nim
In the repository there is a single trivial application - `blink.nim`, you probably recognize it. To build it and run on your LinkIt One:

1. Run `make`. If all is well it produces `app.vxp` in a few seconds about 85kb big.
2. Connect your LinkIt ONE **in USB drive mode** - the small switch closest to the USB cord should be towards the USB cable.
3. Press the reset button on the side of the board (where the green LED is lit) and Ubuntu should automount it.
4. Copy `app.vxp` to the MRE directory on the device. Also make sure `autostart.txt` maps to `app.vxp`.
5. Flip the USB mode switch and press the reset button, no need to unplug the USB cable. This will start the application.
6. After a few seconds the green LED on the board should start blinking.

## Building some other
Just write `other.nim` and make using:
```
make PROJECT=other.nim
```

Currently `blink`, `blink2` and `nimicro` works.


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

