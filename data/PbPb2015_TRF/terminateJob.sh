#!/bin/bash

FILE_RUN_LIST="bash_scripts/submitted_jobs.txt"
FILE_TERMINATED_RUNS="bash_scripts/terminated_jobs.txt"
FILE_RETERMINATED_RUNS="bash_scripts/reterminated_jobs.txt"
RUN_TO_TERMINATE=false
COUNTER=0

while IFS=FILE_RUN_LIST read LINE; do
	if grep -Fxq "$LINE" $FILE_TERMINATED_RUNS; then
		((COUNTER++))
		echo "$COUNTER) RUN $LINE ALREADY TERMINATED"
	else
		echo "RUN $LINE NOT YET TERMINATED, TERMINATE!"
		RUN_TO_TERMINATE=true
		break
	fi
done < "$FILE_RUN_LIST"

COUNTER=0

if $RUN_TO_TERMINATE ; then
	echo "TERMINATE $LINE"
	echo "$LINE" >> "bash_scripts/terminated_jobs.txt"
	root -b -q RunPbPb_JPsi_Grid.C\(\"terminate\",$LINE\)
else
	echo "==================================="	
	while IFS=FILE_TERMINATED_RUNS read LINE; do
		if grep -Fxq "$LINE" $FILE_RETERMINATED_RUNS; then
			((COUNTER++))
			echo "$COUNTER) RUN $LINE ALREADY RETERMINATED"
		else
			echo "RUN $LINE NOT YET RETERMINATED, DO YOU  WANT TO RETERMINATE?"
			break
		fi
	done < "$FILE_TERMINATED_RUNS"

	echo "$LINE" >> "bash_scripts/reterminated_jobs.txt"
	root -b -q RunPbPb_JPsi_Grid.C\(\"terminate\",$LINE\)
fi

#while IFS=FILE_RUN_LIST read LINE; do
	#echo "cp PbPb2015_pDCA/LHC15o/muon_calo_pass1/$LINE/OutputTree/000/Tree_$LINE.root file:."
#done < "$FILE_RUN_LIST"
