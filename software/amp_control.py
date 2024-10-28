import serial
import time

def main():
    # Open the serial port connected to Teensy
    ser = serial.Serial('COM3', 9600, timeout=1)  # Adjust 'COM3' to the port where your Teensy is connected
    time.sleep(2)  # Wait for the connection to establish

    # Function to send commands to Teensy
    def send_command(command):
        ser.write((command + '\n').encode())  # Send command
        time.sleep(0.5)  # Wait for Teensy to process the command
        while ser.in_waiting:
            print(ser.readline().decode().strip())  # Print response from Teensy

    # Initial interaction
    print(ser.readline().decode().strip())  # Read initial message from Teensy

    # User input for number of amplifiers
    num_amps = input("Enter the number of amplifiers (1 or 2): ")
    send_command(num_amps)

    # Control loop for amplifiers
    if num_amps == '1':
        while True:
            gain = input("Enter gain value for the amplifier (1, 2, 4, 5, 8, 10, 16, 32 or 'exit' to quit): ")
            if gain.lower() == 'exit':
                break
            send_command(gain)
    elif num_amps == '2':
        while True:
            gain = input("Enter total gain value for both amps (1, 2, 4, 5, 8, 10, 16, 20, 25, 32, 40, 50, 64, 80, 100, 128, 160, 256, 320, 512, 1024 or 'exit' to quit): ")
            if gain.lower() == 'exit':
                break
            send_command(gain)

    # Close the serial connection
    ser.close()

if __name__ == "__main__":
    main()