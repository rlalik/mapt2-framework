#!/bin/env python2

import ROOT
from mgeanttrack import MGeantTrack
from mgeantfibersraw import MGeantFibersRaw
from mfiberscal import MFibersCal
from mapt_python import MAPT

from optparse import OptionParser

parser = OptionParser()

(options, args) = parser.parse_args()

if __name__ == "__main__":
    print(options)
    print(args)

    if len(args) == 0:
        exit(1)

    m = MAPT()
    m.initAnalysis(args[0], 10000)

    events = m.getEventsNumber()
    print(events)
    for i in range(0, events):
        print("Get event {0}".format(i))
        m.getEvent(i)

        print(m.getGeantTrackNum(), m.getGeantFibersRawNum(), m.getFibersCalSimNum(), m.getFibersCalNum())

        n = m.getGeantTrackNum()
        if n < 0:
            print("Nothing in GeantTrack")
        else:
            print("{0} objects in {1!s}".format(m, "GeantTrack"))
            for j in range(0, n):
                track = m.getGeantTrack(j)
                track._print()

        n = m.getGeantFibersRawNum()
        if n < 0:
            print("Nothing in GeantFibersRaw")
        else:
            print("{0} objects in {1!s}".format(m, "GeantFibersRaw"))
            for j in range(0, n):
                fiber = m.getGeantFibersRaw(j)
                fiber._print()

        n = m.getFibersCalSimNum()
        if n < 0:
            print("Nothing in FibersCalSim")
        else:
            print("{0} objects in {1!s}".format(m, "FibersCalSim"))
            for j in range(0, n):
                fiber = m.getFibersCalSim(j)
                fiber._print()

        n = m.getFibersCalNum()
        if n < 0:
            print("Nothing in FibersCal")
        else:
            print("{0} objects in {1!s}".format(m, "FibersCal"))
            for j in range(0, n):
                fiber = m.getFibersCal(j)
                fiber._print()
