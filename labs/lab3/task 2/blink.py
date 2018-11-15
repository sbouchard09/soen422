import Adafruit_BBIO.GPIO as GPIO
import time

GPIO.setup("P8_12", GPIO.OUT)

# pin 8-12 is set to high for 1 second, then low for one second in an infinite loop
while True:
    GPIO.output("P8_12", GPIO.HIGH)
	time.sleep(1)
	GPIO.output("P8_12", GPIO.LOW)
	time.sleep(1)