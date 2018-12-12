set(SRCS
  filetest.cpp
  main.cpp
  fileread.cpp
  pointer.cpp
  parsingflv.cpp
  flv_message.cpp
  flv_util.cpp
)

################################################################################

ADD_DEFINITIONS(-Wall -g -fno-strict-aliasing -D_LARGEFILE64_SOURCE -D_BARBADOS_=1 -D_REENTRANT -D_FILE_OFFSET_BITS=64)
add_compile_options(-DBOOST_COROUTINES_NO_DEPRECATION_WARNING=1)

add_executable(filetest ${SRCS})
target_link_libraries(filetest
  MPEG2AVMux
  CiMediaParser  
  CiLocalFileIO
  CiMediaFile
  CiMPEG2Lib
  MPEG4Index
  MPEG2Utils
  MPEG4Utils
  CiTransErrors  CiUtils
	dl
	rt
	uuid
	pthread
  ${Boost_LIBRARIES}
)

################################################################################
# Google Performance Tools 를 이용한 프로파일링
# 참고 : http://110.35.173.15/jira/browse/TM-57
# 
# ubuntu
# $ sudo apt install libgoogle-perftools-dev
#
# centos
# $ yum install gperftools-devel
#
#if (NOT APPLE)
#add_executable(filetest-profile ${SRCS})
#target_link_libraries(filetest-profile
#  ${Boost_LIBRARIES}
#  profiler
#)
#endif()

