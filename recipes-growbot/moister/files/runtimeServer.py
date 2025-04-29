from flask import Flask, request, jsonify
from PumpController import (
    PumpController,
)  # Assuming you have the class in pump_controller.py
import logging
from flask import render_template
import subprocess
import streamHandler
import temperatureMeasure
from moist_logger import moist_logger

app = Flask(__name__)

logging.basicConfig(
    filename="/var/www/html/growbot-logs.log",
    filemode="a",
    datefmt="%Y-%m-%d %H:%M:%S",
    level=logging.DEBUG,  # Set the log level to DEBUG to capture all levels of logs
    format="%(asctime)s - %(loggerName)s - %(levelname)s - %(message)s",  # Log format
)

logger = logging.getLogger("CustomLogger")
logger.addFilter(
    type(
        "F",
        (logging.Filter,),
        {
            "filter": lambda self, record: setattr(
                record, "processName", "RuntimeServer"
            )
            or True
        },
    )()
)


@app.route("/water", methods=["POST"])
def water():
    try:
        # Get data from the request (sent as JSON)
        data = request.get_json()  # Parse the incoming JSON data
        water_duration = data.get("water_duration")  # Extract the water level value
        pump_selection = data.get("pump_selection")  # Extract the pump selection value

        if water_duration is None or pump_selection is None:
            return (
                jsonify(
                    {
                        "error": "Missing watering duration ("
                        + str(water_duration)
                        + ") or pump selection("
                        + pump_selection
                        + ")"
                    }
                ),
                400,
            )

        logger.info("## Address pump: " + pump_selection)
        # Use the water_duration to control the pump (send selected pump to the controller)
        if pump_selection == "pump0":
            pump_controller.pump_water(int(water_duration), "pump0")  # Pump 0
        elif pump_selection == "pump1":
            pump_controller.pump_water(int(water_duration), "pump1")  # Pump 1
        else:
            return jsonify({"error": "Invalid pump selection"}), 400

        return (
            jsonify(
                {
                    "message": "Watering triggered successfully",
                    "water_duration": water_duration,
                    "pump_selection": pump_selection,
                }
            ),
            200,
        )
    except Exception as e:
        logger.error("## ERROR during watering")
        return jsonify({"error": str(e)}), 500


@app.route("/control", methods=["POST"])
def control():
    # try:
    global pump_controller
    data = request.get_json().get("command")
    match data:
        case "restartRuntimeServer":
            logger.info("## Request to restart runtimeServer received")
            pump_controller.shutdown()
            try:
                subprocess.Popen(["systemctl", "restart", "runtimeServer"])
                pump_controller = PumpController()
            except subprocess.CalledProcessError as e:
                logger.error(f"Error restarting runtimeServer: {e}")
        case "restartWebServer":
            logger.info("## Request to restart webServer received")
            pump_controller.shutdown()
            try:
                subprocess.Popen(["systemctl", "restart", "apache2"])
                pump_controller = PumpController()
            except subprocess.CalledProcessError as e:
                logger.error(f"Error restarting webserver: {e}")
        case "restartMoistLogger":
            logger.info("## Request to restart moist logger received")
            try:
                subprocess.Popen(["systemctl", "restart", "moister"])
            except subprocess.CalledProcessError as e:
                logger.error(f"Error restarting moist logger: {e}")
        case "restartMoistMeasure":
            print("restarting...")
            logger.info("## Request to restart moist measurement ECU received")
            try:
                pump_controller.reset_moister()
            except subprocess.CalledProcessError as e:
                logger.error(f"Error restarting moist logger: {e}")
        case "restartSystem":
            logger.info("## Request to reboot system received")
            pump_controller.shutdown()
            try:
                subprocess.Popen(["reboot"])
            except subprocess.CalledProcessError as e:
                logger.error(f"Error rebooting: {e}")
        case "stopCamera":
            logger.info("## Request to stop camera stream received")
            try:
                subprocess.Popen(["systemctl", "stop", "mjpg-streamer"])
            except subprocess.CalledProcessError as e:
                logger.error(f"Error stopping camera stream: {e}")
        case "startCamera":
            logger.info("## Request to start camera stream received")
            try:
                subprocess.Popen(["systemctl", "start", "mjpg-streamer"])
            except subprocess.CalledProcessError as e:
                logger.error(f"Error starting camera stream: {e}")
        case "startSprayer":
            logger.info("## Request to start sprayer received")
            try:
                print("## stuff do be done for..")
                moist_logger.startAtomzier()
            except subprocess.CalledProcessError as e:
                logger.error(f"Error starting Sprayer: {e}")
        case "stopSprayer":
            logger.info("## Request to stop sprayer received")
            try:
                print("## stuff do be done for off..")
                moist_logger.stopAtomzier()
            except subprocess.CalledProcessError as e:
                logger.error(f"Error stopping Sprayer: {e}")
        case "statusRuntimeServer":
            logger.info("## Status of RuntimeServer recieved")
            try:
                return (
                    jsonify(
                        {
                            "message": subprocess.run(
                                ["systemctl", "is-active", "runtimeServer"],
                                capture_output=True,
                                text=True,
                            ).stdout,
                            "command ": data,
                        }
                    ),
                    200,
                )
            except subprocess.CalledProcessError as e:
                logger.error(f"Error reading status of runtimeServer: {e}")
        case "statusWebserver":
            logger.info("## Status of Webserver recieved")
            try:
                return (
                    jsonify(
                        {
                            "message": subprocess.run(
                                ["systemctl", "is-active", "apache2"],
                                capture_output=True,
                                text=True,
                            ).stdout,
                            "command ": data,
                        }
                    ),
                    200,
                )
            except subprocess.CalledProcessError as e:
                logger.error(f"Error reading status of webserver: {e}")
        case "statusCamera":
            logger.info("## Status of camera stream recieved")
            try:
                return (
                    jsonify(
                        {
                            "message": subprocess.run(
                                ["systemctl", "is-active", "mjpg-streamer"],
                                capture_output=True,
                                text=True,
                            ).stdout,
                            "command ": data,
                        }
                    ),
                    200,
                )
            except subprocess.CalledProcessError as e:
                logger.error(f"Error reading status of camera stream: {e}")
        case "statusClients":
            logger.info("## Status of connected clients recieved")
            try:
                return (
                    jsonify(
                        {
                            "message": str(
                                int(
                                    subprocess.run(
                                        "netstat -an | grep :80 | grep ESTABLISHED | wc -l",
                                        shell=True,
                                        capture_output=True,
                                        text=True,
                                    ).stdout.strip()
                                )
                                // 2
                            ),
                            "command": data,
                        }
                    ),
                    200,
                )
            except subprocess.CalledProcessError as e:
                logger.error(f"Error reading number of connected clients: {e}")
        case "statusUptime":
            logger.info("## Uptime requestr recieved")
            try:
                return (
                    jsonify(
                        {
                            "message": subprocess.run(
                                "uptime", shell=True, capture_output=True, text=True
                            ).stdout.strip(),
                            "command": data,
                        }
                    ),
                    200,
                )
            except subprocess.CalledProcessError as e:
                logger.error(f"Error reading uptime: {e}")
        case "statusTemp":
            logger.info("## Status request for temperature and humidity recieved")
            try:
                return jsonify({"message": temperatureMeasure.DHT22(26).read()}), 200
            except subprocess.CalledProcessError as e:
                logger.error(f"Error reading temperature: {e}")
        case "clearServerLogs":
            logger.info("## Clearing of server log files requested")
            try:
                open("/var/www/html/growbot-logs.log", "a").truncate(0)
            except subprocess.CalledProcessError as e:
                logger.error(f"Error reading status of camera stream: {e}")
        case "clearMoistLogs":
            logger.info("## Clearing of moister log files requested")
            try:
                open("/var/www/html/moist_log.csv", "a").truncate(0)
            except subprocess.CalledProcessError as e:
                logger.error(f"Error reading status of camera stream: {e}")
        case _:
            logger.warning({"error": "Invalid control sequence: " + str(data)})
            return jsonify({"error": "Invalid control sequence: " + str(data)}), 400
    return jsonify({"message": "controlled successfully", "command ": data}), 200


# except Exception as e:
#     logger.error(f"## ERROR during control: {e}")
#     return jsonify({"error": str(e)}), 500

if __name__ == "__main__":
    logger.info(
        "**** starting GROWBOT ("
        + str(
            subprocess.run(
                "uptime -s", shell=True, capture_output=True, text=True
            ).stdout.strip()
        )
        + ") ****"
    )
    try:
        import ntplib, os, time

        client = ntplib.NTPClient()
        response = client.request("144.76.76.107")
        os.system(
            "date " + time.strftime("%m%d%H%M%Y.%S", time.localtime(response.tx_time))
        )
        logger.info("# Fetched time successful!")
    except Exception as e:
        logger.error("Could not sync with time server: " + str(e))
    pump_controller = PumpController()
    moist_logger = moist_logger()
    logger.info("## Starting service")
    sh = streamHandler.streamHandler(interval=10)
    try:
        app.run(host="0.0.0.0")
    except Exception as e:
        logger.error("#### Failed to run flask app: " + str(e))
