# Trying to get Ni interpreter to run

include ardunimo
import nivm, niparser

var pause: uint32

setup:
  # This smallest Ni program works, but not much else :)
  pause = IntVal(newInterpreter().eval("1000")).value.uint32
  pinMode(13, OUTPUT)

loop:
  digitalWrite(13, LOW)
  delay(pause)
  digitalWrite(13, HIGH)
  delay(pause)
