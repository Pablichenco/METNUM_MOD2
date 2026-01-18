import numpy as np
import glob
import os
import re

   
cadena = "/Users/pabare/Documents/Xcode_projects/mod2/mod2/data/ising_results_L16.dat"
print()
print("DIRECCION")
print(cadena)

print()
cadena = cadena[-6:-4]
print("NUEVA DIRECCION")
print(cadena)

# Extract lattice size from filename
# L = int(cadena.split('L')[0][0:1])
L = int(re.sub('[^0-9]', '', cadena))

print("Número : " + str(L))
    
