#! /usr/bin/env python3

"""make sketches

Automatically builds Arduino sketches (.ino files).

Uses:
   'template.ino'
    '../example registers.csv'
"""

import os


def get_register_info():
    """get register info from 'example registers.csv'

    returns a dictionary:
        key:  rf freq_if freq_lo type_multiplier_synthesizer freq

        value:  dictionary
            key:  in ('R0', 'R1', 'R2', 'R3', 'R4', 'R5')
            value:  register value (int)
    """

    here = os.path.split(__file__)[0]

    rval = dict()

    with open(os.path.join(here, "..", "example registers.csv")) as ifh:
        header = ifh.readline().rstrip()
        assert header == (
            'RF frequency,IF frequency,LO type,Multiplier,'
            'Synthesizer frequency,R0,R1,R2,R3,R4,R5')
        for line in ifh.readlines():
            (
                rf_freq,
                if_freq,
                lo_type,
                multiplier,
                synth_freq,
                reg0, reg1, reg2, reg3, reg4, reg5
                ) = line.rstrip().split(',')

            assert lo_type in ("low", "high"), lo_type
            given = int(synth_freq)
            calculated = None
            if lo_type == "low":
                calculated = (int(rf_freq) - int(if_freq))/int(multiplier)
            else:
                calculated = (int(rf_freq) + int(if_freq))/int(multiplier)
            assert given == calculated, line

            multiplier = "x" + multiplier
            key = "_".join((rf_freq, if_freq, lo_type, multiplier, synth_freq))

            def touchup(register_value):
                """touch up the register value a bit"""

                padding = 8 - len(register_value)
                assert 0 <= padding <= 7, (padding, register_value)
                return "0x" + padding*"0" + register_value + "U"

            value_dict = {
                'R0':  touchup(reg0),
                'R1':  touchup(reg1),
                'R2':  touchup(reg2),
                'R3':  touchup(reg3),
                'R4':  touchup(reg4),
                'R5':  touchup(reg5)
                }

            rval[key] = value_dict

    return rval


def fillout(template, adict):
    """returns copy of template filled out per adict

    applies str.replace for every entry in adict
    """

    rval = template[:]
    for key in adict:
        rval = rval.replace(key, adict[key])
    return rval


if __name__ == "__main__":
    REGISTER_INFO = get_register_info()
    TEMPLATE = open("template.txt").read()

    for configuration in REGISTER_INFO:
        fn = configuration + ".ino"
        print(fn)
        with open(fn, "w") as ofh:
            ofh.writelines(fillout(TEMPLATE, REGISTER_INFO[configuration]))
