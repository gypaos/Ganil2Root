add_custom_command(OUTPUT G2RCoreDict.cxx G2RCoreDict_rdict.pcm G2RCoreDict.rootmap COMMAND ../scripts/build_dict.sh G2RCoreDict.cxx G2RCoreDict.rootmap libG2RCore.so G2RCoreLinkDef.h G2RVDetector.h G2RModularLabel.h DEPENDS G2RCoreLinkDef.h G2RVDetector.h G2RModularLabel.h )
add_library(G2RCore SHARED G2RModularLabel.cxx G2RVDetector.cxx G2RDetectorManager.cxx G2RCoreDict.cxx G2RDetectorFactory.cxx)
target_link_libraries(G2RCore ${ROOT_LIBRARIES}) 

install(FILES G2RModularLabel.h G2RVDetector.h G2RDetectorManager.h  G2RDetectorFactory.h DESTINATION ${CMAKE_INCLUDE_OUTPUT_DIRECTORY})
if(${G2R_ROOT_VERSION_MAJOR} GREATER 5) 
install(FILES G2RCoreDict_rdict.pcm G2RCoreDict.rootmap DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
endif()
