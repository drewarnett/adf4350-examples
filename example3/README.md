Simple single frequency transverter LO
======================================
This collection of programs was put together for a San Diego Microwave Group
project.  This project is a group build of W1GHZ transverter boards for 2.3,
3.4, 5.7, and 10 GHz.

Kerry Banke used the Analog Devices evaluation software to provide the
register values.


Hardware
--------
 * ADF4350
 * Arduino Uno

Note:  be sure to use compatible I/O signaling level voltages.


ADF4350/Arduino connections
---------------------------
 * LE pin D10
 * CLK pin D11
 * DATA pin D12

Modify in the .ino if your connections differ.


Program files
-------------
Naming convention:

 * rf frequency_if frequency_lo type_multiplier_synthesizer frequency.ino

Example: 10368_144_low_x3_3408.ino

 * Synthesizer output will be (10368 – 144)/3 = 3408 MHz


Program behavior
----------------
On power up or after reset, the Arduino will:

 * delay 1 s
 * program the synthesizer
 * stop


How to program your Arduino
---------------------------
 * plug in Arduino to your computer
 * start Arduino IDE
 * ensure IDE is configured for your board (board type, serial port)
 * open .ino file with Arduino IDE
 * click the upload button
