#!/bin/bash

TIMESTAMP=$(date +"%Y-%m-%d_%H-%M-%S")
OUTPUT_DIR="/var/webcam_photos"
mkdir -p "$OUTPUT_DIR"
curl -s "http://localhost:8080/?action=snapshot" -o "$OUTPUT_DIR/photo_$TIMESTAMP.jpg"
