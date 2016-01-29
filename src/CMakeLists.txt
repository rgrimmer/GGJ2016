set(BOX2D_INSTALL_DOC OFF CACHE BOOL "")
set(BOX2D_BUILD_SHARED OFF CACHE BOOL "")
set(BOX2D_BUILD_STATIC OFF CACHE BOOL "")
set(BOX2D_BUILD_EXAMPLES OFF CACHE BOOL "")

add_subdirectory(Box2D)

include_directories(Box2D)

add_subdirectory(Plugins)
add_subdirectory(Extension)
add_subdirectory(Game)
