
include_directories(${SHSDK_INCLUDE_DIRS})

set(SOURCES_PLUGIN_IMPL CShPluginPlatformer.cpp CShPluginPlatformer.h)
source_group("" FILES ${SOURCES_PLUGIN_IMPL}) 

set(SOURCES_GAMECONTACTLISTENER GameContactListener.cpp GameContactListener.h)
source_group("GameContactListener" FILES ${SOURCES_GAMECONTACTLISTENER})

set(SOURCES_GAMEOBJECT GameObject.cpp GameObject.h)
source_group("GameObject" FILES ${SOURCES_GAMEOBJECT})

set(SOURCES_GAMEOBJECTSENSOR GameObjectSensor.cpp GameObjectSensor.h)
source_group("GameObject\\Sensor" FILES ${SOURCES_GAMEOBJECTSENSOR})

set(SOURCES_GAMEOBJECTPLAYER GameObjectPlayer.cpp GameObjectPlayer.h)
source_group("GameObject\\Player" FILES ${SOURCES_GAMEOBJECTPLAYER})

set(SOURCES_GAMEOBJECTENEMY GameObjectEnemy.cpp GameObjectEnemy.h)
source_group("GameObject\\Enemy" FILES ${SOURCES_GAMEOBJECTENEMY})

set(SOURCES_GAMEOBJECTPLATFORM GameObjectPlatform.cpp GameObjectPlatform.h)
source_group("GameObject\\Platform" FILES ${SOURCES_GAMEOBJECTPLATFORM})

set(SOURCES_GAMEOBJECTPIKE GameObjectPike.cpp GameObjectPike.h)
source_group("GameObject\\Pike" FILES ${SOURCES_GAMEOBJECTPIKE}) 

set(SOURCES_GAMEOBJECTROCK GameObjectRock.cpp GameObjectRock.h)
source_group("GameObject\\Rock" FILES ${SOURCES_GAMEOBJECTROCK}) 

set(SOURCES_CAMERA GameCamera.cpp GameCamera.h)
source_group("Camera" FILES ${SOURCES_CAMERA})

set(SOURCES_BACKGROUND GameBackground.cpp GameBackground.h)
source_group("Background" FILES ${SOURCES_BACKGROUND})

set(SOURCES ${SOURCES_PLUGIN_IMPL} ${SOURCES_GAMEOBJECT} ${SOURCES_GAMEOBJECTPLAYER} ${SOURCES_GAMEOBJECTENEMY} ${SOURCES_GAMEOBJECTPLATFORM} ${SOURCES_CAMERA} ${SOURCES_BACKGROUND} ${SOURCES_GAMECONTACTLISTENER} ${SOURCES_GAMEOBJECTSENSOR} ${SOURCES_GAMEOBJECTPIKE} ${SOURCES_GAMEOBJECTROCK})

# Compile to use it on Runtime
add_library(PluginPlatformer STATIC ${SOURCES})
set_property(TARGET PluginPlatformer PROPERTY FOLDER "Runtime")
set_property(TARGET PluginPlatformer APPEND PROPERTY COMPILE_DEFINITIONS "SH_DEV=1")
set_property(TARGET PluginPlatformer APPEND PROPERTY COMPILE_DEFINITIONS "SH_DEBUG=1")

# Compile to use it in the Shine Editor
add_library(PluginPlatformer_Editor OBJECT ${SOURCES})
set_property(TARGET PluginPlatformer_Editor PROPERTY FOLDER "Editor")
set_property(TARGET PluginPlatformer_Editor APPEND PROPERTY COMPILE_DEFINITIONS "SH_DEV=1")
set_property(TARGET PluginPlatformer_Editor APPEND PROPERTY COMPILE_DEFINITIONS "SH_DEBUG=1")
set_property(TARGET PluginPlatformer_Editor APPEND PROPERTY COMPILE_DEFINITIONS "SH_EDITOR=1")
set_property(TARGET PluginPlatformer_Editor APPEND PROPERTY COMPILE_DEFINITIONS "_INTERNAL_DLL")
set_property(TARGET PluginPlatformer_Editor APPEND PROPERTY POSITION_INDEPENDENT_CODE True)

