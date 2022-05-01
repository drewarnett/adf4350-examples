#!/usr/bin/env python3

"""ADF4350 R4 keying

Tool to generate set of R4 values for Arduino sketch for PLL output buffer
keying.

Run from the command line and copy and paste the output into your Arduino
sketch.  Example use:

$ python3 adf4350-r4-keying.py 
Original R4 value:  0x9A013C
#define KEYDOWN    0X009A003CU
#define KEYDOWN_M3 0X009A0034U
#define KEYDOWN_M6 0X009A002CU
#define KEYDOWN_M9 0X009A0024U
#define KEYUP      0X009A0004U
#define REGISTER_4 KEYUP
"""


def check_uint(value, size):
    """return True if uint value OK"""

    return isinstance(value, int) and value >= 0 and value.bit_length() <= size


def make_value(
        original, output_enable, output_power, aux_enable=False, aux_power=0):
    """return value with main and aux outputs per given"""

    assert check_uint(original, 32), original
    assert isinstance(output_enable, bool)
    assert check_uint(output_power, 2), output_power
    assert isinstance(aux_enable, bool)
    assert check_uint(aux_power, 2), aux_power

    rval = original & (~(1 << 5)) | (int(output_enable) << 5)
    rval = rval & (~(0b11 << 3)) | ((output_power) << 3)
    rval = rval & (~(1 << 8)) | (int(aux_enable) << 8)
    rval = rval & (~(0b11 << 6)) | ((aux_power) << 6)

    return rval


if __name__ == '__main__':
    original = int(input('Original R4 value:  '), 0)

    print('#define KEYDOWN    {:#010X}U'.format(make_value(original, True, 3)))
    print('#define KEYDOWN_M3 {:#010X}U'.format(make_value(original, True, 2)))
    print('#define KEYDOWN_M6 {:#010X}U'.format(make_value(original, True, 1)))
    print('#define KEYDOWN_M9 {:#010X}U'.format(make_value(original, True, 0)))
    print(
        '#define KEYUP      {:#010X}U'.format(make_value(original, False, 0)))
    print('#define REGISTER_4 KEYUP')
