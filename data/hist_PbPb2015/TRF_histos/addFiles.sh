#!/bin/bash

# REMOVE PREVIOUS SUM FILE
rm hist_TRF_sum.root
FILE_RUN_LIST="../bash_scripts/run_list.txt"

COMMAND_STRING="hadd hist_TRF_sum.root"
FILE_PATH="/home/luca/cernbox/JPSI/Jpsi_polarization_data_sync/hist_trigger_response_function_fixed"

while IFS=FILE_RUN_LIST read LINE; do
  FILE_LIST="$FILE_PATH/Tree_$LINE.root"
  if [ -f $FILE_LIST ]; then
		echo "$LINE exists"
    COMMAND_STRING+=" Tree_$LINE.root"
	else
		echo "$LINE does not exists"
	fi
done <"$FILE_RUN_LIST"

echo "======================"
echo "Go to this address : $FILE_PATH"
echo $COMMAND_STRING