/**
 * HC-06 Config
 * Version 0.1
 * Copyright © 2015 dithosoft Software Solutions
 * 
 * --------------------------------------------------------------------------------
 * 
 * Configure the HC-06 Bluetooth device using an Arduino. The Bluetooth device name
 * and PIN can be changed.
 * 
 * --------------------------------------------------------------------------------
 * 
 * License: The MIT License (MIT)
 * Copyright © 2015 dithosoft Software Solutions
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 * --------------------------------------------------------------------------------
 * 
 * Usage:
 * The sketch uses the SoftSerial library to access the HC-06 device, so the normal
 * serial connection can be used to control the tool.
 * 
 * In the configuration section below, pick two ports for RX and TX on the Arduino.
 * Please note the restrictions in the documentation of the SoftSerial library that
 * apply to certain Arduinos.
 * 
 * Wire the configured Arduino's RX pin to the TX pin of the HC-06.
 * Wire the configured Arduino's TX pin to the RX pin of the HC-06.
 * 
 * Start the Arduino and start your serial monitor. Follow the instructions there.
 * IMPORTANT: YOU NEED TO SET THE SERIAL MONITOR TO END EACH TRANSMISSION WITH A
 *            CARRIAGE RETURN (CR, '\r') CHARACTER, OTHERWISE INPUTS WILL NOT BE
 *            RECOGNIZED.
 */
 
#include <SoftwareSerial.h>

/*********************************************************************************
 * Configuration
 *********************************************************************************/
#define RXPIN 10
#define TXPIN 11

/*********************************************************************************
 * You should not need to touch anything below, unless you know what you're doing.
 *********************************************************************************/
SoftwareSerial hc06(RXPIN, TXPIN);

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // Output welcome message on the user's serial monitor
  Serial.println(F("HC-06 Config v0.1"));
  Serial.println(F("Copyright © 2015 dithosoft Software Solutions"));
  Serial.println(F("---------------------------------------------"));

  // Let the user select the BAUD rate for his HC-06
  selectHC06BAUDRate();
}


void selectHC06BAUDRate()
{
  Serial.println(F(""));
  Serial.println(F("What BAUD rate is your HC-06 configured to?"));
  Serial.println(F("[1] 1200bps"));
  Serial.println(F("[2] 2400bps"));
  Serial.println(F("[3] 4800bps"));
  Serial.println(F("[4] 9600bps (this is the default value)"));
  Serial.println(F("[5] 19200bps"));
  Serial.println(F("[6] 38400bps"));
  Serial.println(F("[7] 57600bps"));
  Serial.println(F("[8] 115200bps"));
  Serial.println(F(""));
  Serial.println(F("Please enter your choice."));
  
  String userInput = String();

  input:
  do
  {
    userInput = Serial.readStringUntil('\r');
  }
  while (userInput.equals(""));

  int choiceMade = userInput.toInt();
  if (choiceMade < 1 || choiceMade > 8)
  {
    Serial.println(F("Invalid choice! Please chose a valid item."));
    goto input;
  }

  // Start serial communication with the HC-06 device
  int baudRate;
  switch (choiceMade)
  {
    case 1:
      baudRate = 1200;
      break;
    case 2:
      baudRate = 2400;
      break;
    case 3:
      baudRate = 4800;
      break;
    case 5:
      baudRate = 19200;
      break;
    case 6:
      baudRate = 38400;
      break;
    case 7:
      baudRate = 57600;
      break;
    case 8:
      baudRate = 115200;
      break;
    default:
      baudRate = 9600;
      break;
  }

  String baudString = String(baudRate);
  Serial.println("Starting serial communication with " + baudString + " bps...");
  hc06.begin(baudRate);
}

void loop() // run over and over
{
  // Output menu and let user chose what he wants to do
  int action = mainMenuChoice();

  // User wants to change the BT device name
  if (action == 1)
  {
    
  }

  // User wants to change the pairing code
  if (action == 2)
  {
    changeBTPIN();
  }

  // User wants to see version information
  if (action == 3)
  {
    showHC06Version();
  }
}


/**
 * Show the main menu with options for the user to chose from.
 * Returns: 1 if the user wants to change the BT device name
 *          2 if the user wants to change the BT PIN
 */
int mainMenuChoice()
{
  Serial.println(F(""));
  Serial.println(F("What do you want to do?"));
  Serial.println(F("[1] Set the Bluetooth device name"));
  Serial.println(F("[2] Set the Bluetooth PIN"));
  Serial.println(F("[3] Show HC-06 version information"));
  Serial.println(F(""));
  Serial.println(F("Please enter your choice."));

  String userInput = String();

  input:
  do
  {
    userInput = Serial.readStringUntil('\r');
  }
  while (userInput.equals(""));

  int choiceMade = userInput.toInt();
  if (choiceMade < 1 || choiceMade > 3)
  {
    Serial.println(F("Invalid choice! Please chose a valid item."));
    goto input;
  }

  return choiceMade;
}


/**
 * Handle changing the BT PIN.
 */
void changeBTPIN()
{
  Serial.println(F(""));

  // Show instructions
  input:
  Serial.print(F("Please enter a 4-digit PIN: "));

  // Let the user enter a string (wait for CR)
  String userInput = String();
  do
  {
    userInput = Serial.readStringUntil('\r');
  }
  while (userInput.equals(""));

  // Output what the user entered
  Serial.println(userInput);

  // It must be 4 characters
  if (userInput.length() != 4)
  {
    Serial.print("Your input must contain 4 digits! ");    
    goto input;
  }

  // And it must be numeric
  int inputAsInt = userInput.toInt();
  if (inputAsInt == 0)
  {
    Serial.print("Your input must consist of numbers only! "); 
    goto input;
  }
}


/**
 * Handle output of HC-06 version number.
 */
void showHC06Version()
{
  String reply;

  // Put the HC-06 into AT command mode. We expect "OK" as the reply to the AT command.
  // Unfortunately, the HC-06 doesn't use an end-of-line mark, so we read exactly 2 chars
  // here and hope for the best.
  int bytesRead;
  char atReplyBuffer[] = { '\0', '\0', '\0' };
  hc06.print("AT");
  bytesRead = hc06.readBytesUntil('\0', atReplyBuffer, 2);
  reply = String(atReplyBuffer);
  if (bytesRead != 2 || !reply.equalsIgnoreCase("ok"))
  {
    if (reply.equals(""))
      Serial.println("HC-06 didn't reply in time!");
    else
      Serial.println("Unexpected reply ('" + reply + "') to AT command");

    return;
  }

  // Get the version. As we don't have an end-of-line mark, we need to wait until the
  // timeout is reached and hope for the best. We also check whether the reply starts
  // with "OK", so have at least some indication things worked.
  Serial.print("HC-06 version number: ");
  hc06.print("AT+VERSION");
  reply = hc06.readString();
  if (reply.equals(""))
  {
    Serial.println("HC-06 didn't reply in time!");
  }
  else
  {
    if (reply.length() < 2 || !reply.substring(0,2).equalsIgnoreCase("OK"))
      Serial.println("Unexpected answer ('" + reply + "') to AT+VERSION command");
    else  
      Serial.println(reply.substring(2));
  }
}

