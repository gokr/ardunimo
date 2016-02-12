# In nim we normally use import but wrapper/ardunimo.nim
# needs to be included at the top of a Nim sketch.
include ardunimo

# ardunimo.nim defines two trivial templates, setup and loop
# making it clean and convenient for this special case.
setup:
  # Nim is indentation based just like Python
  pinMode(13, OUTPUT)

loop:
  digitalWrite(13, LOW)
  delay(300)
  digitalWrite(13, HIGH)
  delay(300)
