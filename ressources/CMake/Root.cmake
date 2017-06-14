# This file find your active root installation and use it for configuration
# Simplified version of the macro from Fair Root

message("Looking for Root:")
set(G2R_ROOT_SEARCHPATH 
    $ENV{ROOTSYS}/bin 
    $ENV{PATH}
    /usr/bin  # Debian install
    /opt/local/bin # Macports install
    /usr/local/bin
    )

find_program(G2R_ROOT_CONFIG NAMES root-config PATHS ${G2R_ROOT_SEARCHPATH} )
if(G2R_ROOT_CONFIG MATCHES "NOTFOUND")
  message(FATAL_ERROR "ROOT is not found, check your installation")
endif()

exec_program(${G2R_ROOT_CONFIG} ARGS "--version" OUTPUT_VARIABLE G2R_ROOT_VERSION)
# now parse the parts of the user given version string into variables
string(REGEX REPLACE "^([0-9]+)\\.[0-9][0-9]+\\/[0-9][0-9]+" "\\1" req_root_major_vers "${ROOT_MIN_VERSION}")
string(REGEX REPLACE "^[0-9]+\\.([0-9][0-9])+\\/[0-9][0-9]+.*" "\\1" req_root_minor_vers "${ROOT_MIN_VERSION}")
string(REGEX REPLACE "^[0-9]+\\.[0-9][0-9]+\\/([0-9][0-9]+)" "\\1" req_root_patch_vers "${ROOT_MIN_VERSION}")

# and now the version string given by cmake
string(REGEX REPLACE "^([0-9]+)\\.[0-9][0-9]+\\/[0-9][0-9]+.*" "\\1" found_root_major_vers "${ROOTVERSION}")
string(REGEX REPLACE "^[0-9]+\\.([0-9][0-9])+\\/[0-9][0-9]+.*" "\\1" found_root_minor_vers "${ROOTVERSION}")
string(REGEX REPLACE "^[0-9]+\\.[0-9][0-9]+\\/([0-9][0-9]+).*" "\\1" found_root_patch_vers "${ROOTVERSION}")


set(G2R_ROOT_VERSION_MAJOR "0")

if(found_root_major_vers LESS 5)
  message( FATAL_ERROR "Invalid ROOT version \"${G2R_ROOT_VERSION}\", at least major version 5 is required")
elseif(found_root_major_vers LESS 6)
  set(G2R_ROOT_VERSION_MAJOR "5")
else()
  set(G2R_ROOT_VERSION_MAJOR "6")
endif()


message(" Root ${G2R_ROOT_VERSION} found")

## Collect the different information ##

# List of Root dependencies
exec_program(${G2R_ROOT_CONFIG} ARGS "--libs" OUTPUT_VARIABLE ROOT_LIBRARIES)
set(ROOT_LIBRARIES ${ROOT_LIBRARIES} -lXMLParser -lXMLIO -lSpectrum )
#set(ROOT_LIBRARIES Gui Core RIO Net Hist Graf Graf3d Gpad Tree Rint Postscript Matrix Physics MathCore Thread MultiProc )

# Lib directories
exec_program(${G2R_ROOT_CONFIG} ARGS "--libdir" OUTPUT_VARIABLE ROOT_LIBRARY_DIR)
link_directories( ${ROOT_LIBRARY_DIR})  

# Include directories
exec_program(${G2R_ROOT_CONFIG} ARGS "--incdir" OUTPUT_VARIABLE ROOT_INCLUDE_DIR)
include_directories(SYSTEM ${ROOT_INCLUDE_DIR})  

# Get the compilator flag from root to assure consistancy
exec_program(${G2R_ROOT_CONFIG} ARGS "--cflags" OUTPUT_VARIABLE G2R_ROOT_CFLAGS )
if(CMAKE_CXX_FLAGS)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${G2R_ROOT_CFLAGS}")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS_RELEASE} ${G2R_ROOT_CFLAGS}")
endif()
