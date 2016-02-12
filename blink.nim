include ardunimo

setup:
  pinMode(13, OUTPUT)

loop:
  while true:
    digitalWrite(13, LOW)
    delay(300)
    digitalWrite(13, HIGH)
    delay(300)
