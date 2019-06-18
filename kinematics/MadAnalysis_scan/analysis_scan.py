import glob
import os
import re
import numpy as np
from numpy import genfromtxt
import subprocess
import sys

#running the script python analysis_scan.py file_with_masses


homedir=os.environ.get("HOME")

kinematics="""
    ofstream f("../Output/pTlplus_rr{a:.2e}_mS{b:.2e}_mT{c:.2e}.dat", fstream::app);
    f << lplus.pt()<< endl;
    f.close();

    ofstream f1("../Output/pTlminus_rr{a:.2e}_mS{b:.2e}_mT{c:.2e}.dat", fstream::app);
    f1 << lminus.pt()<< endl;
    f1.close();

    ofstream f2("../Output/pTnu_rr{a:.2e}_mS{b:.2e}_mT{c:.2e}.dat", fstream::app); 
    f2 << nu.pt()<< endl;
    f2.close();

    ofstream f3("../Output/pTpsil_rr{a:.2e}_mS{b:.2e}_mT{c:.2e}.dat", fstream::app);
    f3 << psil.pt()<< endl;
    f3.close();
    

    ofstream f4("../Output/pTvisible_rr{a:.2e}_mS{b:.2e}_mT{c:.2e}.dat", fstream::app);
    f4 << pvisible.Pt()<< endl;                          
    f4.close();

    ofstream f5("../Output/pnu_rr{a:.2e}_mS{b:.2e}_mT{c:.2e}.dat", fstream::app);
    f5 << nu.p()<< endl;
    f5.close();

    ofstream f6("../Output/langle_rr{a:.2e}_mS{b:.2e}_mT{c:.2e}.dat", fstream::app);
    f6 << lplus.angle(lminus)<< endl;
    f6.close();

    ofstream f7("../Output/dphi_rr{a:.2e}_mS{b:.2e}_mT{c:.2e}.dat", fstream::app);
    f7 << lplus.dphi_0_pi(lminus)<< endl;
    f7.close();

    ofstream f8("../Output/theta-lMET_rr{a:.2e}_mS{b:.2e}_mT{c:.2e}.dat", fstream::app);
    f8 << lplus.angle(-pvisible)<< endl;
    f8.close();

    ofstream f9("../Output/m-lnu_rr{a:.2e}_mS{b:.2e}_mT{c:.2e}.dat", fstream::app);
    f9 << plnu.m()<< endl;
    f9.close();
/*
    ofstream f10("../Output/theta_ll_rr{a:.2e}_mS{b:.2e}_mT{c:.2e}.dat", fstream::app);
    f10 << muplus.angle(muminus)<< endl;
    f10.close();

    ofstream f11("../Output/m-ee_rr{a:.2e}_mS{b:.2e}_mT{c:.2e}.dat", fstream::app);
    f11 << pee.m()<< endl;
    f11.close();
*/
    ofstream f12("../Output/m-ll_rr{a:.2e}_mS{b:.2e}_mT{c:.2e}.dat", fstream::app);
    f12 << pll.m()<< endl;
    f12.close();

    ofstream f13("../Output/dphi-lMET_rr{a:.2e}_mS{b:.2e}_mT{c:.2e}.dat", fstream::app);
    f13 << lplus.dphi_0_pi(-pvisible)<< endl;
    f13.close();

"""

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
    with open('analysis_template.cpp','r') as ftemplate:
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
