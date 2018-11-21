add_custom_command(OUTPUT G2RCATSDict.cxx G2RCATSDict_rdict.pcm G2RCATSDict.rootmap COMMAND ../../scripts/build_dict.sh G2RCATSDict.cxx G2RCATSDict.rootmap libG2RCATS.so G2RCATSLinkDef.h G2RCATS.h)
add_library(G2RCATS SHARED G2RCATS.cxx G2RCATSDict.cxx)
target_link_libraries(G2RCATS ${ROOT_LIBRARIES} G2RCore) 

install(FILES G2RCATS.h DESTINATION ${CMAKE_INCLUDE_OUTPUT_DIRECTORY})

if(${G2R_ROOT_VERSION_MAJOR} GREATER 5) 
install(FILES G2RCATSDict_rdict.pcm G2RCATSDict.rootmap DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
endif()
