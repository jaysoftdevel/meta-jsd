import threading
import subprocess
import time

class streamHandler:
    def __init__(self, interval=10):
        self.interval = interval
        self._stop_event = threading.Event()
        self.thread = threading.Thread(target=self._poll_connections, daemon=True)
        self.thread.start()

    def _poll_connections(self):
        while not self._stop_event.is_set():
            try:
                result = subprocess.run("netstat -an | grep :80 | grep ESTABLISHED | wc -l", shell=True, capture_output=True, text=True).stdout.strip()
                if result == "0":
                    if subprocess.run("systemctl is-active mjpg-streamer", shell=True, capture_output=True, text=True).stdout.strip() == "active":
                        print("Disable webcam: " + str(result))
                        subprocess.run([ 'systemctl', 'stop', 'mjpg-streamer'])
            except Exception as e:
                print("### Exception while running netstat:", str(e))
            time.sleep(self.interval)

    def stop(self):
        """Stops the polling thread."""
        self._stop_event.set()
        self.thread.join()

# Example usage
if __name__ == "__main__":
    poller = streamHandler(interval=10)
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        poller.stop()
        print("Polling stopped.")