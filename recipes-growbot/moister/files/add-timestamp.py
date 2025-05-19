#!/usr/bin/env python3

from PIL import Image, ImageDraw, ImageFont
import datetime
import sys

if len(sys.argv) < 2:
    print("Usage: python script.py <image_path>")
    sys.exit(1)

img_path = sys.argv[1]
img = Image.open(img_path)
draw = ImageDraw.Draw(img)

# Load a font with larger size
font_size = 32

# use a bitmap font
#font = ImageFont.load("arial.pil")

# use a truetype font
font = ImageFont.truetype("LiberationMono-Regular.ttf", 25)

timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M")
draw.text((10, img.height - font_size - 10), timestamp, font=font, fill=(255, 255, 255))

img.save(img_path)