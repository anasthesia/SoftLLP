import glob
import re
import numpy as np
from numpy import genfromtxt
import subprocess
import sys

#running the script python main_MG_scan_file.py file_with_params scalar/pseudo
# running script that generates the process (no need to use every time)
'''
print('generating process...')
subprocess.call(['./my_proc_run_scalar.sh'], stdout=subprocess.PIPE)
subprocess.call(['./my_proc_run_pseudo.sh'], stdout=subprocess.PIPE)
print('DONE')
'''

#positiveMS='/Users/stasya/Dropbox/prj/micromegas_4.3.5/Singlet-Triplet_main_cycle/finalscans/'
#negativeMS='/Users/stasya/Dropbox/prj/micromegas_4.3.5/Singlet-Triplet_main_cycle/negative/'

#reading mS and mT for which we want to run MG
masses = genfromtxt(sys.argv[1],  comments="#", delimiter=' ')
print(masses)



for i in range(masses.shape[0]):
    print('----------------------------------------------------------------------')
    print('i={}'.format(i))
    # writing mS and mT to parameter card param_card_new.dat (param_card_raw.dat is used as a template)
    with open('param_card_raw.dat','r') as fin:
        with open('param_card.dat','w') as fout:
            lines=fin.readlines()

            for lnnum, ln in enumerate(lines):
                if ln.startswith("Block frblock"):
                    #ms
                    lines[lnnum+1]=re.sub("1\s([\S]+)\s",'1 '+'{:.4e}'.format(masses[i,1])+' ',lines[lnnum+1])
                    print(lines[lnnum+1])

                    #mt
                    lines[lnnum+2]=re.sub("2\s([\S]+)\s",'2 '+'{:.4e}'.format(masses[i,2])+' ',lines[lnnum+2])
                    print(lines[lnnum+2])

                    #rr
                    lines[lnnum+3]=re.sub("3\s([\S]+)\s",'3 '+'{:.4e}'.format(masses[i,3])+' ',lines[lnnum+3])
                    print(lines[lnnum+3])

            fout.writelines(lines)

    #running script that generates events on parameter cards created


    print('generating events...')
    subprocess.call(['./my_event_generation_run.sh', sys.argv[2],'{:.2e}'.format(masses[i,1]),'{:.2e}'.format(masses[i,2]),'{:.2e}'.format(masses[i,3])])
    ##subprocess.call(['./my_event_generation_run.sh], stdout=subprocess.PIPE')
    #print('DONE')
