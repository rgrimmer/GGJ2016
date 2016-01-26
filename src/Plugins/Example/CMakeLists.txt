
include_directories(${SHSDK_INCLUDE_DIRS})

set(SOURCES_PLUGIN_IMPL CShPluginExample.cpp CShPluginExample.h)
source_group("" FILES ${SOURCES_PLUGIN_IMPL})

# Compile to use it on Runtime
add_library(PluginExample STATIC ${SOURCES_PLUGIN_IMPL})
set_property(TARGET PluginExample PROPERTY FOLDER "Runtime")
set_property(TARGET PluginExample APPEND PROPERTY COMPILE_DEFINITIONS "SH_DEV=1")
set_property(TARGET PluginExample APPEND PROPERTY COMPILE_DEFINITIONS "SH_MASTER=1")

# Compile to use it in the Shine Editor
add_library(PluginExample_Editor OBJECT ${SOURCES_PLUGIN_IMPL})
set_property(TARGET PluginExample_Editor PROPERTY FOLDER "Editor")
set_property(TARGET PluginExample_Editor APPEND PROPERTY COMPILE_DEFINITIONS "SH_DEV=1")
set_property(TARGET PluginExample_Editor APPEND PROPERTY COMPILE_DEFINITIONS "SH_MASTER=1")
set_property(TARGET PluginExample_Editor APPEND PROPERTY COMPILE_DEFINITIONS "SH_EDITOR=1")
set_property(TARGET PluginExample_Editor APPEND PROPERTY COMPILE_DEFINITIONS "_INTERNAL_DLL")
set_property(TARGET PluginExample_Editor APPEND PROPERTY POSITION_INDEPENDENT_CODE True)

