# Install script for directory: /Users/marcel/Documents/Coding/gnuradio/gr-cbacon

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/cbacon" TYPE FILE FILES "/Users/marcel/Documents/Coding/gnuradio/gr-cbacon/cmake/Modules/cbaconConfig.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/marcel/Documents/Coding/gnuradio/gr-cbacon/build/include/cbacon/cmake_install.cmake")
  include("/Users/marcel/Documents/Coding/gnuradio/gr-cbacon/build/lib/cmake_install.cmake")
  include("/Users/marcel/Documents/Coding/gnuradio/gr-cbacon/build/swig/cmake_install.cmake")
  include("/Users/marcel/Documents/Coding/gnuradio/gr-cbacon/build/python/cmake_install.cmake")
  include("/Users/marcel/Documents/Coding/gnuradio/gr-cbacon/build/grc/cmake_install.cmake")
  include("/Users/marcel/Documents/Coding/gnuradio/gr-cbacon/build/apps/cmake_install.cmake")
  include("/Users/marcel/Documents/Coding/gnuradio/gr-cbacon/build/docs/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/marcel/Documents/Coding/gnuradio/gr-cbacon/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
