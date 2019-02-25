#!/bin/bash

FILE_TERMINATED_RUNS="bash_scripts/terminated_jobs.txt"
ALIEN_PATH="PbPb2015_pDCA_TRF_hist_new/LHC15o/muon_calo_pass1"
LOCAL_PATH="/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/new_hist_trigger_response_function_fixed"

while IFS=FILE_TERMINATED_RUNS read LINE; do
    if [ $(find "$LOCAL_PATH" -name "Tree_$LINE.root") ]; then 
    echo "Tree_$LINE already downloaded"
    else
    echo "cp $ALIEN_PATH/$LINE/OutputTree/000/Tree_$LINE.root file:$LOCAL_PATH/."
    fi
done < "$FILE_TERMINATED_RUNS"