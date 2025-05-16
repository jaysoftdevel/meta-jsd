import threading
import subprocess
import time
from moist_logger import moist_logger

class streamHandler:
    def __init__(self, logger, interval=10):
        self.logger = logger
        self.interval = interval
        self._stop_event = threading.Event()
        self.thread = threading.Thread(target=self._poll_connections, daemon=True)
        self.thread.start()
        print("done")

    def _poll_connections(self):
        while not self._stop_event.is_set():
            try:
                result = subprocess.run("netstat -an | grep :80 | grep ESTABLISHED | wc -l", shell=True, capture_output=True, text=True).stdout.strip()
                print("result: "+str(result))
                if result == "0":
                    print("### Closing connections")
                    print("### Disable webcam: " + str(result))
                    subprocess.run([ 'systemctl', 'stop', 'mjpg-streamer'])
                    print("### Stopping night light")
                    self.logger.stopNightLight()
                    print("### done")
            except Exception as e:
                print("### Exception while running netstat:", str(e))
            time.sleep(self.interval)

    def stop(self):
        """Stops the polling thread."""
        self._stop_event.set()
        self.thread.join()

# Example usage
if __name__ == "__main__":
    moist_logger = moist_logger()
    poller = streamHandler(moist_logger, interval=10)
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        poller.stop()
        print("Polling stopped.")