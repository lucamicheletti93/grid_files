#!/bin/bash

fileRunList="bash_scripts/to_resubmit.txt"

while IFS= read line
do
	fileXml="$line.xml"
	if [ -f "$fileXml" ]; then
	echo "the file $line.xml exists!"
	else
	echo "the file $line.xml does not exist!"
	break
	fi
done <"$fileRunList"
root -b -q Read_MC.C\(\"full\",$line\)
