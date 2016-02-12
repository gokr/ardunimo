#
#  Print.h - Base class that provides print() and println()
#  Copyright (c) 2008 David A. Mellis.  All right reserved.
#
#  This library is free software; you can redistribute it and/or
#  modify it under the terms of the GNU Lesser General Public
#  License as published by the Free Software Foundation; either
#  version 2.1 of the License, or (at your option) any later version.
#
#  This library is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#  Lesser General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public
#  License along with this library; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#
#  Modified 20 Aug 2014 by MediaTek Inc.
#

import
  wString

const
  DEC* = 10
  HEX* = 16
  OCT* = 8
  BIN* = 2

type
  Print* {.importcpp: "Print", header: "Print.h", inheritable .} = object
  Printable* {.importcpp: "Printable", header: "Printable.h".} = object
  

proc constructPrint*(): Print {.cdecl, constructor, importcpp: "Print(@)",
                             header: "Print.h".}
proc getWriteError*(this: var Print): cint {.cdecl, importcpp: "getWriteError",
                                        header: "Print.h".}
proc clearWriteError*(this: var Print) {.cdecl, importcpp: "clearWriteError",
                                     header: "Print.h".}
proc write*(this: var Print; a3: uint8): csize {.cdecl, importcpp: "write",
    header: "Print.h".}
proc write*(this: var Print; str: cstring): csize {.cdecl, importcpp: "write",
    header: "Print.h".}
proc write*(this: var Print; buffer: ptr uint8; size: csize): csize {.cdecl,
    importcpp: "write", header: "Print.h".}
proc write*(this: var Print; buffer: cstring; size: csize): csize {.cdecl,
    importcpp: "write", header: "Print.h".}
#proc print*(this: var Print; a3: ptr FlashStringHelper): csize {.cdecl,
#    importcpp: "print", header: "Print.h".}
proc print*(this: var Print; a3: ArString): csize {.cdecl, importcpp: "print",
    header: "Print.h".}
proc print*(this: var Print; a3: ptr char): csize {.cdecl, importcpp: "print",
    header: "Print.h".}
proc print*(this: var Print; a3: char): csize {.cdecl, importcpp: "print",
    header: "Print.h".}
proc print*(this: var Print; a3: cuchar; a4: cint = DEC): csize {.cdecl, importcpp: "print",
    header: "Print.h".}
proc print*(this: var Print; a3: cint; a4: cint = DEC): csize {.cdecl, importcpp: "print",
    header: "Print.h".}
proc print*(this: var Print; a3: cuint; a4: cint = DEC): csize {.cdecl, importcpp: "print",
    header: "Print.h".}
proc print*(this: var Print; a3: clong; a4: cint = DEC): csize {.cdecl, importcpp: "print",
    header: "Print.h".}
proc print*(this: var Print; a3: culong; a4: cint = DEC): csize {.cdecl, importcpp: "print",
    header: "Print.h".}
proc print*(this: var Print; a3: cdouble; a4: cint = 2): csize {.cdecl, importcpp: "print",
    header: "Print.h".}
proc print*(this: var Print; a3: Printable): csize {.cdecl, importcpp: "print",
    header: "Print.h".}
#proc println*(this: var Print; a3: ptr FlashStringHelper): csize {.cdecl,
#    importcpp: "println", header: "Print.h".}
proc println*(this: var Print; s: ArString): csize {.cdecl, importcpp: "println",
    header: "Print.h".}
proc println*(this: var Print; a3: ptr char): csize {.cdecl, importcpp: "println",
    header: "Print.h".}
proc println*(this: var Print; a3: char): csize {.cdecl, importcpp: "println",
    header: "Print.h".}
proc println*(this: var Print; a3: cuchar; a4: cint = DEC): csize {.cdecl,
    importcpp: "println", header: "Print.h".}
proc println*(this: var Print; a3: cint; a4: cint = DEC): csize {.cdecl,
    importcpp: "println", header: "Print.h".}
proc println*(this: var Print; a3: cuint; a4: cint = DEC): csize {.cdecl,
    importcpp: "println", header: "Print.h".}
proc println*(this: var Print; a3: clong; a4: cint = DEC): csize {.cdecl,
    importcpp: "println", header: "Print.h".}
proc println*(this: var Print; a3: culong; a4: cint = DEC): csize {.cdecl,
    importcpp: "println", header: "Print.h".}
proc println*(this: var Print; a3: cdouble; a4: cint = 2): csize {.cdecl,
    importcpp: "println", header: "Print.h".}
proc println*(this: var Print; a3: Printable): csize {.cdecl, importcpp: "println",
    header: "Print.h".}
proc println*(this: var Print): csize {.cdecl, importcpp: "println", header: "Print.h".}
proc printf*(this: var Print; fmt: cstring): csize {.varargs, cdecl, importcpp: "printf",
    header: "Print.h".}


# Copied here from Printable.h to avoid cyclid deps
proc printTo*(this: Printable; p: var Print): csize {.noSideEffect, cdecl,
    importcpp: "printTo", header: "Printable.h".}
