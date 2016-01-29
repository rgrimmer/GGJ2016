
# Enable Address Sanitizer
if (UNIX)
	option(ENABLE_ASAN "Enable address sanitizer" ON)

	if (ENABLE_ASAN)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
	endif (ENABLE_ASAN)
endif(UNIX)

include_directories(${SHSDK_INCLUDE_DIRS})

set(SOURCES_MAIN main.cpp)
source_group("" FILES ${SOURCES_MAIN})

set(SOURCES_GAME Game.cpp Game.h)
source_group("" FILES ${SOURCES_GAME})

set(SOURCES_GAMESTATE GameState.cpp GameState.h)
source_group("GameState" FILES ${SOURCES_GAMESTATE})

set(SOURCES_GAMESTATEMENUMAIN GameStateMenuMain.cpp GameStateMenuMain.h)
source_group("GameState\\MenuMain" FILES ${SOURCES_GAMESTATEMENUMAIN})

set(SOURCES_GAMESTATEGAME GameStateGame.cpp GameStateGame.h)
source_group("GameState\\Game" FILES ${SOURCES_GAMESTATEGAME})

set(SOURCES_SOUND Sound.cpp Sound.h)
source_group("Sound" FILES ${SOURCES_SOUND})

add_executable(GGJ2016 WIN32 ${SOURCES_MAIN} ${SOURCES_GAME} ${SOURCES_GAMESTATE} ${SOURCES_GAMESTATEMENUMAIN} ${SOURCES_GAMESTATEGAME} ${SOURCES_SOUND})
set_property(TARGET GGJ2016 APPEND PROPERTY COMPILE_DEFINITIONS "SH_DEV=1")
set_property(TARGET GGJ2016 APPEND PROPERTY COMPILE_DEFINITIONS "SH_DEBUG=1")

target_link_libraries(GGJ2016 PluginExample PluginPlatformer Box2D) # link with plugins

target_link_libraries(GGJ2016 ${SHSDK_LIBRARIES})


