from luma.core.interface.serial import i2c
from luma.oled.device import ssd1306
from PIL import ImageDraw, ImageFont, Image
import time

serial = i2c(port=1, address=0x3C)
device = ssd1306(serial)

# Create an image to draw on
image = Image.new("1", device.size)
draw = ImageDraw.Draw(image)

# Draw some text
draw.text((15, 15), "Hello Pi 5!", fill=255)

# Display the image
device.display(image)
time.sleep(10)
