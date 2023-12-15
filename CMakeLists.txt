cmake_minimum_required(VERSION 3.20)

project(mif)

file(GLOB PUBLIC_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE mif_files ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL ${CMAKE_CURRENT_SOURCE_DIR}/)
set(COMMANDS_FILE ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json)

if (EXISTS ${COMMANDS_FILE})
  file(COPY ${COMMANDS_FILE} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/)
endif()

message(${mif_files})

add_executable(mif_e ${mif_files})
target_compile_options(mif_e PRIVATE -g -Wall)


list(FILTER mif_files EXCLUDE REGEX "main.c")

add_library(mif SHARED ${mif_files})
add_library(mif_static STATIC ${mif_files})

target_compile_options(mif PUBLIC -fPIC)
target_compile_options(mif_static PUBLIC -fPIC)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(
  mif
    PUBLIC
      $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      ${CMAKE_CURRENT_BINARY_DIR}/include
      ${CMAKE_CURRENT_SOURCE_DIR}/include)


target_include_directories(
  mif_static
    PUBLIC
      $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      ${CMAKE_CURRENT_BINARY_DIR}/include
      ${CMAKE_CURRENT_SOURCE_DIR}/include)


target_include_directories(
  mif_e
    PUBLIC
      $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      ${CMAKE_CURRENT_BINARY_DIR}/include
      ${CMAKE_CURRENT_SOURCE_DIR}/include)


include(FetchContent)

set(LIBRARIES m)


target_link_libraries(mif_e PRIVATE ${LIBRARIES})
target_link_libraries(mif PRIVATE ${LIBRARIES})
target_link_libraries(mif_static PRIVATE ${LIBRARIES})
