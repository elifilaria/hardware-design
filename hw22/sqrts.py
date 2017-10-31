# print square roots in Python language.  R. Brown, 9/2010 

import sys

from math import sqrt

print("sqrt(n)\n--------")

maxi = int(sys.argv[1])

for n in range(0, maxi+1):
    print(sqrt(n))
