# Install script for directory: /Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/eigen/unsupported/Eigen

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

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE FILE FILES
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/eigen/unsupported/Eigen/AdolcForward"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/eigen/unsupported/Eigen/AlignedVector3"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/eigen/unsupported/Eigen/ArpackSupport"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/eigen/unsupported/Eigen/AutoDiff"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/eigen/unsupported/Eigen/BVH"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/eigen/unsupported/Eigen/EulerAngles"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/eigen/unsupported/Eigen/FFT"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/eigen/unsupported/Eigen/IterativeSolvers"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/eigen/unsupported/Eigen/KroneckerProduct"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/eigen/unsupported/Eigen/LevenbergMarquardt"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/eigen/unsupported/Eigen/MatrixFunctions"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/eigen/unsupported/Eigen/MoreVectorization"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/eigen/unsupported/Eigen/MPRealSupport"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/eigen/unsupported/Eigen/NNLS"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/eigen/unsupported/Eigen/NonLinearOptimization"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/eigen/unsupported/Eigen/NumericalDiff"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/eigen/unsupported/Eigen/OpenGLSupport"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/eigen/unsupported/Eigen/Polynomials"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/eigen/unsupported/Eigen/Skyline"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/eigen/unsupported/Eigen/SparseExtra"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/eigen/unsupported/Eigen/SpecialFunctions"
    "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/eigen/unsupported/Eigen/Splines"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE DIRECTORY FILES "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/eigen/unsupported/Eigen/src" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/cmake-build-debug/third_party/eigen/unsupported/Eigen/CXX11/cmake_install.cmake")

endif()

