#!/bin/bash

# set the paths
MGdir=~/mywork/soft/MG5_aMC_v2_6_5

CARDdir=$MGdir/Singlet-triplet_MG_run_files

# move the new cards into the Card directory
#rm $MGdir/pp-Z-leptons_"$1"/Cards/param_card.dat
cp $CARDdir/param_card.dat $MGdir/soft_llp_ST/pp-Z-leptons_"$1"/Cards/
cp $CARDdir/run_card.dat $MGdir/soft_llp_ST/pp-Z-leptons_"$1"/Cards/run_card.dat
cp $CARDdir/me5_configuration.txt $MGdir/soft_llp_ST/pp-Z-leptons_"$1"/Cards/me5_configuration.txt
cp $CARDdir/madanalysis5_parton_card.dat $MGdir/soft_llp_ST/pp-Z-leptons_"$1"/Cards/madanalysis5_parton_card.dat

# go to MG and start the process
cd $MGdir/soft_llp_ST/pp-Z-leptons_"$1"
pwd
#loading root for madanalysis
module load phys/root/6.10
./bin/generate_events -f rr"$4"_mS"$2"_mT"$3"
