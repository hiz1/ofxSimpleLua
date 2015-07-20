cmake_minimum_required(VERSION 3.2)

file(GLOB SOURCE_FILES *.cpp lua/*.c)

add_library(ofxSimpleLua STATIC
  ${SOURCE_FILES}
)