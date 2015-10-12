# HC06 Config
Arduino sketch that helps you configure your HC-06 bluetooth module. 
The following options of the HC-06 can be changed:

* The bluetooth name
* The bluetooth PIN
* The BAUD rate

In addition you can output the current firmware version.

## How it works

Once you've wired up the Arduino and the HC-06, you can transfer the sketch 
to the Arduino using the Arduino PC software. Open up the serial monitor to
interactively configure the options. The whole process is "menu guided":
Select an option from the menu presented on the serial console and then 
follow the instructions.

**Please make sure to select "carriage return" (CR, `\r`) line ending for the
serial monitor! Otherwise your inputs will not be recognized!**
