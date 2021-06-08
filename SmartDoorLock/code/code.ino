
// Include Libraries
#include "Arduino.h"
#include "DCMotor.h"
#include "NewPing.h"
#include "LED.h"
#include "Wire.h"
#include "SPI.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"
#include "PiezoSensor.h"


// Pin Definitions
#define DCMOTOR_PIN_COIL1  5
#define HCSR04_PIN_TRIG 7
#define HCSR04_PIN_ECHO 4
#define LEDG_PIN_VIN  6
#define LEDR_PIN_VIN  8
#define LEDSTRIPDOTSTAR_PIN_DI  11
#define LEDSTRIPDOTSTAR_PIN_CI  10
#define OLED128X64_PIN_RST  9
#define OLED128X64_PIN_DC 13
#define OLED128X64_PIN_CS 12
#define PIEZOSENSOR1_1_PIN_POS  A1
#define PIEZOSENSOR2_2_PIN_POS  A0



// Global variables and defines

// object initialization
HardwareSerial& bthc05(Serial1);
DCMotor dcMotor(DCMOTOR_PIN_COIL1);
NewPing hcsr04(HCSR04_PIN_TRIG,HCSR04_PIN_ECHO);
LED ledG(LEDG_PIN_VIN);
LED ledR(LEDR_PIN_VIN);
#define SSD1306_LCDHEIGHT 64
Adafruit_SSD1306 oLed128x64(OLED128X64_PIN_DC, OLED128X64_PIN_RST, OLED128X64_PIN_CS);
PiezoSensor piezoSensor1_1(PIEZOSENSOR1_1_PIN_POS);
PiezoSensor piezoSensor2_2(PIEZOSENSOR2_2_PIN_POS);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    bthc05.begin(9600);
    //This example uses HC-05 Bluetooth to communicate with an Android device.
    //Download bluetooth terminal from google play store, https://play.google.com/store/apps/details?id=Qwerty.BluetoothTerminal&hl=en
    //Pair and connect to 'HC-05', the default password for connection is '1234'.
    //You should see this message from your arduino on your android device
    bthc05.println("Bluetooth On....");
    oLed128x64.begin(SSD1306_SWITCHCAPVCC);  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
    oLed128x64.clearDisplay(); // Clear the buffer.
    oLed128x64.display();
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // HC - 05 Bluetooth Serial Module - Test Code
    String bthc05Str = "";
    //Receive String from bluetooth device
    if (bthc05.available())
    {
    //Read a complete line from bluetooth terminal
    bthc05Str = bthc05.readStringUntil('\n');
    // Print raw data to serial monitor
    Serial.print("BT Raw Data: ");
    Serial.println(bthc05Str);
    }
    //Send sensor data to Bluetooth device  
    bthc05.println("PUT YOUR SENSOR DATA HERE");
    }
    else if(menuOption == '2') {
    // DC Motor - Hobby Motor Gear - Test Code
    // The DC motor will turn on and off for 4000ms (4 sec)
    dcMotor.on(200);                        // 1. turns on
    delay(4000);                             // 2. waits 4000 milliseconds (4 sec). change the value in the brackets (4000) for a longer or shorter delay.
    dcMotor.off();                       // 3. turns off
    delay(4000);                             // 4. waits 4000 milliseconds (4 sec). change the value in the brackets (4000) for a longer or shorter delay.

    }
    else if(menuOption == '3') {
    // Ultrasonic Sensor - HC-SR04 - Test Code
    // Read distance measurment from UltraSonic sensor           
    int hcsr04Dist = hcsr04.ping_cm();
    delay(10);
    Serial.print(F("Distance: ")); Serial.print(hcsr04Dist); Serial.println(F("[cm]"));

    }
    else if(menuOption == '4') {
    // LED - Basic Green 5mm - Test Code
    // The LED will turn on and fade till it is off
    for(int i=255 ; i> 0 ; i -= 5)
    {
    ledG.dim(i);                      // 1. Dim Led 
    delay(15);                               // 2. waits 5 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    }                                          
    ledG.off();                        // 3. turns off
    }
    else if(menuOption == '5') {
    // LED - Basic Red 5mm - Test Code
    // The LED will turn on and fade till it is off
    for(int i=255 ; i> 0 ; i -= 5)
    {
    ledR.dim(i);                      // 1. Dim Led 
    delay(15);                               // 2. waits 5 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    }                                          
    ledR.off();                        // 3. turns off
    }
    else if(menuOption == '6')
    {
    // Disclaimer: The DotStar APA102 LED Strip is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    else if(menuOption == '7')
    {
    // Disclaimer: The Infrared Thermometer - MLX90614 is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    else if(menuOption == '8') {
    // Monochrome 1.3 inch 128x64 OLED graphic display - Test Code
    oLed128x64.setTextSize(1);
    oLed128x64.setTextColor(WHITE);
    oLed128x64.setCursor(0, 10);
    oLed128x64.clearDisplay();
    oLed128x64.println("Circuito.io Rocks!");
    oLed128x64.display();
    delay(1);
    oLed128x64.startscrollright(0x00, 0x0F);
    delay(2000);
    oLed128x64.stopscroll();
    delay(1000);
    oLed128x64.startscrollleft(0x00, 0x0F);
    delay(2000);
    oLed128x64.stopscroll();
    }
    else if(menuOption == '9') {
    // Piezo Element #1 - Test Code
    int piezoSensor1_1Val = piezoSensor1_1.read();
    Serial.print(F("Val: ")); Serial.println(piezoSensor1_1Val);

    }
    else if(menuOption == '10') {
    // Piezo Element #2 - Test Code
    int piezoSensor2_2Val = piezoSensor2_2.read();
    Serial.print(F("Val: ")); Serial.println(piezoSensor2_2Val);

    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) HC - 05 Bluetooth Serial Module"));
    Serial.println(F("(2) DC Motor - Hobby Motor Gear"));
    Serial.println(F("(3) Ultrasonic Sensor - HC-SR04"));
    Serial.println(F("(4) LED - Basic Green 5mm"));
    Serial.println(F("(5) LED - Basic Red 5mm"));
    Serial.println(F("(6) DotStar APA102 LED Strip"));
    Serial.println(F("(7) Infrared Thermometer - MLX90614"));
    Serial.println(F("(8) Monochrome 1.3 inch 128x64 OLED graphic display"));
    Serial.println(F("(9) Piezo Element #1"));
    Serial.println(F("(10) Piezo Element #2"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
          Serial.println(F("Now Testing HC - 05 Bluetooth Serial Module"));
        else if(c == '2') 
          Serial.println(F("Now Testing DC Motor - Hobby Motor Gear"));
        else if(c == '3') 
          Serial.println(F("Now Testing Ultrasonic Sensor - HC-SR04"));
        else if(c == '4') 
          Serial.println(F("Now Testing LED - Basic Green 5mm"));
        else if(c == '5') 
          Serial.println(F("Now Testing LED - Basic Red 5mm"));
        else if(c == '6') 
          Serial.println(F("Now Testing DotStar APA102 LED Strip - note that this component doesn't have a test code"));
        else if(c == '7') 
          Serial.println(F("Now Testing Infrared Thermometer - MLX90614 - note that this component doesn't have a test code"));
        else if(c == '8') 
          Serial.println(F("Now Testing Monochrome 1.3 inch 128x64 OLED graphic display"));
        else if(c == '9') 
          Serial.println(F("Now Testing Piezo Element #1"));
        else if(c == '10') 
          Serial.println(F("Now Testing Piezo Element #2"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}

/*******************************************************

*    Circuito.io is an automatic generator of schematics and code for off
*    the shelf hardware combinations.

*    Copyright (C) 2016 Roboplan Technologies Ltd.

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*    In addition, and without limitation, to the disclaimers of warranties 
*    stated above and in the GNU General Public License version 3 (or any 
*    later version), Roboplan Technologies Ltd. ("Roboplan") offers this 
*    program subject to the following warranty disclaimers and by using 
*    this program you acknowledge and agree to the following:
*    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND 
*    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN 
*    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT 
*    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS 
*    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY 
*    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE. 
*    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
*    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT 
*    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES 
*    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO 
*    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE 
*    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT 
*    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
*    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN. 
*    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN, 
*    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF 
*    THE ABOVE. 
********************************************************/
// Include Libraries
#include "Arduino.h"
#include "DCMotor.h"
#include "NewPing.h"
#include "LED.h"
#include "Wire.h"
#include "SPI.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"
#include "PiezoSensor.h"


// Pin Definitions
#define DCMOTOR_PIN_COIL1 5
#define HCSR04_PIN_TRIG 7
#define HCSR04_PIN_ECHO 4
#define LEDG_PIN_VIN  6
#define LEDR_PIN_VIN  8
#define LEDSTRIPDOTSTAR_PIN_DI  11
#define LEDSTRIPDOTSTAR_PIN_CI  10
#define OLED128X64_PIN_RST  9
#define OLED128X64_PIN_DC 13
#define OLED128X64_PIN_CS 12
#define PIEZOSENSOR1_1_PIN_POS  A1
#define PIEZOSENSOR2_2_PIN_POS  A0



// Global variables and defines

// object initialization
HardwareSerial& bthc05(Serial1);
DCMotor dcMotor(DCMOTOR_PIN_COIL1);
NewPing hcsr04(HCSR04_PIN_TRIG,HCSR04_PIN_ECHO);
LED ledG(LEDG_PIN_VIN);
LED ledR(LEDR_PIN_VIN);
#define SSD1306_LCDHEIGHT 64
Adafruit_SSD1306 oLed128x64(OLED128X64_PIN_DC, OLED128X64_PIN_RST, OLED128X64_PIN_CS);
PiezoSensor piezoSensor1_1(PIEZOSENSOR1_1_PIN_POS);
PiezoSensor piezoSensor2_2(PIEZOSENSOR2_2_PIN_POS);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    bthc05.begin(9600);
    //This example uses HC-05 Bluetooth to communicate with an Android device.
    //Download bluetooth terminal from google play store, https://play.google.com/store/apps/details?id=Qwerty.BluetoothTerminal&hl=en
    //Pair and connect to 'HC-05', the default password for connection is '1234'.
    //You should see this message from your arduino on your android device
    bthc05.println("Bluetooth On....");
    oLed128x64.begin(SSD1306_SWITCHCAPVCC);  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
    oLed128x64.clearDisplay(); // Clear the buffer.
    oLed128x64.display();
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // HC - 05 Bluetooth Serial Module - Test Code
    String bthc05Str = "";
    //Receive String from bluetooth device
    if (bthc05.available())
    {
    //Read a complete line from bluetooth terminal
    bthc05Str = bthc05.readStringUntil('\n');
    // Print raw data to serial monitor
    Serial.print("BT Raw Data: ");
    Serial.println(bthc05Str);
    }
    //Send sensor data to Bluetooth device  
    bthc05.println("PUT YOUR SENSOR DATA HERE");
    }
    else if(menuOption == '2') {
    // DC Motor - Hobby Motor Gear - Test Code
    // The DC motor will turn on and off for 4000ms (4 sec)
    dcMotor.on(200);                        // 1. turns on
    delay(4000);                             // 2. waits 4000 milliseconds (4 sec). change the value in the brackets (4000) for a longer or shorter delay.
    dcMotor.off();                       // 3. turns off
    delay(4000);                             // 4. waits 4000 milliseconds (4 sec). change the value in the brackets (4000) for a longer or shorter delay.

    }
    else if(menuOption == '3') {
    // Ultrasonic Sensor - HC-SR04 - Test Code
    // Read distance measurment from UltraSonic sensor           
    int hcsr04Dist = hcsr04.ping_cm();
    delay(10);
    Serial.print(F("Distance: ")); Serial.print(hcsr04Dist); Serial.println(F("[cm]"));

    }
    else if(menuOption == '4') {
    // LED - Basic Green 5mm - Test Code
    // The LED will turn on and fade till it is off
    for(int i=255 ; i> 0 ; i -= 5)
    {
    ledG.dim(i);                      // 1. Dim Led 
    delay(15);                               // 2. waits 5 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    }                                          
    ledG.off();                        // 3. turns off
    }
    else if(menuOption == '5') {
    // LED - Basic Red 5mm - Test Code
    // The LED will turn on and fade till it is off
    for(int i=255 ; i> 0 ; i -= 5)
    {
    ledR.dim(i);                      // 1. Dim Led 
    delay(15);                               // 2. waits 5 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    }                                          
    ledR.off();                        // 3. turns off
    }
    else if(menuOption == '6')
    {
    // Disclaimer: The DotStar APA102 LED Strip is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    else if(menuOption == '7')
    {
    // Disclaimer: The Infrared Thermometer - MLX90614 is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    else if(menuOption == '8') {
    // Monochrome 1.3 inch 128x64 OLED graphic display - Test Code
    oLed128x64.setTextSize(1);
    oLed128x64.setTextColor(WHITE);
    oLed128x64.setCursor(0, 10);
    oLed128x64.clearDisplay();
    oLed128x64.println("Circuito.io Rocks!");
    oLed128x64.display();
    delay(1);
    oLed128x64.startscrollright(0x00, 0x0F);
    delay(2000);
    oLed128x64.stopscroll();
    delay(1000);
    oLed128x64.startscrollleft(0x00, 0x0F);
    delay(2000);
    oLed128x64.stopscroll();
    }
    else if(menuOption == '9') {
    // Piezo Element #1 - Test Code
    int piezoSensor1_1Val = piezoSensor1_1.read();
    Serial.print(F("Val: ")); Serial.println(piezoSensor1_1Val);

    }
    else if(menuOption == '10') {
    // Piezo Element #2 - Test Code
    int piezoSensor2_2Val = piezoSensor2_2.read();
    Serial.print(F("Val: ")); Serial.println(piezoSensor2_2Val);

    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) HC - 05 Bluetooth Serial Module"));
    Serial.println(F("(2) DC Motor - Hobby Motor Gear"));
    Serial.println(F("(3) Ultrasonic Sensor - HC-SR04"));
    Serial.println(F("(4) LED - Basic Green 5mm"));
    Serial.println(F("(5) LED - Basic Red 5mm"));
    Serial.println(F("(6) DotStar APA102 LED Strip"));
    Serial.println(F("(7) Infrared Thermometer - MLX90614"));
    Serial.println(F("(8) Monochrome 1.3 inch 128x64 OLED graphic display"));
    Serial.println(F("(9) Piezo Element #1"));
    Serial.println(F("(10) Piezo Element #2"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
          Serial.println(F("Now Testing HC - 05 Bluetooth Serial Module"));
        else if(c == '2') 
          Serial.println(F("Now Testing DC Motor - Hobby Motor Gear"));
        else if(c == '3') 
          Serial.println(F("Now Testing Ultrasonic Sensor - HC-SR04"));
        else if(c == '4') 
          Serial.println(F("Now Testing LED - Basic Green 5mm"));
        else if(c == '5') 
          Serial.println(F("Now Testing LED - Basic Red 5mm"));
        else if(c == '6') 
          Serial.println(F("Now Testing DotStar APA102 LED Strip - note that this component doesn't have a test code"));
        else if(c == '7') 
          Serial.println(F("Now Testing Infrared Thermometer - MLX90614 - note that this component doesn't have a test code"));
        else if(c == '8') 
          Serial.println(F("Now Testing Monochrome 1.3 inch 128x64 OLED graphic display"));
        else if(c == '9') 
          Serial.println(F("Now Testing Piezo Element #1"));
        else if(c == '10') 
          Serial.println(F("Now Testing Piezo Element #2"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}
