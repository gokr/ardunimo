#
#  WString.h - String library for Wiring & Arduino
#  ...mostly rewritten by Paul Stoffregen...
#  Copyright (c) 2009-10 Hernando Barragan.  All right reserved.
#  Copyright 2011, Paul Stoffregen, paul@pjrc.com
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

# When compiling programs with this class, the following gcc parameters
# dramatically increase performance and memory (RAM) efficiency, typically
# with little or no increase in code size.
#     -felide-constructors
#     -std=c++0x

# An inherited class for holding the result of a concatenation.  These
# result objects are assumed to be writable by subsequent concatenations.

discard "forward decl of StringSumHelper"
type
  ArString* {.importcpp: "String", header: "WString.h", inheritable.} = object # use a function pointer to allow for "if (s)" without the
                                                           # complications of an operator bool(). for more information, see:
                                                           # 
                                                           # http://www.artima.com/cppsource/safebool.html
                                                           #typedef void 
                                                           #(String::*StringIfHelperType)() const;
                                                           # constructors
                                                           # creates a copy of the initial value.
                                                           # if the initial value is null or invalid, or if memory allocation
                                                           # fails, the string will be marked as invalid (i.e. "if (s)" will
                                                           # be false).
    # the actual char array
    # the array length minus one (for the '\0')
    # the String length (not counting the '\0')
  

proc constructString*(cstr: cstring = ""): ArString {.cdecl, constructor,
    importcpp: "String(@)", header: "WString.h".}
proc constructString*(str: ArString): ArString {.cdecl, constructor,
    importcpp: "String(@)", header: "WString.h".}
proc constructString*(c: char): ArString {.cdecl, constructor, importcpp: "String(@)",
                                       header: "WString.h".}
proc constructString*(a2: cuchar; base: cuchar = 10.cuchar): ArString {.cdecl, constructor,
    importcpp: "String(@)", header: "WString.h".}
proc constructString*(a2: cint; base: cuchar = 10.cuchar): ArString {.cdecl, constructor,
    importcpp: "String(@)", header: "WString.h".}
proc constructString*(a2: cuint; base: cuchar = 10.cuchar): ArString {.cdecl, constructor,
    importcpp: "String(@)", header: "WString.h".}
proc constructString*(a2: clong; base: cuchar = 10.cuchar): ArString {.cdecl, constructor,
    importcpp: "String(@)", header: "WString.h".}
proc constructString*(a2: culong; base: cuchar = 10.cuchar): ArString {.cdecl, constructor,
    importcpp: "String(@)", header: "WString.h".}
proc constructString*(a2: cfloat; decimalPlaces: cuchar = 2.cuchar): ArString {.cdecl,
    constructor, importcpp: "String(@)", header: "WString.h".}
proc constructString*(a2: cdouble; decimalPlaces: cuchar = 2.cuchar): ArString {.cdecl,
    constructor, importcpp: "String(@)", header: "WString.h".}
proc destroyString*(this: var ArString) {.cdecl, importcpp: "#.~String()",
                                      header: "WString.h".}
proc reserve*(this: var ArString; size: cuint): cuchar {.cdecl, importcpp: "reserve",
    header: "WString.h".}
proc length*(this: ArString): cuint {.noSideEffect, cdecl, importcpp: "length",
                                  header: "WString.h".}
proc concat*(this: var ArString; str: ArString): cuchar {.cdecl, importcpp: "concat",
    header: "WString.h".}
proc concat*(this: var ArString; cstr: cstring): cuchar {.cdecl, importcpp: "concat",
    header: "WString.h".}
proc concat*(this: var ArString; c: char): cuchar {.cdecl, importcpp: "concat",
    header: "WString.h".}
#proc concat*(this: var ArString; c: cuchar): cuchar {.cdecl, importcpp: "concat",
#    header: "WString.h".}
proc concat*(this: var ArString; num: cint): cuchar {.cdecl, importcpp: "concat",
    header: "WString.h".}
proc concat*(this: var ArString; num: cuint): cuchar {.cdecl, importcpp: "concat",
    header: "WString.h".}
proc concat*(this: var ArString; num: clong): cuchar {.cdecl, importcpp: "concat",
    header: "WString.h".}
proc concat*(this: var ArString; num: culong): cuchar {.cdecl, importcpp: "concat",
    header: "WString.h".}
proc concat*(this: var ArString; num: cfloat): cuchar {.cdecl, importcpp: "concat",
    header: "WString.h".}
proc concat*(this: var ArString; num: cdouble): cuchar {.cdecl, importcpp: "concat",
    header: "WString.h".}
proc `+=`*(this: var ArString; rhs: ArString) {.cdecl, importcpp: "(# += #)",
    header: "WString.h".}
proc `+=`*(this: var ArString; cstr: cstring) {.cdecl, importcpp: "(# += #)",
    header: "WString.h".}
proc `+=`*(this: var ArString; c: char) {.cdecl, importcpp: "(# += #)",
                                    header: "WString.h".}
proc `+=`*(this: var ArString; num: cuchar) {.cdecl, importcpp: "(# += #)",
                                        header: "WString.h".}
proc `+=`*(this: var ArString; num: cint) {.cdecl, importcpp: "(# += #)",
                                      header: "WString.h".}
proc `+=`*(this: var ArString; num: cuint) {.cdecl, importcpp: "(# += #)",
                                       header: "WString.h".}
proc `+=`*(this: var ArString; num: clong) {.cdecl, importcpp: "(# += #)",
                                       header: "WString.h".}
proc `+=`*(this: var ArString; num: culong) {.cdecl, importcpp: "(# += #)",
                                        header: "WString.h".}
proc `+=`*(this: var ArString; num: cfloat) {.cdecl, importcpp: "(# += #)",
                                        header: "WString.h".}
proc `+=`*(this: var ArString; num: cdouble) {.cdecl, importcpp: "(# += #)",
    header: "WString.h".}
#proc ArStringIfHelperType*(this: ArString): operator {.noSideEffect, cdecl,
#    importcpp: "StringIfHelperType", header: "WString.h".}
proc compareTo*(this: ArString; s: ArString): cint {.noSideEffect, cdecl,
    importcpp: "compareTo", header: "WString.h".}
proc equals*(this: ArString; s: ArString): cuchar {.noSideEffect, cdecl,
    importcpp: "equals", header: "WString.h".}
proc equals*(this: ArString; cstr: cstring): cuchar {.noSideEffect, cdecl,
    importcpp: "equals", header: "WString.h".}
proc `==`*(this: ArString; rhs: ArString): cuchar {.noSideEffect, cdecl,
    importcpp: "(# == #)", header: "WString.h".}
proc `==`*(this: ArString; cstr: cstring): cuchar {.noSideEffect, cdecl,
    importcpp: "(# == #)", header: "WString.h".}
proc `<`*(this: ArString; rhs: ArString): cuchar {.noSideEffect, cdecl,
    importcpp: "(# < #)", header: "WString.h".}
proc `<=`*(this: ArString; rhs: ArString): cuchar {.noSideEffect, cdecl,
    importcpp: "(# <= #)", header: "WString.h".}
proc equalsIgnoreCase*(this: ArString; s: ArString): cuchar {.noSideEffect, cdecl,
    importcpp: "equalsIgnoreCase", header: "WString.h".}
proc startsWith*(this: ArString; prefix: ArString): cuchar {.noSideEffect, cdecl,
    importcpp: "startsWith", header: "WString.h".}
proc startsWith*(this: ArString; prefix: ArString; offset: cuint): cuchar {.
    noSideEffect, cdecl, importcpp: "startsWith", header: "WString.h".}
proc endsWith*(this: ArString; suffix: ArString): cuchar {.noSideEffect, cdecl,
    importcpp: "endsWith", header: "WString.h".}
proc charAt*(this: ArString; index: cuint): char {.noSideEffect, cdecl,
    importcpp: "charAt", header: "WString.h".}
proc setCharAt*(this: var ArString; index: cuint; c: char) {.cdecl,
    importcpp: "setCharAt", header: "WString.h".}
proc `[]`*(this: ArString; index: cuint): char {.noSideEffect, cdecl, importcpp: "#[@]",
    header: "WString.h".}
proc `[]`*(this: var ArString; index: cuint): var char {.cdecl, importcpp: "#[@]",
    header: "WString.h".}
proc getBytes*(this: ArString; buf: ptr cuchar; bufsize: cuint; index: cuint = 0) {.
    noSideEffect, cdecl, importcpp: "getBytes", header: "WString.h".}
proc toCharArray*(this: ArString; buf: cstring; bufsize: cuint; index: cuint = 0) {.
    noSideEffect, cdecl, importcpp: "toCharArray", header: "WString.h".}
proc c_str*(this: ArString): cstring {.noSideEffect, cdecl, importcpp: "c_str",
                                   header: "WString.h".}
proc indexOf*(this: ArString; ch: char): cint {.noSideEffect, cdecl,
    importcpp: "indexOf", header: "WString.h".}
proc indexOf*(this: ArString; ch: char; fromIndex: cuint): cint {.noSideEffect, cdecl,
    importcpp: "indexOf", header: "WString.h".}
proc indexOf*(this: ArString; str: ArString): cint {.noSideEffect, cdecl,
    importcpp: "indexOf", header: "WString.h".}
proc indexOf*(this: ArString; str: ArString; fromIndex: cuint): cint {.noSideEffect,
    cdecl, importcpp: "indexOf", header: "WString.h".}
proc lastIndexOf*(this: ArString; ch: char): cint {.noSideEffect, cdecl,
    importcpp: "lastIndexOf", header: "WString.h".}
proc lastIndexOf*(this: ArString; ch: char; fromIndex: cuint): cint {.noSideEffect,
    cdecl, importcpp: "lastIndexOf", header: "WString.h".}
proc lastIndexOf*(this: ArString; str: ArString): cint {.noSideEffect, cdecl,
    importcpp: "lastIndexOf", header: "WString.h".}
proc lastIndexOf*(this: ArString; str: ArString; fromIndex: cuint): cint {.noSideEffect,
    cdecl, importcpp: "lastIndexOf", header: "WString.h".}
proc substring*(this: ArString; beginIndex: cuint): ArString {.noSideEffect, cdecl,
    importcpp: "substring", header: "WString.h".}
proc substring*(this: ArString; beginIndex: cuint; endIndex: cuint): ArString {.
    noSideEffect, cdecl, importcpp: "substring", header: "WString.h".}
proc replace*(this: var ArString; find: char; replace: char) {.cdecl,
    importcpp: "replace", header: "WString.h".}
proc replace*(this: var ArString; find: ArString; replace: ArString) {.cdecl,
    importcpp: "replace", header: "WString.h".}
proc remove*(this: var ArString; index: cuint) {.cdecl, importcpp: "remove",
    header: "WString.h".}
proc remove*(this: var ArString; index: cuint; count: cuint) {.cdecl,
    importcpp: "remove", header: "WString.h".}
proc toLowerCase*(this: var ArString) {.cdecl, importcpp: "toLowerCase",
                                    header: "WString.h".}
proc toUpperCase*(this: var ArString) {.cdecl, importcpp: "toUpperCase",
                                    header: "WString.h".}
proc trim*(this: var ArString) {.cdecl, importcpp: "trim", header: "WString.h".}
proc toInt*(this: ArString): clong {.noSideEffect, cdecl, importcpp: "toInt",
                                 header: "WString.h".}
proc toFloat*(this: ArString): cfloat {.noSideEffect, cdecl, importcpp: "toFloat",
                                    header: "WString.h".}
type
  ArStringSumHelper* {.importcpp: "StringSumHelper", header: "WString.h".} = object of ArString
  

proc constructStringSumHelper*(s: ArString): ArStringSumHelper {.cdecl, constructor,
    importcpp: "StringSumHelper(@)", header: "WString.h".}
proc constructStringSumHelper*(p: cstring): ArStringSumHelper {.cdecl, constructor,
    importcpp: "StringSumHelper(@)", header: "WString.h".}
proc constructStringSumHelper*(c: char): ArStringSumHelper {.cdecl, constructor,
    importcpp: "StringSumHelper(@)", header: "WString.h".}
proc constructStringSumHelper*(num: cuchar): ArStringSumHelper {.cdecl, constructor,
    importcpp: "StringSumHelper(@)", header: "WString.h".}
proc constructStringSumHelper*(num: cint): ArStringSumHelper {.cdecl, constructor,
    importcpp: "StringSumHelper(@)", header: "WString.h".}
proc constructStringSumHelper*(num: cuint): ArStringSumHelper {.cdecl, constructor,
    importcpp: "StringSumHelper(@)", header: "WString.h".}
proc constructStringSumHelper*(num: clong): ArStringSumHelper {.cdecl, constructor,
    importcpp: "StringSumHelper(@)", header: "WString.h".}
proc constructStringSumHelper*(num: culong): ArStringSumHelper {.cdecl, constructor,
    importcpp: "StringSumHelper(@)", header: "WString.h".}
proc constructStringSumHelper*(num: cfloat): ArStringSumHelper {.cdecl, constructor,
    importcpp: "StringSumHelper(@)", header: "WString.h".}
proc constructStringSumHelper*(num: cdouble): ArStringSumHelper {.cdecl, constructor,
    importcpp: "StringSumHelper(@)", header: "WString.h".}
