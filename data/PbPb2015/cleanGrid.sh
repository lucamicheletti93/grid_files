#!/bin/bash

fileRunList="bash_scripts/run_list.txt"
fileDownloadedTrees="bash_scripts/downloaded_trees.txt"

while IFS=fileRunList read line; do
  downloadedFile="/media/luca/488AE2208AE20A70/PbPb_2015_Trees_pDCA/Tree_$line.root"
	if [ -f "$downloadedFile" ]; then
    echo "cd ; cd PbPb2015_pDCA/LHC15o/muon_calo_pass1/$line/OutputTree/000/ ; mv Tree_$line.root ../ ; cd ../ ; rmdir 000"
    echo "$line" >> "bash_scripts/downloaded_trees.txt"
  else
    echo "re-terminate the file"
    #echo "rm 000$line.xml" >> "bash_scripts/to_reterminate.txt"
    #echo "rmdir PbPb2015_pDCA/LHC15o/muon_calo_pass1/$line" >> "bash_scripts/to_reterminate.txt"
    #echo "$line" >> "bash_scripts/to_reterminate.txt"
	fi
done < "$fileRunList"

echo "--- List of files to be downloaded ---"
while IFS=fileRunList read line; do
  if grep -Fxq "$line" $fileDownloadedTrees; then
    echo "The file exists"
  else
    echo "cd ; cd PbPb2015_pDCA/LHC15o/muon_calo_pass1/$line/OutputTree/000/ ; cp Tree_$line.root file:."
  fi
done < "$fileRunList"
