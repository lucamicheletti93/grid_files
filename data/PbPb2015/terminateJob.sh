#!/bin/bash

#fileRunList="bash_scripts/run_list.txt"
#fileTermianteRuns="bash_scripts/terminated_jobs.txt"

fileRunList="bash_scripts/to_reterminate.txt"
fileTermianteRuns="bash_scripts/reterminated_jobs.txt"

while IFS=fileRunList read line; do
	if grep -Fxq "$line" $fileTermianteRuns; then
		echo "$line exists"
	else
		echo "$line does not exists"
		break
	fi
done < "$fileRunList"

#echo "$line" >> "bash_scripts/terminated_jobs.txt"
echo "$line" >> "bash_scripts/reterminated_jobs.txt"
root -b -q RunPbPb_JPsi_Grid.C\(\"terminate\",$line\)

#while IFS=fileTermianteRuns read line1; do
	#while IFS=fileRunList read line2; do
		#if [[ $line1 == *"$line2"* ]]; then
	    #echo "$line1 = $line2"
		#else
			#echo "$line1 !=! $line2"
			#break
		#fi

	#done < "$fileRunList"
#done < "$fileTermianteRuns"

#echo "$line2" >> "terminated_runs.txt"
