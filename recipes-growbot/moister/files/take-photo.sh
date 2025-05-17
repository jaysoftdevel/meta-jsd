#!/bin/bash

OUTPUT_DIR="/var/www/html/webcam_photos"
mkdir -p "$OUTPUT_DIR"

# Determine next image index
LAST_INDEX=$(ls "$OUTPUT_DIR"/photo_*.jpg 2>/dev/null | sed -n 's/.*photo_\([0-9]*\)\.jpg/\1/p' | sort -n | tail -1)
NEXT_INDEX=$(printf "%04d" $((10#$LAST_INDEX + 1)))

# Capture snapshot from MJPEG stream
curl -s "http://localhost:8080/?action=snapshot" -o "$OUTPUT_DIR/photo_${NEXT_INDEX}.jpg"
