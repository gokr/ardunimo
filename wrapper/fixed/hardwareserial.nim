#
#  HardwareSerial.h - Hardware serial library for Wiring
#  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.
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
#  Modified 28 September 2010 by Mark Sproul
#  Modified 14 August 2012 by Alarus
#  Modified 3 December 2013 by Matthijs Kooijman
#  Modified 20 Aug 2014 by MediaTek Inc.
#

import
  Stream

type
  HardwareSerial* {.importcpp: "HardwareSerial", header: "HardwareSerial.h".} = object of Stream
  

proc begin*(this: var HardwareSerial; a3: culong) {.cdecl, importcpp: "begin",
    header: "HardwareSerial.h".}
proc `end`*(this: var HardwareSerial) {.cdecl, importcpp: "end",
                                    header: "HardwareSerial.h".}
proc available*(this: var HardwareSerial): cint {.cdecl, importcpp: "available",
    header: "HardwareSerial.h".}
proc peek*(this: var HardwareSerial): cint {.cdecl, importcpp: "peek",
                                        header: "HardwareSerial.h".}
proc read*(this: var HardwareSerial): cint {.cdecl, importcpp: "read",
                                        header: "HardwareSerial.h".}
proc flush*(this: var HardwareSerial) {.cdecl, importcpp: "flush",
                                    header: "HardwareSerial.h".}
proc write*(this: var HardwareSerial; a3: uint8): csize {.cdecl, importcpp: "write",
    header: "HardwareSerial.h".}
#proc bool*(this: var HardwareSerial): operator {.cdecl, importcpp: "bool",
#    header: "HardwareSerial.h".}
