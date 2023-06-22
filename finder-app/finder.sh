# In the name of God
#!/bin/bash

if [ $# -ne 2 ]  ; then 
    echo "Please provide two arguments - filesDir and searchStr"
    exit 1   
fi

filesDir="$1"

if [ ! -d "$filesDir" ] ; then
    echo "error - path provided for filesDir is not a directory path"
    exit 1   
fi

cd $filesDir

numOfFiles=0

for file in *
do 
    if [ -f $file ]; then
        numOfFiles=$((numOfFiles + 1))
    fi    
done         


searchStr="$2"
matchingLines=0

for x in `grep -c -r "$searchStr" *`
 do 
 	matchingLines=$((matchingLines + 1))
 
done 

echo "The number of files are ${numOfFiles} and the number of matching lines are ${matchingLines}"	         
