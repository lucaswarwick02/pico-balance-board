import time
import board
import busio
import adafruit_icm20x
import neopixel
import math

# Setup ic2 and icm
i2c = busio.I2C(board.GP5, board.GP4)
icm = adafruit_icm20x.ICM20948(i2c, 0x68)

# Setup the NeoPixel LED
pixel_pin = board.GP28
num_pixels = 1
pixels = neopixel.NeoPixel(pixel_pin, num_pixels, brightness=0.2, auto_write=False)

SENSITIVITY = 8 # Reduce this value to make the board more sensitive to movement

def getPercentageFromAcceleration(x, y):
    # Get average of x and y
    avgerage = math.sqrt(x ** 2 + y ** 2)
    # Highest average value I found was just above to, so use 11
    # Get Percentage from 0 to 11
    percentage = avgerage / SENSITIVITY
    return percentage

def lerpColour (percentage):
    # We want to lerp (linear interpolate) using the percentage
    # For r we lerp between 0 and 255
    # For g we lerp between 255 and 0
    delta = 255 * percentage
    return (0 + delta, 255 - delta, 0)

def getAcceleration():
    return icm.acceleration

while True:
    x, y, z = getAcceleration()
    percentage = getPercentageFromAcceleration(x, y)
    colour = lerpColour(percentage)
    # Set Pixel Colour
    pixels.fill(colour)
    pixels.show()