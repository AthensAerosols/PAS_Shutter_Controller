# PAS_Shutter_Controller
Code to control a motorized arc lamp shutter via Arduino

# Instructions

1. Download and extract the zip file.
2. Copy the folder 'Adafruit_Motor_Shield' into your Arduino libraries folder. Restart the IDE if necessary.
3. Upload 'PAS_Shutter_Controller.ino' to the Arduino.

You may control or query the board with the following commands:
- `*IDN?`: The instrument ID query.
- `t.l`: Request the temperature of lens 1 (pin A0).
- `s.o`: Open the shutter.
- `s.c`: Close the shutter.
- `v.s`: Set the valve to sampling position.
- `v.b`: Set the valve to background poisition.

The newline character (`\n`) serves as the termination character; the baud rate is 9600.

The program has an auto-shut setpoint.  When the temperature rises above the setpoint, it automatically shuts the shutter to avoid lens damage.  The default temperature is 150 C.
