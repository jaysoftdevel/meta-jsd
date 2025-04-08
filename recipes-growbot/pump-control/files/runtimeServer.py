from flask import Flask, request, jsonify
from PumpController import PumpController  # Assuming you have the class in pump_controller.py

app = Flask(__name__)

# Initialize PumpController
pump_controller = PumpController()

@app.route('/water', methods=['POST'])
def water():
    try:
        # Get data from the request (sent as JSON)
        print("### Collect data")
        data = request.get_json()  # Parse the incoming JSON data
        water_duration = data.get('water_duration')  # Extract the water level value
        pump_selection = data.get('pump_selection')  # Extract the pump selection value

        print("### Check data")
        if water_duration is None or pump_selection is None:
            return jsonify({"error": "Missing watering duration (" + str(water_duration) + ") or pump selection(" + pump_selection + ")"}), 400
        
        print("### Address pump")
        # Use the water_duration to control the pump (send selected pump to the controller)
        if pump_selection == 'pump0':
            pump_controller.pump_water(int(water_duration), "pump0")  # Pump 0
        elif pump_selection == 'pump1':
            pump_controller.pump_water(int(water_duration), "pump1")  # Pump 1
        else:
            return jsonify({"error": "Invalid pump selection"}), 400

        print("### Send back")
        return jsonify({"message": "Watering triggered successfully", "water_duration": water_duration, "pump_selection": pump_selection}), 200
    except Exception as e:
        print("### ERROR")
        return jsonify({"error": str(e)}), 500

if __name__ == '__main__':
    print("### starting service")
    app.run(host='0.0.0.0')
