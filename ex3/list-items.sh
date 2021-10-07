#!/bin/bash

# "rename" the input arguments
path=$1
flag=$2

# check number of arguments
if [ $# -ne 2 ]; then
   echo "Usage: $0 DIR_PATH -d|-f"
   exit 1
fi

# check first argument
if [ ! -d "$path" ]; then
   echo "First argument $path should correspond to an existing directory path"
   exit 2
fi

# check second argument
if   [ "$flag" == "-f" ]; then
   permissionChar="-"
elif [ "$flag" == "-d" ]; then
   permissionChar="d"
else
   echo "Second argument $flag should be -d or -f"
   exit 2
fi

# use $permissionChar to filter files or directories according to flag
ls -l $path | grep "^$permissionChar" | sed -r 's/^.*[ ](.*)$/\1/'




