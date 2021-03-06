cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(history_wipe)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -O3 -std=gnu99")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions")

include_directories(
)

link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(history_wipe
  main.c
)

target_link_libraries(history_wipe
  SceLibKernel_stub
  SceThreadmgrForDriver_stub
  SceIofilemgrForDriver_stub
  gcc
)

set_target_properties(history_wipe
  PROPERTIES LINK_FLAGS "-nostdlib"
)

vita_create_self(history_wipe.skprx history_wipe
  CONFIG ${CMAKE_SOURCE_DIR}/history_wipe.yml
)
