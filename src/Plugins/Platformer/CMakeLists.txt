
include_directories(${SHSDK_INCLUDE_DIRS})

set(SOURCES_PLUGIN_IMPL CShPluginPlatformer.cpp CShPluginPlatformer.h)
source_group("" FILES ${SOURCES_PLUGIN_IMPL})

set(SOURCES_GAMEOBJECT GameObject.cpp GameObject.h)
source_group("GameObject" FILES ${SOURCES_GAMEOBJECT})

set(SOURCES_GAMEOBJECTPLAYER GameObjectPlayer.cpp GameObjectPlayer.h)
source_group("GameObject\\Player" FILES ${SOURCES_GAMEOBJECTPLAYER})

set(SOURCES_GAMEOBJECTENEMY GameObjectEnemy.cpp GameObjectEnemy.h)
source_group("GameObject\\Enemy" FILES ${SOURCES_GAMEOBJECTENEMY})

set(SOURCES_GAMEOBJECTPLATFORM GameObjectPlatform.cpp GameObjectPlatform.h)
source_group("GameObject\\Platform" FILES ${SOURCES_GAMEOBJECTPLATFORM})

set(SOURCES_CAMERA GameCamera.cpp GameCamera.h)
source_group("Camera" FILES ${SOURCES_CAMERA})

# Compile to use it on Runtime
add_library(PluginPlatformer STATIC ${SOURCES_PLUGIN_IMPL} ${SOURCES_GAMEOBJECT} ${SOURCES_GAMEOBJECTPLAYER} ${SOURCES_GAMEOBJECTENEMY} ${SOURCES_GAMEOBJECTPLATFORM} ${SOURCES_CAMERA})
set_property(TARGET PluginPlatformer PROPERTY FOLDER "Runtime")
set_property(TARGET PluginPlatformer APPEND PROPERTY COMPILE_DEFINITIONS "SH_DEV=1")
set_property(TARGET PluginPlatformer APPEND PROPERTY COMPILE_DEFINITIONS "SH_DEBUG=1")

# Compile to use it in the Shine Editor
add_library(PluginPlatformer_Editor OBJECT ${SOURCES_PLUGIN_IMPL} ${SOURCES_GAMEOBJECT} ${SOURCES_GAMEOBJECTPLAYER} ${SOURCES_GAMEOBJECTENEMY} ${SOURCES_GAMEOBJECTPLATFORM} ${SOURCES_CAMERA})
set_property(TARGET PluginPlatformer_Editor PROPERTY FOLDER "Editor")
set_property(TARGET PluginPlatformer_Editor APPEND PROPERTY COMPILE_DEFINITIONS "SH_DEV=1")
set_property(TARGET PluginPlatformer_Editor APPEND PROPERTY COMPILE_DEFINITIONS "SH_DEBUG=1")
set_property(TARGET PluginPlatformer_Editor APPEND PROPERTY COMPILE_DEFINITIONS "SH_EDITOR=1")
set_property(TARGET PluginPlatformer_Editor APPEND PROPERTY COMPILE_DEFINITIONS "_INTERNAL_DLL")
set_property(TARGET PluginPlatformer_Editor APPEND PROPERTY POSITION_INDEPENDENT_CODE True)

