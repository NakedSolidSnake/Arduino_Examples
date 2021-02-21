
cmake_minimum_required(VERSION 3.7.0)

project(Semaphore)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

# This one is important
SET(CMAKE_SYSTEM_NAME Linux)

set(CMAKE_BUILD_TYPE Debug)


add_executable(semaphore "")
target_sources(semaphore
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/context.cpp
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
  ${CMAKE_CURRENT_LIST_DIR}/states/green_state.cpp
  ${CMAKE_CURRENT_LIST_DIR}/states/red_state.cpp
  ${CMAKE_CURRENT_LIST_DIR}/states/yellow_state.cpp
  )

target_include_directories(semaphore 
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/states  
  )
install(TARGETS semaphore DESTINATION bin)