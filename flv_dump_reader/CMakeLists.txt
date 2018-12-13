set(PROJECT_NAME flv_dump_reader)
project(${PROJECT_NAME})

include_directories(../src)

set(SRCS
  flv_dump_reader_main.cpp
  ${CMAKE_SOURCE_DIR}/src/flv_message.cpp
  ${CMAKE_SOURCE_DIR}/src/parsingflv.cpp
  ${CMAKE_SOURCE_DIR}/src/flv_message.cpp
  ${CMAKE_SOURCE_DIR}/src/flv_util.cpp
)

################################################################################

ADD_DEFINITIONS(-Wall -g -fno-strict-aliasing -D_LARGEFILE64_SOURCE -D_BARBADOS_=1 -D_REENTRANT -D_FILE_OFFSET_BITS=64)
add_compile_options(-DBOOST_COROUTINES_NO_DEPRECATION_WARNING=1)

add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME}
  http_async_client  
  MPEG2AVMux
  CiMediaParser  
  CiLocalFileIO
  CiMediaFile
  CiMPEG2Lib
  MPEG4Index
  MPEG2Utils
  MPEG4Utils
  CiTransErrors  
  CiUtils
	dl
	rt
	uuid
	pthread
  ${Boost_LIBRARIES}
)

