from flask import Flask, request, jsonify
from PumpController import PumpController  # Assuming you have the class in pump_controller.py
import logging
from flask import render_template
from flask_socketio import SocketIO, emit
import subprocess
import threading

app = Flask(__name__)
socketio = SocketIO(app)

logging.basicConfig(
    filename="/var/www/html/growbot-logs.log",
    level=logging.DEBUG,  # Set the log level to DEBUG to capture all levels of logs
    format='%(asctime)s - %(loggerName)s - %(levelname)s - %(message)s',  # Log format
)

logger = logging.getLogger("CustomLogger")
logger.addFilter(type('F', (logging.Filter,), {'filter': lambda self, record: setattr(record, 'processName', 'RuntimeServer') or True})())

@app.route('/water', methods=['POST'])
def water():
    try:
        # Get data from the request (sent as JSON)
        logger.info("## Collect data")
        data = request.get_json()  # Parse the incoming JSON data
        water_duration = data.get('water_duration')  # Extract the water level value
        pump_selection = data.get('pump_selection')  # Extract the pump selection value

        logger.info("## Check data")
        if water_duration is None or pump_selection is None:
            return jsonify({"error": "Missing watering duration (" + str(water_duration) + ") or pump selection(" + pump_selection + ")"}), 400

        logger.info("## Address pump")
        # Use the water_duration to control the pump (send selected pump to the controller)
        if pump_selection == 'pump0':
            pump_controller.pump_water(int(water_duration), "pump0")  # Pump 0
        elif pump_selection == 'pump1':
            pump_controller.pump_water(int(water_duration), "pump1")  # Pump 1
        else:
            return jsonify({"error": "Invalid pump selection"}), 400

        logger.info("## Send response back")
        return jsonify({"message": "Watering triggered successfully", "water_duration": water_duration, "pump_selection": pump_selection}), 200
    except Exception as e:
        logger.error("## ERROR during watering")
        return jsonify({"error": str(e)}), 500

@app.route('/control', methods=['POST'])
def control():
    try:
        data = request.get_json().get('command')
        if data == 'restartRuntimeServer':
            logger.info("## Request to restart runtimeServer received")
            pump_controller.shutdown()
            try:
                subprocess.Popen([ 'systemctl', 'restart', 'runtimeServer'])
            except subprocess.CalledProcessError as e:
                logger.error(f"Error restarting runtimeServer: {e}")
        if data == 'restartSystem':
            logger.info("Request to reboot system received")
            pump_controller.shutdown()
            try:
                subprocess.Popen([ 'reboot'])
            except subprocess.CalledProcessError as e:
                logger.error(f"Error restarting apache2/runtimeServer: {e}") 
        else:
            logger.warning({"error": "Invalid control sequence: " + str(data)})
            return jsonify({"error": "Invalid control sequence: " + str(data)}), 400
        return jsonify({"message": "controlled successfully", "command ": data}), 200
    except Exception as e:
        logger.error(f"## ERROR during control: {e}")
        return jsonify({"error": str(e)}), 500

@app.route('/execute', methods=['POST'])
def execute_command():
    logger.info("## doing some execute stuff")
    data = request.get_json()
    command = data.get('command', '')

    if not command:
        return jsonify({"success": False, "error": "No command provided"}), 400

    try:
        # Run the shell command and capture stdout and stderr
        result = subprocess.run(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        
        if result.returncode == 0:
            return jsonify({"success": True, "output": result.stdout})
        else:
            return jsonify({"success": False, "error": result.stderr})
    
    except Exception as e:
        logging.error(f"Error executing command: {e}")
        return jsonify({"success": False, "error": str(e)}), 500
        
if __name__ == '__main__':
    try:
        import ntplib, os, time
        client = ntplib.NTPClient()
        response = client.request('144.76.76.107') # use static address to opt out DNS 
        os.system('date ' + time.strftime('%m%d%H%M%Y.%S',time.localtime(response.tx_time)))
        logger.info("# Fetched time successful!")
    except Exception as e:
        logger.info('Could not sync with time server: ' + str(e))
    # Initialize PumpController
    logger.info("# Initializing PumpController")
    pump_controller = PumpController()
    logger.info("## Starting service")
    app.run(host='0.0.0.0')
