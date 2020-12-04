cmake_minimum_required(VERSION 2.8.2)

project(googletest-download NONE)

include(ExternalProject)
ExternalProject_Add(googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           master
  SOURCE_DIR        "C:/Users/Dev1l/source/repos/iMCrazyDev/HSE-Course/module-1/homework/BigInteger/out/build/x64-Debug (по умолчанию)/googletest-src"
  BINARY_DIR        "C:/Users/Dev1l/source/repos/iMCrazyDev/HSE-Course/module-1/homework/BigInteger/out/build/x64-Debug (по умолчанию)/googletest-build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)
