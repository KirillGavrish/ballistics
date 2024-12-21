# Install script for directory: /Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib

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
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/GeographicLib" TYPE FILE FILES
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/Accumulator.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/AlbersEqualArea.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/AuxAngle.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/AuxLatitude.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/AzimuthalEquidistant.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/CassiniSoldner.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/CircularEngine.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/Constants.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/DAuxLatitude.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/DMS.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/DST.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/Ellipsoid.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/EllipticFunction.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/GARS.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/GeoCoords.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/Geocentric.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/Geodesic.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/GeodesicExact.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/GeodesicLine.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/GeodesicLineExact.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/Geohash.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/Geoid.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/Georef.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/Gnomonic.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/GravityCircle.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/GravityModel.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/Intersect.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/LambertConformalConic.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/LocalCartesian.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/MGRS.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/MagneticCircle.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/MagneticModel.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/Math.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/NearestNeighbor.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/NormalGravity.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/OSGB.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/PolarStereographic.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/PolygonArea.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/Rhumb.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/SphericalEngine.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/SphericalHarmonic.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/SphericalHarmonic1.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/SphericalHarmonic2.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/TransverseMercator.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/TransverseMercatorExact.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/UTMUPS.hpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/include/GeographicLib/Utility.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/GeographicLib" TYPE FILE FILES "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/cmake-build-debug/third_party/GeographicLib/include/GeographicLib/Config.h")
endif()

