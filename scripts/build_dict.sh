#!/bin/bash

# This script detect the root version and call the command necessary to build 
# a Dictionnary, rootmap and pcm file accordingly

# check rootcint exist
command -v rootcint >/dev/null 2>&1 || { printf >&2 "ERROR : rootcint binary not found.\n * For ROOT install from source check that \$ROOTSYS/bin is in your PATH\n * For Macports ROOT install consider adding /opt/local/bin to your PATH\n * For debian ROOT install consider adding /usr/bin to your PATH\n"; exit 1; }

# Checking that enought argument are given
if [ "$#" -lt 5 ]
  then
    echo "Dictionnary Generation in : $PWD"
    echo "Incorrect argument number : 1.DictName 2.Rootmap 3.LibName 4.LinkDefFile 5+.Header "
    echo "Arguments are : $@"
    exit 1
fi

# Modify the lib name according to the system
lib_ext=.so
system=$(uname -a)
system="${system/%\ */}"
if [ "$system" == "Darwin" ]
  then
    lib_ext=.dylib
fi

lib_name=$3
lib_name="${lib_name%.*}"
lib_name="$lib_name$lib_ext"

# Detect the Root
is_root=$(which root-config)

# Detect the version
if [ $is_root != "" ]; 
  then
    version=$(root-config --version)
  else 
    echo  "root-config not found"
    exit 1
fi

# Get the Major version
version_major="${version%.*}"

# if before version 4, exit
if [ $version_major -lt 5 ]
  then
    echo "Root version too old, min. version 5" 
    exit 1
fi

header=""
COUNTER=1
for VAR in "$@"
do
  if [ $COUNTER -gt 4 ]; then
    header="$header $VAR"
  fi
  let COUNTER=COUNTER+1
done

# Version 5 : generate the dictionnary then the libmap
if [ $version_major -eq 5 ]
  then
    rootcint -f $1 -c -p -I../Core -I../../Core -I$GRUDIR/include -I$GRUDIR/MFMlib -I$NPTOOL/NPLib/include $header $4	
fi

# Version 6 or more : generate both at once
if [ $version_major -gt 5 ]
  then
   rootcint -f $1 -rmf $2 -rml $lib_name -I../Core -I../../Core -I$GRUDIR/include -I$NPTOOL/NPLib/include $header $4
fi




