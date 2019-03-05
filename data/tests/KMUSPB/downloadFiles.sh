#!/bin/bash

FILE_TERMINATED_RUNS="bash_scripts/reterminated_jobs.txt"
ALIEN_PATH="test_PbPb2015_OLD_PS/LHC15o/muon_calo_pass1"
#LOCAL_PATH="/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/hist_checkPbPb2015/PS_CMUL7"
#LOCAL_PATH="/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/hist_checkPbPb2015/AOD175"
#LOCAL_PATH="/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/hist_checkPbPb2015/old_PS_CMUL7_or_CINT7"
#LOCAL_PATH="/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/tests/OLD_PS"
LOCAL_PATH="trees"

while IFS=FILE_TERMINATED_RUNS read LINE; do
    if [ $(find "$LOCAL_PATH" -name "Tree_$LINE.root") ]; then 
        echo "Tree_$LINE already downloaded"
    else
        echo "cp $ALIEN_PATH/$LINE/OutputTree/000/Tree_$LINE.root file:$LOCAL_PATH/."
    fi
done < "$FILE_TERMINATED_RUNS"
