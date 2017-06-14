#!/bin/bash
  CMD="export"
  SEP="="

# test if export is supported
export 1>/dev/null 2>/dev/null
if [ "${?}" == 0 ]; then
  CMD="export"
  SEP="="
else
  setenv 1>/dev/null 2>/dev/null
  if [ "${?} == 0" ]; then
  CMD="setenv"
  SEP=" "
  else
  echo "Neither setenv nor export found!"
  fi
fi 

# find script path
if [ -n "$ZSH_VERSION" ]; then
   SCRIPTPATH="$( cd "$( dirname "${(%):-%x}" )" && pwd )"
elif [ -n "$tcsh" ]; then
   SCRIPTPATH="$( cd "$( dirname "$0" )" && pwd )"
elif [ -n "$BASH_VERSION" ]; then
   SCRIPTPATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
else
   echo "neither bash or zsh is used, abort"
   exit 1
fi

# export GANIL2ROOT environment variable
${CMD} GANIL2ROOT${SEP}$SCRIPTPATH

NPARCH=$(uname)
# mac os x case
if [ "${NPARCH}" = "Darwin" ] ; 
then
  ${CMD} DYLD_LIBRARY_PATH${SEP}$DYLD_LIBRARY_PATH:$GANIL2ROOT/lib
else 
  ${CMD} LD_LIBRARY_PATH${SEP}$LD_LIBRARY_PATH:$GANIL2ROOT/lib
fi

alias g2r='cd $GANIL2ROOT'  

${CMD} GANIL2ROOT_DIR${SEP}$GANIL2ROOT/NPLib
