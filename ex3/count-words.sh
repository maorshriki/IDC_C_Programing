#!/bin/bash

#############################################
# Script count-words.sh for counting files
# that contain words recursively in a given
# path
#############################################

# "rename" the input arguments
path=$1
word=$2

# check number of arguments
if [ $# -ne 2 ]; then
   echo "Usage: $0 PATH WORD"
   exit 11
fi

# check first argument
if [ ! -e "$path" ]; then
   echo "First argument $path should correspond to an existing path"
   exit 202
fi

if [ -f "$path" ]; then
   # if path is a file, then print 1 if it contains word and 0 otherwise
   num_words=`cat $path | tr [[:space:]] "\n" | grep -c "^$word$"`
   if [ $num_words -gt 0 ]; then
      echo 1
   else
      echo 0
   fi
   exit 0
fi

if [ ! -d "$path" ]; then
   echo "Code should not reach here - input path $path exists but is not a file or a directory"
   exit 111
fi

# if code reached here, then path is a valid directory

# determine all files and immediate subdirectories
files=`./list-items.sh $path -f`
dirs=`./list-items.sh $path -d`
files_and_dirs="$files $dirs"

# iterate over all files / subdirectories, recursively apply script, and sum the counts
# note that the recursive calls are guaranteed to complete successfully because path is valid

total_sum=0
for item in $files_and_dirs; do
   count=`$0 $path/$item $word`
   ((total_sum+=count))   
done
echo $total_sum
