add_custom_command(OUTPUT G2RMust2Dict.cxx G2RMust2Dict_rdict.pcm G2RMust2Dict.rootmap COMMAND ../../scripts/build_dict.sh G2RMust2Dict.cxx G2RMust2Dict.rootmap libG2RMust2.so G2RMust2LinkDef.h G2RMust2.h)
add_library(G2RMUST2 SHARED G2RMust2.cxx G2RMust2Dict.cxx)
target_link_libraries(G2RMUST2 ${ROOT_LIBRARIES} G2RCore) 

install(FILES G2RMust2.h DESTINATION ${CMAKE_INCLUDE_OUTPUT_DIRECTORY})

if(${G2R_ROOT_VERSION_MAJOR} GREATER 5) 
install(FILES G2RMust2Dict_rdict.pcm G2RMust2Dict.rootmap DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
endif()
