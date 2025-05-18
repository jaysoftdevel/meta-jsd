import time
import board
import busio
from adafruit_ssd1306 import SSD1306_I2C
from PIL import Image, ImageDraw, ImageFont

# Set up I2C interface
i2c = busio.I2C(board.SCL, board.SDA)

# Initialize display
WIDTH = 128
HEIGHT = 32
oled = SSD1306_I2C(WIDTH, HEIGHT, i2c)

# Clear display
oled.fill(0)
oled.show()

# Create blank image for drawing
image = Image.new("1", (WIDTH, HEIGHT))
draw = ImageDraw.Draw(image)

# Use default font
font = ImageFont.load_default()

# Draw text
draw.text((0, 0), "Hello, RPi5!", font=font, fill=255)

# Display image
oled.image(image)
oled.show()
