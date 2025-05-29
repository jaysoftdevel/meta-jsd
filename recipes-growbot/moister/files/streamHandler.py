import threading
import subprocess
import time
from moist_logger import moist_logger

import threading
import time
import subprocess

class StreamHandler:
    def __init__(self, logger, interval=10):
        self.logger = logger
        self.interval = interval
        self._stop_event = threading.Event()
        self.thread = threading.Thread(target=self._poll_connections, daemon=True)
        self.thread.start()
        print("### Polling thread started.")

    def _poll_connections(self):
        print("### Starting poll loop...")
        while not self._stop_event.is_set():
            try:
                print("## Checking webcam connections...")
                result = subprocess.run(
                    "netstat -an | grep :80 | grep ESTABLISHED | wc -l",
                    shell=True, capture_output=True, text=True
                ).stdout.strip()
                print(f"result: {result}")

                if result == "0":
                    print("### No consumers. Stopping services.")
                    subprocess.run(['systemctl', 'stop', 'mjpg-streamer'])
                    self.logger.stopNightLight()
                else:
                    print("### Consumer detected. Services running.")

            except Exception as e:
                print(f"### Exception while polling: {e}")

            time.sleep(self.interval)
        print("### Polling loop exiting (should not happen unless stop() is called).")

    def stop(self):
        print("### Stopping polling thread...")
        self._stop_event.set()
        self.thread.join()
        print("### Polling thread stopped.")

# Example usage
if __name__ == "__main__":
    logger = moist_logger()
    poller = streamHandler(logger, interval=10)
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        poller.stop()
        print("Exiting main program.")

