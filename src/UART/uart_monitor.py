import serial

while True:
	with serial.Serial('/dev/ttyACM0', 9600, timeout = 1) as ser:
		line = ser.readline()

	print(line)
