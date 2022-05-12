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
    # TODO: Get average of x and y
    # TODO: Get Percentage from 0 to 11
    return 0

def lerpColour (percentage):
    # TODO: We want to lerp (linear interpolate) using the percentage
    # For r we lerp between 0 and 255
    # For g we lerp between 255 and 0
    return (0, 0, 0)

def getAcceleration():
    # TODO: Grab the acceleration fro the icm (only 1 line is needed here)
    return (0, 0, 0)

while True:
    # TODO: Get colour from acceleration
    x, y, z = getAcceleration()
    percentage = getPercentageFromAcceleration(x, y)
    # Set Pixel Colour
    colour = lerpColour(percentage)
    pixels.fill(colour)
    pixels.show()