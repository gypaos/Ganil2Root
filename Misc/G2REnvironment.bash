# This File contains all environment variables needed by Ganil2Root.
# On linux system, include it in your bashrc or tcshrc file.


# Ganil2Root needs
# WARNING: if you run Ganil2Root at GANIL, the GRUSYS variable
# should be already defined. Check it before redefining it!!
export GRUSYS=/your/path/to/GRU/installation

export GANIL2ROOT=/your/path/to/ganil2root/directory
export LD_LIBRARY_PATH=$GANIL2ROOT/libs:$LD_LIBRARY_PATH
# if running on Mac OS X, add the following line
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$GANIL2ROOT/libs
