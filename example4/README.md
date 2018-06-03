multiple frequency transverter LO
=================================
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


DF4350/Arduino connections
---------------------------
 * LE pin D10
 * CLK pin D11
 * DATA pin D12

Modify in the .ino if your connections differ.


Switch connections
------------------
Arduino UNO connector pins D2 to D6 are used.  No connect = open = 1.  Short to ground = closed = 0.

D5     | D4     | D3     | D2     | configuration
-------|--------|--------|--------|--------------
open   | open   | open   | open   | 10368_144_low_x3_3408
open   | open   | open   | closed | 5760_144_low_x2_2808
open   | open   | closed | open   | 3456_144_low_x1_3312
open   | closed | open   | open   | 3400_144_low_x1_3256
closed | open   | open   | open   | 2304_144_low_x1_2160

D6
 * open - read the frequency switches once at power up
 * closed - read the frequency switches at all times


Program behavior
----------------
On power up or after reset, the Arduino will:

 * delay 1 s
 * sample D6
 * if D6 open:
   * read the switches
   * program the synthesizer
   * stop
 * else:
   * do forever:
     * read the switches
     * program the synthesizer


How to program your Arduino
---------------------------
 * plug in Arduino to your computer
 * start Arduino IDE
 * ensure IDE is configured for your board (board type, serial port)
 * open .ino file with Arduino IDE
 * click the upload button
