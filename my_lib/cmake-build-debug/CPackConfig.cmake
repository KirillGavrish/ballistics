# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BUILD_SOURCE_DIRS "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib;/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/cmake-build-debug")
set(CPACK_CMAKE_GENERATOR "Ninja")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "/Applications/CLion.app/Contents/bin/cmake/mac/aarch64/share/cmake-3.28/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "ballistics built using CMake")
set(CPACK_DMG_SLA_USE_RESOURCE_FILE_LICENSE "ON")
set(CPACK_GENERATOR "Bundle")
set(CPACK_INNOSETUP_ARCHITECTURE "x64")
set(CPACK_INSTALL_CMAKE_PROJECTS "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/cmake-build-debug;ballistics;ALL;/")
set(CPACK_INSTALL_PREFIX "/usr/local")
set(CPACK_MODULE_PATH "")
set(CPACK_NSIS_DISPLAY_NAME "GeographicLib-2.4")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
set(CPACK_NSIS_PACKAGE_NAME "GeographicLib-2.4")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OBJDUMP_EXECUTABLE "/usr/bin/objdump")
set(CPACK_OSX_SYSROOT "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk")
set(CPACK_OUTPUT_CONFIG_FILE "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/cmake-build-debug/CPackConfig.cmake")
set(CPACK_PACKAGE_CONTACT "karney@alum.mit.edu")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "/Applications/CLion.app/Contents/bin/cmake/mac/aarch64/share/cmake-3.28/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "GeographicLib library, utilities, and documentation")
set(CPACK_PACKAGE_FILE_NAME "GeographicLib-2.4-darwin")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "GeographicLib-2.4")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "GeographicLib-2.4")
set(CPACK_PACKAGE_NAME "ballistics")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "GeographicLib")
set(CPACK_PACKAGE_VERSION "2.4")
set(CPACK_PACKAGE_VERSION_MAJOR "2")
set(CPACK_PACKAGE_VERSION_MINOR "4")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_RESOURCE_FILE_LICENSE "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/LICENSE.txt")
set(CPACK_RESOURCE_FILE_README "/Applications/CLion.app/Contents/bin/cmake/mac/aarch64/share/cmake-3.28/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "/Applications/CLion.app/Contents/bin/cmake/mac/aarch64/share/cmake-3.28/Templates/CPack.GenericWelcome.txt")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")
set(CPACK_SOURCE_IGNORE_FILES "#;~$;/\\.git;../build;/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/man/(.*\\.pod|makeusage\\.sh|dummy\\..*)$;/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/cmake/maintainer-.*\\.cmake$;/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/(develop|cgi-bin|.*\\.cache)/;/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/(data-distrib|data-installer)/;/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/(archive|scratch|mpfr_mpir_x86_x64_msvc2010)/;/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/.*\\.(zip|tar\\.gz|bak|lsp)$;/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/(autogen|biblio)\\.sh$;/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/third_party/GeographicLib/(makefile-admin|HOWTO-RELEASE.txt)$")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/cmake-build-debug/CPackSourceConfig.cmake")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "GeographicLib-2.4")
set(CPACK_SYSTEM_NAME "Darwin")
set(CPACK_THREADS "1")
set(CPACK_TOPLEVEL_TAG "Darwin")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/Users/bennington2000super/Documents/5 семестр/Баллистика/my_lib/cmake-build-debug/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()