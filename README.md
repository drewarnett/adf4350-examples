Arduino ADF4350 Examples
========================
Examples of programming an Analog Devices ADF4350 with an Arduino.  These were 
written for Kerry Banke, N6IZW, and others in the San Diego Microwave Group.

The ADF4350 has 6 registers behind a simple shift register interface.

WARNING:  Take care interfacing the microcontroller to the ADF4350 due to
likely differences in the digital signal voltage levels.  It is almost certain
that level shifting will have to be done unless you choose a microcontroller
that has the same digital signal voltage levels.  We used an Uno clone that
had a 3.3 V I/O option and avoided the need for extra level shifters.

So far, these examples are very simplistic.  With Analog Devices evaluation
software, however, they may be all you need.  More complicated examples will
be added as I receive requests.


example1
--------
Programs the synthesizer with fixed register values on power up or when the
microcontroller comes out of reset.

Customize:  Arduino CLK, DATA, and LE connections.

Customize:  Fixed register values.  Get these from the data sheet or from
Analog Device's evaluation board software.


example2
--------
Programs the synthesizer with one of two sets of fixed register values
depending on a switch on power up or when the microcontroller comes out of
reset or when the switch value changes.

Customize:  Arduino CLK, DATA, and LE connections.

Customize:  Fixed register values.  Get these from the data sheet or from
Analog Device's evaluation board software.

Customize:  switch connection.  Switch is placed between a digital pin and
ground.


example3
--------
Like example1, this programs the synthesizer once on power up or when the
microcontroller comes out of reset.  In this case, a collection of
Arduino sketches (.ino files) are provided per the 'example registers.csv'
spreadsheet.  The examples were created for a group build of W1GHZ
transverters for 2.4, 3.5, 5.7, and 10 GHz.

example4
--------
This provides the list of frequencies from example3, but in a single sketch.
A set of switches selects the band.  Another switch, that is read at power
up or after reset, decides if the frequency switches are continuously active.
This was also created for the group build of transverters.

example5
--------
Contains sketches for:
[simple-microwave-radios](https://github.com/drewarnett/simple-microwave-radios/wiki).  This project uses the ADF4350 as a simple QRP transmitter on 1.2 and 10
GHz.  Should be possible to apply on other bands as well or use for a
propagation beacon.

References
----------
http://www.analog.com/en/products/rf-microwave/pll-synth/adf4350.html

www.analog.com/en/design-center/evaluation-hardware-and-software/evaluation-boards-kits/eval-adf4350.html
