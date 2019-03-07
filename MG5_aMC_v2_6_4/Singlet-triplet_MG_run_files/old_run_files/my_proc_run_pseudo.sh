#!/bin/bash

# set the paths
MGdir=~/mywork/llp/soft_LLP/MG5_aMC_v2_6_4
CARDdir=$MGdir/Singlet-triplet_MG_run_files

# set proc card file
PROC_CARD="proc_card_pseudo.dat"


# go to MG and generate the process
cd $MGdir
./bin/mg5 $CARDdir/$PROC_CARD
