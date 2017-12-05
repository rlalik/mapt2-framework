#!/bin/env python3

import glob
import collections
from operator import itemgetter

dir_prefix="cards_gps_CR/"

pat_prot="/gps/pos/type Surface\n\
/gps/pos/shape Sphere\n\
/gps/pos/centre 0. 3.5 0. cm\n\
/gps/pos/radius 7 cm\n\
/gps/ang/type cos\n\
/gps/particle proton\n\
/gps/ene/type Arb\n\
/gps/hist/type arb\n\
/gps/hist/file {:s}{:s}\n\
/gps/hist/inter Lin\n"

pat_ion="/gps/source/add {:E}\n\
/gps/pos/type Surface\n\
/gps/pos/shape Sphere\n\
/gps/pos/centre 0. 3.5 0. cm\n\
/gps/pos/radius 7 cm\n\
/gps/ang/type cos\n\
/gps/particle ion\n\
/gps/ion {:d} {:d}\n\
/gps/ene/type Arb\n\
/gps/hist/type arb\n\
/gps/hist/file {:s}{:s}\n\
/gps/hist/inter Lin\n"

fl = glob.glob("*.txt")

class particle:
    def __init__(self):
        A=0
        Z=0
        f=""
        i=0.0

def integrate(f):
    l2 = ""
    l1 = ""

    i = 0.0
    with open(f) as fp:
        for line in fp:
            l2 = line
            if l1 != "":
                n1 = l1.split()
                n2 = l2.split()
                f1_1 = float(n1[0])
                f1_2 = float(n1[1])
                f2_1 = float(n2[0])
                f2_2 = float(n2[1])
                i += (f2_1 - f1_1) * (f1_2 + f2_2) / 2.0
            l1 = l2
    return i

particles = {}

max_i = 0.0

for f in fl:
    # integrate spectrum
    i=integrate(f)
    # find maximum integral for normalization
    if i > max_i:
        max_i = i

if max_i == 0.0:
    print("INTEGRATION ERROR")
    max_i = 1.0

for f in fl:
    # integrate spectrum
    i=integrate(f)

    # get the name
    parts=f.split('_')
    if len(parts) == 2:
        t = pat_prot.format(dir_prefix, f)
        particles[int(parts[0])] = t
    if len(parts) == 3:
        t = pat_ion.format(i/max_i, int(parts[1]), int(parts[0]), dir_prefix, f)
        particles[int(parts[0])] = t

pp = collections.OrderedDict(sorted(particles.items(), key=itemgetter(0)))
#pp.sort(key=itemgetter(1))

#print(pp)
for p,v in pp.items():
    print(v)
