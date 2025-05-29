#!/bin/sh

OUTPUT_DIR="/var/www/html/webcam_photos"
JSON_OUTPUT="${OUTPUT_DIR}/timestamps.json"

# Create timestamp in format YYYY-MM-DD_HH:MM
TIMESTAMP=$(date +"%Y-%m-%d_%H-%M")
PHOTO_PATH="${OUTPUT_DIR}/photo_${TIMESTAMP}.jpg"

# Check if camera is running
if [ "$(systemctl is-active mjpg-streamer)" == "inactive" ]; then
    systemctl start mjpg-streamer
    # Wait for port 8080 to be ready
    echo "Waiting for mjpg-streamer to become available..."
    for i in {1..10}; do
        if nc -z localhost 8080; then
            echo "Stream is live."
            break
        fi
        sleep 1
    done
    # Take snapshot using curl
    if ! curl --silent --show-error --fail \
              --connect-timeout 5 \
              -u done:funk \
              "http://localhost:8080/?action=snapshot" \
              -o "$PHOTO_PATH"; then
        echo "Failed to retrieve snapshot."
    else
        echo "Snapshot saved to $PHOTO_PATH"
    fi
    systemctl stop mjpg-streamer
else
# Take snapshot using curl
if ! curl --silent --show-error --fail \
          --connect-timeout 5 \
          -u done:funk \
          "http://localhost:8080/?action=snapshot" \
          -o "$PHOTO_PATH"; then
    echo "Failed to retrieve snapshot."
else
    echo "Snapshot saved to $PHOTO_PATH"
fi
fi

python3 /var/www/html/add-timestamp.py "${PHOTO_PATH}"

echo "[" > "$JSON_OUTPUT"
first=1

for img in "${OUTPUT_DIR}"/photo_*.jpg; do
  # Extract timestamp string from filename
  basename=$(basename "$img")
  timestamp_str=$(echo "$basename" | sed -E 's/photo_([0-9]{4}:[0-9]{2}:[0-9]{2}_[0-9]{2}-[0-9]{2})\.jpg/\1/')

  if [ $first -eq 1 ]; then
    first=0
  else
    echo "," >> "$JSON_OUTPUT"
  fi

  echo "  \"$timestamp_str\"" >> "$JSON_OUTPUT"
done

echo "]" >> "$JSON_OUTPUT"

# !! Rendering on the RPi5 is too much effort at runtime!!
# Always overwrite timelapse video
# VIDEO_PATH="$VIDEO_OUTPUT_DIR/timelapse_latest.mp4"
# echo "[INFO] Rendering video → $VIDEO_PATH"
# ffmpeg -y -framerate "$FRAMERATE" -pattern_type glob \
#   -i "$OUTPUT_DIR/photo_*.jpg" \
#   -vf "scale=640:-2" \
#   -c:v libx264 -preset veryfast -crf 30 \
#   -pix_fmt yuv420p "$VIDEO_PATH"
