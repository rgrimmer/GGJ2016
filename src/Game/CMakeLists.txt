
include_directories(${SHSDK_INCLUDE_DIRS})

set(SOURCES_MAIN main.cpp)
source_group("" FILES ${SOURCES_MAIN})

set(SOURCES_GAME Game.cpp Game.h)
source_group("" FILES ${SOURCES_GAME})

add_executable(GGJ2016 WIN32 ${SOURCES_MAIN} ${SOURCES_GAME})
set_property(TARGET GGJ2016 APPEND PROPERTY COMPILE_DEFINITIONS "SH_DEV=1")
set_property(TARGET GGJ2016 APPEND PROPERTY COMPILE_DEFINITIONS "SH_MASTER=1")

target_link_libraries(GGJ2016 PluginExample) # link with plugins

target_link_libraries(GGJ2016 ${SHSDK_LIBRARIES})


