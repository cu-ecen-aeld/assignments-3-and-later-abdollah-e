# In the name of Allah 
#!/bin/bash

if [ $# -ne 2 ]  ; then 
    echo "Please provide two arguments - filesDir and searchStr"
    exit 1
fi

writeFile="$1"
writestr="$2"

dirPath=$(dirname "$writeFile")
fileName=$(basename "$writeFile")



if [ ! -d "$dirPath" ] ; then 
    echo "writer: Directory does not exist - creating drirectory structure..."
    mkdir -p "$dirPath"
fi    

if [ ! -f "$writeFile" ] ; then 
    echo "writer: File does not exist - creating file"
    touch "$writeFile"
else 
    echo "writer: File exists overwritting file" 
    rm "$writeFile"
    touch "$writeFile"  
fi

if [ $? -eq 1 ] ; then 
   echo "error while creating file"
   exit 1
fi

echo "$writestr" > "$writeFile"


   
