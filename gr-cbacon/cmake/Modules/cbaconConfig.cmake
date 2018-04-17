INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_CBACON cbacon)

FIND_PATH(
    CBACON_INCLUDE_DIRS
    NAMES cbacon/api.h
    HINTS $ENV{CBACON_DIR}/include
        ${PC_CBACON_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    CBACON_LIBRARIES
    NAMES gnuradio-cbacon
    HINTS $ENV{CBACON_DIR}/lib
        ${PC_CBACON_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CBACON DEFAULT_MSG CBACON_LIBRARIES CBACON_INCLUDE_DIRS)
MARK_AS_ADVANCED(CBACON_LIBRARIES CBACON_INCLUDE_DIRS)

