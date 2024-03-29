include(${CMAKE_CURRENT_LIST_DIR}/Initialize.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/CompileOption.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/AlliedModders/All.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/Source/SourceEngine.cmake)

add_library(smsdk_ext INTERFACE)
target_sources(smsdk_ext INTERFACE ${SOURCEMOD_PATH}/public/smsdk_ext.cpp)
target_compile_definitions(smsdk_ext INTERFACE -DSDK_EXPORTS -DSOURCEMOD_BUILD)
target_link_libraries(smsdk_ext INTERFACE smsdk mmsdk source_sdk #[[CDetour]]) # Uncomment CDetour to enable detour.
add_library(amsdk INTERFACE)
target_link_libraries(amsdk INTERFACE smsdk_ext)