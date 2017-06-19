add_custom_command(OUTPUT G2RExlDict.cxx G2RExlDict_rdict.pcm G2RExlDict.rootmap COMMAND ../../scripts/build_dict.sh G2RExlDict.cxx G2RExlDict.rootmap libG2RExl.so G2RExlLinkDef.h G2RExl.h)
add_library(G2REXL SHARED G2RExl.cxx G2RExlDict.cxx)
target_link_libraries(G2REXL ${ROOT_LIBRARIES} G2RCore) 

install(FILES G2RExl.h DESTINATION ${CMAKE_INCLUDE_OUTPUT_DIRECTORY})

if(${G2R_ROOT_VERSION_MAJOR} GREATER 5) 
install(FILES G2RExlDict_rdict.pcm G2RExlDict.rootmap DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
endif()
