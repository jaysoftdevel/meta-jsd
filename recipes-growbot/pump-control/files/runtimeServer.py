from flask import Flask
import subprocess
from waterControl import GPIOWaterController  # Import your class

app = Flask(__name__)

@app.route('/water', methods=['POST'])
def water():
    print("### enter watering")
    try:
        # Run water.py as a script (this will call the __main__ block)
        print("### trigger subprocess")
        subprocess.run(['python3', 'waterControl.py'], check=True)
        print("### done triggering subprocess")
        return 'Watering script executed successfully', 200
    except subprocess.CalledProcessError as e:
        return f'Error executing watering script: {e}', 500

if __name__ == '__main__':
    print("### starting service")
    app.run(host='0.0.0.0', port=5000)
