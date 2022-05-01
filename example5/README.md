# Simple Amateur Radio Microwave Transmitters

For more information, please see:
[simple-microwave-radios](https://github.com/drewarnett/simple-microwave-radios/wiki).

For 1.2, use a low or bandpass filter.  The ADF4350 is harmonic rich.  Even
with a filter, we see the specified +5 dBm output.

N6IZW provided these register values using ADI's EVB software for 1296.100:

```
R5 0x580005
R4 0x9A013C
R3 0x4B3
R2 0x2004E42
R1 0x8008321
R0 0x4081E8
```

I wrote a python program `[adf4350-r4-keying.py](adf4350-r4-keying.py)` to
generate #define statements to use in an Arduino sketch.  This provides
register values with the output buffer on or off, but also with the output
buffer set to -3, -6, and -9 dB of full output.  The output can be copied and
pasted into your sketch.

The -3, -6, -9 does provide useful waveform shaping when using the ADF4350 for
OOK (on-off keying).  Better OOK can be had by keying an external buffer
amplifier with better shaping.

On to off depth measured at 57 dB, so the CW backwave is acceptable.

[1296.ino](1296/1296.ino) - This sketch has key jack input, sidetone output
and built in LED indicator, and some shaping.

For 10 GHz, the ADF4350 is programmed to 1/3 of the desired frequency.  Use this
with W1GHZ's 10 GHz LO tripler board.  (Paul reported good results keying the
last two amplifier stages.)  Or, if you use a high pass filter, the harmonic
rich ADF4350 provides a very useful 3rd harmonic of -11 dBm at 10 GHz per
N6IZW.

N6IZW provided these register values using ADI's EVB software for 10368.150:
```
R5 0x580005
R4 0x8A003C
R3 0x4B3
R2 0x2004E42
R1 0x8008C81
R0 0x560A08
```

[10368.ino](10368/10368.ino) - This sketch is the same as 1296.ino except that
the ADF4350 is programmed for 10368.150/3 MHz.
