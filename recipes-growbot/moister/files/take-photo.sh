#!/bin/sh

#set -e

OUTPUT_DIR="/var/www/html/webcam_photos"
VIDEO_OUTPUT_DIR="${OUTPUT_DIR}"
FRAMERATE=2

# Determine next image index
LAST_INDEX=$(ls "$OUTPUT_DIR"/photo_*.jpg 2>/dev/null | sed -n 's/.*photo_\([0-9]*\)\.jpg/\1/p' | sort -n | tail -1)
[ -z "$LAST_INDEX" ] && LAST_INDEX=0000

# Calculate next index
NEXT_INDEX=$(printf "%04d" $(expr 0 + "$LAST_INDEX" + 1))

# Check if camera is running already
if [ "$(systemctl is-active mjpg-streamer)" = "inactive" ]; then
then
    systemctl start mjpg-streamer
    sleep 2
    wget -q "http://done:funk@localhost:8080/?action=snapshot" -O "$OUTPUT_DIR/photo_${NEXT_INDEX}.jpg"
    systemctl stop mjpg-streamer
else
    wget -q "http://done:funk@localhost:8080/?action=snapshot" -O "$OUTPUT_DIR/photo_${NEXT_INDEX}.jpg"
fi

# Always overwrite timelapse video
VIDEO_PATH="$VIDEO_OUTPUT_DIR/timelapse_latest.mp4"

echo "[INFO] Rendering video → $VIDEO_PATH"
ffmpeg -y -framerate "$FRAMERATE" -pattern_type glob \
    -i "$OUTPUT_DIR/photo_*.jpg" \
    -c:v libx264 -pix_fmt yuv420p "$VIDEO_PATH"
