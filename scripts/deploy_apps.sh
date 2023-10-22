#!/bin/bash
REMOTE_DIR="root@192.168.5.10:/home/root/"
APP_PATH="../recipes-rootbot/rootbot"
TESTER_BIN="tester/build/tester"
TESTER_STEPPER_BIN="tester-stepper/build/tester-stepper"
ROOTBOT_BIN="rootbot/build/rootbot"

scp "${APP_PATH}/${TESTER_BIN}" "${REMOTE_DIR}"
scp "${APP_PATH}/${TESTER_STEPPER_BIN}" "${REMOTE_DIR}"
scp "${APP_PATH}/${ROOTBOT_BIN}" "${REMOTE_DIR}"
