include ardunimo
 
# This seq is produced at compile time
const pauses = @[100, 200, 300, 500, 1000, 2000]

# Just an index into the seq
var pau = 0

setup:
  pinMode(13, OUTPUT)

loop:
  digitalWrite(13, LOW)
  delay(pauses[pau].uint32)
  if pau == pauses.high:
    pau = 0
  else:
    inc pau
  digitalWrite(13, HIGH)
  delay(pauses[pau].uint32)
