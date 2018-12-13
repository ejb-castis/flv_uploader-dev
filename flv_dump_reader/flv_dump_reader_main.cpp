#include <chrono>
#include <functional>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <string>

#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "streamer/base64.h"

#include "flv_util.h"
#include "flv_message.h"
#include "parsingflv.h"

void flv_dump_read() {
  // std::string file_path = "/data/project/git/rtmp-module/build/20181130104010.mp4.h264ac3.dump/of.h264";
  // parsingflv::parsingh_flv(file_path);
  //std::string fn = "/data/project/git/rtmp-module/build/20181130104010.mp4.h264ac3.dump/audio/audio.dump.2";
  std::string directory = "/data/project/git/rtmp-module/build/20181130104010.mp4.h264ac3.dump/video";
  std::string file_name = "video.dump";
  std::string file_path;

  for (unsigned index=90; index <= 90; ++index )  {
    file_path = directory + "/" + file_name + "." + std::to_string(index);
    parsingflv::parsing_flv(file_path);
  }
}


void flv_message_dump_read() {
  using namespace flv_message;
  castis::streamer::MediaPublishEsContext context;
  unsigned six = 234;
  unsigned eix = 234; //234

  std::string directory = "/data/project/git/rtmp-module/build/dump/flv_es";
  std::string file_name = "flv_es.dump";
  std::string file_path;

  for (unsigned index=six; index <= eix; ++index )  {
    file_path = directory + "/" + file_name + "." + std::to_string(index);

    read_flv_es_dump_file(context, file_path);
  }

}

int main() {

  flv_message_dump_read();
  
  return 1;
}