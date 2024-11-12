import subprocess
import SoapySDR

def find_airspy():
    command = ["SoapySDRUtil", "--find=driver=airspyhf"]
    result = subprocess.run(command, capture_output=True, text=True)

    if result.returncode == 0:
        print("Command executed successfully!")
        print("Output:")
        print(result.stdout)
    else:
        print("Error in executing command:")
        print(result.stdout)

if __name__ == "__main__":
    find_airspy()