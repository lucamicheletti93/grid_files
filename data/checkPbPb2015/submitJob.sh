#!/bin/bash 

FILE_RUN_LIST="bash_scripts/run_list.txt"
FILE_SUBMITTED_RUNS="bash_scripts/submitted_jobs.txt"
while IFS=FILE_RUN_LIST read LINE; do
	if grep -Fxq "$LINE" $FILE_SUBMITTED_RUNS; then
		echo "$LINE exists"
	else
		echo "$LINE does not exists"
		break
	fi
done <"$FILE_RUN_LIST"

echo "$LINE" >> "bash_scripts/submitted_jobs.txt"
root -b -q RunPbPb_JPsi_Grid.C\(\"full\",$LINE\)
