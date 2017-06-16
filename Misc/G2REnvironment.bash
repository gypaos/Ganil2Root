# This File contains all environment variables needed by Ganil2Root.
# On linux system, include it in your bashrc or tcshrc file.


# Ganil2Root needs
# WARNING: if you run Ganil2Root at GANIL, the GRUSYS variable
# should be already defined. Check it before redefining it!!
export GRUSYS=/home/acqexp/GRU/GRUcurrent

#export GANIL2ROOT=/your/path/to/ganil2root/directory
export GANIL2ROOT=/home/muvi/e748/ganil2root
export LD_LIBRARY_PATH=$GANIL2ROOT/libs:$LD_LIBRARY_PATH
# if running on Mac OS X, add the following line
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$GANIL2ROOT/libs
