import glob
import os
import re
import numpy as np
from numpy import genfromtxt
import subprocess
import sys

#running the script python analysis_scan.py file_with_masses file_with_kinematic-functions-to-build


homedir=os.environ.get("HOME")

# specifying kinematic functions to build
with open(sys.argv[2],'r') as fkinfunc:
    kinfunc=fkinfunc.readlines()

kinematics="".join(kinfunc)


inputevents=os.path.join(homedir,'MG/soft_llp_ST/pp-Z-leptons_scalar/Events/rr{a:.2e}_mS{b:.2e}_mT{c:.2e}/unweighted_events.lhe.gz')

#reading mS and mT for which we want to run analysis
masses = genfromtxt(sys.argv[1],  comments="#", delimiter=' ')
print(masses)

for i in range(masses.shape[0]):
    print('----------------------------------------------------------------------')
    print('i={}'.format(i))

    #writing an input file that will be used for analysis
    with open(os.path.join(homedir,'MG/llp_kinematics/Input/tmp'),'w') as inputfile:
        inputfile.write(inputevents.format(a=masses[i,2],b=masses[i,0],c=masses[i,1]))


    # including kinematic variables to calculate
    with open('analysis_template_rec-events.cpp','r') as ftemplate:
        with open(os.path.join(homedir,'MG/llp_kinematics/Build/SampleAnalyzer/User/Analyzer/debug_distributions.cpp'),'w') as fout:

            lines=ftemplate.readlines()
            #print(lines)

            for line in lines:
                if line.startswith("// start here"):
                    fout.write(kinematics.format(a=masses[i,2],b=masses[i,0],c=masses[i,1]))
                else:
                    fout.write(line)


    print('running analysis')
    cmd ='source '+os.path.join(homedir,'MG/llp_kinematics/Build/setup.sh')+ ' && make -C '+ os.path.join(homedir,'MG/llp_kinematics/Build/') +'  && '+os.path.join(homedir,'MG/llp_kinematics/Build/MadAnalysis5job')+' '+os.path.join(homedir,'MG/llp_kinematics/Input/tmp')
    print(cmd)
    subprocess.call([cmd], shell=True)
