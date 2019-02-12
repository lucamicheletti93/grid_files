#!/bin/bash

fileRunList="bash_scripts/run_list.txt"
fileSubmittedRuns="bash_scripts/submitted_jobs.txt"
while IFS=fileRunList read line; do
	if grep -Fxq "$line" $fileSubmittedRuns; then
		echo "$line exists"
	else
		echo "$line does not exists"
		break
	fi
done <"$fileRunList"

echo "$line" >> "bash_scripts/submitted_jobs.txt"
root -b -q RunPbPb_JPsi_Grid.C\(\"full\",$line\)
