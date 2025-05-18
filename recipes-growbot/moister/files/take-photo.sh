#!/bin/sh

OUTPUT_DIR="/var/www/html/webcam_photos"
VIDEO_OUTPUT_DIR="${OUTPUT_DIR}"
FRAMERATE=2

# Determine next image index
LAST_INDEX=$(ls "$OUTPUT_DIR"/photo_*.jpg 2>/dev/null | sed -n 's/.*photo_\([0-9]*\)\.jpg/\1/p' | sort -n | tail -1)
[ -z "$LAST_INDEX" ] && LAST_INDEX=0000

# Calculate next index
NEXT_INDEX=$(printf "%04d" $(expr 0 + "$LAST_INDEX" + 1))
PHOTO_PATH="$OUTPUT_DIR/photo_${NEXT_INDEX}.jpg"

# Check if camera is running
if [ "$(systemctl is-active mjpg-streamer)" = "inactive" ]; then
    systemctl start mjpg-streamer
    sleep 2
    wget -q "http://done:funk@localhost:8080/?action=snapshot" -O "$PHOTO_PATH"
    systemctl stop mjpg-streamer
else
    wget -q "http://done:funk@localhost:8080/?action=snapshot" -O "$PHOTO_PATH"
fi

# Always overwrite timelapse video (with timestamp overlay)
VIDEO_PATH="$VIDEO_OUTPUT_DIR/timelapse_latest.mp4"
echo "[INFO] Rendering video → $VIDEO_PATH"

ffmpeg -y -framerate "$FRAMERATE" -pattern_type glob \
  -i "$OUTPUT_DIR/photo_*.jpg" \
  -vf "scale=640:-2,drawtext=fontfile=/usr/share/fonts/TTF/DejaVuSans.ttf: \
       text='%{pts\:localtime\:%s}':fontcolor=white:fontsize=16:box=1:boxcolor=black@0.5:x=w-tw-10:y=h-th-10" \
  -c:v libx264 -preset veryfast -crf 30 -pix_fmt yuv420p "$VIDEO_PATH"
