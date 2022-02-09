#!/bin/bash

FILE_TERMINATED_RUNS="bash_scripts/reterminated_jobs.txt"
ALIEN_PATH="test_PbPb2015_KINT7inMUON_ONLY/LHC15o/muon_calo_pass1"
#LOCAL_PATH="/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/hist_checkPbPb2015/PS_CMUL7"
#LOCAL_PATH="/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/hist_checkPbPb2015/AOD175"
#LOCAL_PATH="/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/hist_checkPbPb2015/old_PS_CMUL7_or_CINT7"
#LOCAL_PATH="/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/tests/OLD_PS"
#LOCAL_PATH="trees"
LOCAL_PATH="/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/fixed_hist_trigger_response_function/DATA"

RUN_TO_ADD=true

while IFS=FILE_TERMINATED_RUNS read LINE; do
    if [ $(find "$LOCAL_PATH" -name "Tree_$LINE.root") ]; then 
        echo "Tree_$LINE already downloaded"
    else
        echo "cp $ALIEN_PATH/$LINE/OutputTree/000/Tree_$LINE.root file:$LOCAL_PATH/."
        RUN_TO_ADD=false
    fi
done < "$FILE_TERMINATED_RUNS"

COMMANDSTRING="hadd hist_TRF_DATA.root"

if $RUN_TO_ADD ; then
    echo "ALL RUNS DOWNLOADED"
    while IFS=FILE_TERMINATED_RUNS read LINE; do
    COMMANDSTRING+=" Tree_$LINE.root"
done < "$FILE_TERMINATED_RUNS"
fi

echo $COMMANDSTRING