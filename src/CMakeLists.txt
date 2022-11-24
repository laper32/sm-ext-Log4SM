add_library(log4sm SHARED
	${CMAKE_CURRENT_LIST_DIR}/extension.cpp
	${CMAKE_CURRENT_LIST_DIR}/detail/ext.cpp
	${CMAKE_CURRENT_LIST_DIR}/log4sm/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/log4sm/sm_handler.cpp
	${CMAKE_CURRENT_LIST_DIR}/log4sm/sm_interface.cpp
	${CMAKE_CURRENT_LIST_DIR}/log4sm/sp_native.cpp
)

target_include_directories(log4sm PUBLIC 
	${CMAKE_CURRENT_LIST_DIR}
	${CMAKE_CURRENT_LIST_DIR}/common
	${CMAKE_CURRENT_LIST_DIR}/detail
	${CMAKE_CURRENT_LIST_DIR}/log4sm
	$ENV{LPS_SDK_PATH}/sm/public
)


target_link_libraries(log4sm PUBLIC amsdk spdlog::spdlog_header_only Boost::boost fmt::fmt-header-only)

set_target_properties(log4sm PROPERTIES PREFIX "" SUFFIX ".ext.2.${HL2SDK_GAME}${LIB_SHARED_EXT}")

# Windows is true, Linux is not tested.
install(TARGETS log4sm
	RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/addons/sourcemod/extensions
)

# If you have gamedata
# Uncomment to activate it
#[[ install(
	DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/gamedata/
	DESTINATION ${PROJECT_SOURCE_DIR}/addons/sourcemod/gamedata
	FILES_MATCHING PATTERN "*.games.txt"
) ]]

# If you have SP include...
# Uncomment to activate it
#[[
install(
	DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/sourcepawn/
	DESTINATION ${PROJECT_SOURCE_DIR}/addons/sourcemod/scripting/include
	FILES_MATCHING PATTERN "*.inc"
)
]]
