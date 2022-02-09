#!/bin/bash 

FILE_RUN_LIST="bash_scripts/run_list.txt"
FILE_SUBMITTED_RUNS="bash_scripts/submitted_jobs.txt"
COUNTER=0
while IFS=FILE_RUN_LIST read LINE; do
	if grep -Fxq "$LINE" $FILE_SUBMITTED_RUNS; then
		((COUNTER++))
		echo "$COUNTER) $LINE ALREADY EXISTS"
	else
		echo "$LINE DOES NOT EXIST"
		break
	fi
done <"$FILE_RUN_LIST"

echo "$LINE" >> "bash_scripts/submitted_jobs.txt"
root -b -q RunPbPb_JPsi_Grid.C\(\"full\",$LINE\)
