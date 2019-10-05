# Alexa Controlled 8 Channel Relay using SINRIC with Node MCU
1.  Make Smart your Home appliances with little bit of coding and some hardware requirements.
2.  No need to be a hardcore programmer for the Arduino Codes required in this Project.
 

# Requirements
1.  Arduino IDE (Download it from here:- https://www.arduino.cc/en/Main/Software).
2.  Node MCU.
3.  8 Channel Relay.
4.  Power Adapter To Power Up Node MCU and Relay Module.

Before Using this code, Keep in Mind  :

 * Make Sure Arduino is Install On your System, and ESP8266 driver is also install.
 * By going tools you have set Correct Board which is Node MCU 12E 1.0
 
Please Don't Blame Me if Your Board gets Accidently Fried by the incorrect connections.
Code is Working Properly already for my devices. 


Please make these changes before uploading the code to Node MCU.

1. Add your Sinric API key @Line 21.
2. Add your wifi Credentials @Line 22 & Line 23.
3. Add your Device IDs from SINIRIC Dashboard.
4.  Relay Pins For Node MCU  
    relayOne = 5;
    relayTwo = 4;
    relayThree = 0;
    relayFour = 2;
    relayFive = 14;
    relaySix = 12;
    relaySeven = 13;
    relayEight = 15;

# Once Done Making the Above changes,Upload the code to Node MCU and make the correct connections.

# After the connections are done its time for the Alexa Commands.

# For that In your Alexa App Add SINRIC Slill and Sign In with Your Credentials.

# Now Add devices by Going to Discover Devices Section of the App.

# Once Done Adding Devices now say "Alexa Device 1 On" or "Alexa Turn On All Devices(Make sure to ad devices to group before this command)".

# For any queries Ask me here only on Github,i will be happy to help you out..
