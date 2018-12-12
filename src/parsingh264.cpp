#include "CiGlobals.h"
#include "CiMediaType.h"

#include "common_CiFileIO.h"
#include "common_CiLocalFileIO.h"
#include "common_CiMediaFile.h"
#include "common_CiMPEG2Lib.h"
#include "common_MPEG2Utils.h"
#include "common_MPEG4Utils.h"
#include "common_CiMediaParser.h"
#include "common_CiUtils.h"

#include <algorithm>
#include <bitset>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "parsingflv.h"

using namespace flv_util;

namespace parsingh264 {

  bool get_h264_resolution(unsigned char* buffer, std::size_t len,
                         int& video_width,
                         int& video_height, int& ec) {

  assam::CCiH264VideoMediaFrame frame;
  bool ret; 

  std::cout << "> framebuffer > " << std::endl;
  std::cout << to_hex(buffer, len) << std::endl; 

  ret = frame.AddPacketData(buffer, len);
  //std::cout << "> add packet " << ret << std::endl;

  frame.MakeMediaFrame();
  //std::cout << "> make media frame " << std::endl; 
  
  ret = frame.ParseMediaFrame();
  if (not ret) std::cout << "> parse media frame returns false" << std::endl;

  if (ret) {
    video_width = H264Utils::GetPictureWidth(frame.m_SPS);
    video_height = H264Utils::GetPictureHeight(frame.m_SPS);
    std::cout << "video_width[" << video_width << "]" << std::endl;
    std::cout << "video_height[" << video_height << "]" << std::endl;

    std::cout << " > sps size:" << frame.m_SPS.size << std::endl; 
    std::cout << " > sps" << std::endl; 
    std::cout << to_hex(frame.m_SPS.buffer,512) << std::endl;
  }

  int elements = 
    H264Utils::ParseSequenceParameterSet(frame.m_SPS, buffer, len);
    std::cout << "elements:" << elements << ",sps level idc:" << frame.m_SPS.level_idc << std::endl; 

  return ret;
}


} // namespace parsingh264