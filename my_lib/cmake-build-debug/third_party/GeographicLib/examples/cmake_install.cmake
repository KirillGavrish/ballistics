# Install script for directory: /Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/GeographicLib-dev" TYPE FILE FILES
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/CMakeLists.txt"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-Accumulator.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-AlbersEqualArea.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-AuxAngle.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-AuxLatitude.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-AzimuthalEquidistant.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-CassiniSoldner.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-CircularEngine.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-Constants.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-DMS.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-DST.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-Ellipsoid.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-EllipticFunction.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-GARS.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-GeoCoords.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-Geocentric.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-Geodesic.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-Geodesic-small.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-GeodesicExact.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-GeodesicLine.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-GeodesicLineExact.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-GeographicErr.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-Geohash.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-Geoid.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-Georef.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-Gnomonic.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-GravityCircle.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-GravityModel.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-Intersect.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-LambertConformalConic.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-LocalCartesian.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-MGRS.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-MagneticCircle.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-MagneticModel.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-Math.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-NearestNeighbor.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-NormalGravity.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-OSGB.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-PolarStereographic.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-PolygonArea.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-Rhumb.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-RhumbLine.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-SphericalEngine.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-SphericalHarmonic.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-SphericalHarmonic1.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-SphericalHarmonic2.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-TransverseMercator.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-TransverseMercatorExact.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-UTMUPS.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/example-Utility.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/GeoidToGTX.cpp"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/examples/make-egmcof.cpp"
    )
endif()

