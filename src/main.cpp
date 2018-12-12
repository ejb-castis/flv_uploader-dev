#include "filetest.h"
#include <iostream>
#include <tuple>
#include "time.h"
#include "Session.h"
#include "fileread.h"
#include "parsingflv.h"

using namespace rtmp;
using namespace test;
using namespace std;

void file_test_local() {
  string filename;
  unsigned int createtime;
  unsigned int stackedcount;
  unsigned int risingcount;

  std::cout << "c function...................."<<std::endl;
  parsing_hitcount_test();
  
  std::cout << "general parsing test ...................."<<std::endl;
  current_parsing_vod_hitcount_test("-abc-=-def= 0 100");
  auto result = alter_parsing_vod_hitcount_test("-abc-=-def= 0 100");
  std::tie(filename, createtime, stackedcount, risingcount) = result;
  std::cout << "result ....................: "<< filename << "::" << createtime << "::"<< stackedcount << "::"<< risingcount << std::endl;

  std::cout << "vod test1 ...................."<<std::endl;
  current_parsing_vod_hitcount_test("test=.==+m3u81536228734, = 0 29078");
  result = alter_parsing_vod_hitcount_test("test=.==+m3u81536228734, = 0 29078");
  std::tie(filename, createtime, stackedcount, risingcount) = result;
  std::cout << "result ....................: "<< filename << "::" << createtime << "::"<< stackedcount << "::"<< risingcount << std::endl;

  std::cout << "vod test2 ...................."<<std::endl;
  current_parsing_vod_hitcount_test("test=.==+m3u81536228734 = 29078");
  result = alter_parsing_vod_hitcount_test("test=.==+m3u81536228734 = 29078");
  std::tie(filename, createtime, stackedcount, risingcount) = result;
  std::cout << "result ....................: "<< filename << "::" << createtime << "::"<< stackedcount << "::"<< risingcount << std::endl;
  std::cout << "vod test3 ...................."<<std::endl;
  current_parsing_vod_hitcount_test("test=.==+m3u8 , 1536228734 = 29078 120");
  result = alter_parsing_vod_hitcount_test("test=.==+m3u8 , 1536228734 = 29078 120");
  std::tie(filename, createtime, stackedcount, risingcount) = result;
  std::cout << "result ....................: "<< filename << "::" << createtime << "::"<< stackedcount << "::"<< risingcount << std::endl;

  std::cout << "vod test4 ...................."<<std::endl;
  current_parsing_vod_hitcount_test("test=.m3u8,1536228734=2 0");
  result =  alter_parsing_vod_hitcount_test("test=.m3u8,1536228734=2 0");
  std::tie(filename, createtime, stackedcount, risingcount) = result;
  std::cout << "result ....................: "<< filename << "::"<< createtime << "::"<< stackedcount << "::"<< risingcount << std::endl;

  std::cout << "vod func test........................................................"<<std::endl;

  std::cout << "vod func test ...................."<< 1 << std::endl;
  char linestr[] ="test=.m3u8,1536228734=2 0";
  time_t create_time=time(NULL);
  int stack_count;
  int rising_count;
  int ec=0;
  get_values_from_vod_hitcount(linestr, filename, create_time, stack_count, rising_count, ec);
  std::cout << "result ....................: "<< ec <<" "<< filename << "::"<< create_time << "::"<< stack_count << "::"<< rising_count << std::endl;

  std::cout << "vod func test ...................."<< 2 << std::endl;
  char linestr2[] ="test=.==+m3u81536228734,= 029078";
  filename ="";
  create_time=time(NULL);
  stack_count=0;
  rising_count=0;
  get_values_from_vod_hitcount(linestr2, filename, create_time, stack_count, rising_count, ec);
  std::cout << "result ....................: "<< ec <<" "<< filename << "::"<< create_time << "::"<< stack_count << "::"<< rising_count << std::endl;

  std::cout << "vod func test ...................."<< 3 << std::endl;
  char linestr3[] ="test=.,==+m3u81536228734,24203=029078 -23";
  filename ="";
  create_time=time(NULL);
  stack_count=0;
  rising_count=0;
  get_values_from_vod_hitcount(linestr3, filename, create_time, stack_count, rising_count, ec);
  std::cout << "result ....................: "<< ec <<" "<< filename << "::"<< create_time << "::"<< stack_count << "::"<< rising_count << std::endl;

  std::cout << "vod func test ...................."<< 4 << std::endl;
  char linestr4[] ="test=.m3u8,1536228734= 2 -22";
  //char linestr4[] ="test=.==+m3u81536228734,1536228734= 029078 23";
  filename ="";
  create_time=time(NULL);
  stack_count=0;
  rising_count=0;
  get_values_from_vod_hitcount(linestr4, filename, create_time, stack_count, rising_count, ec);
  std::cout << "result ....................: "<< ec <<" "<< filename << "::"<< create_time << "::"<< stack_count << "::"<< rising_count << std::endl;
}

int ptr_test() {
  auto session = session_ptr(new rtmp::Session);

  {
    auto chunk_stream =session->get_chunk_stream(1);
    std::cout << "chunk_stream: " << chunk_stream.get() << ",id: " << chunk_stream->id_ << std::endl;
    
    auto header= rtmpheader_ptr(new Header);
    header->type_id_ = 128;
    chunk_stream->set_preceding_chunk_header(header);
    auto preceding_chunk_header = chunk_stream->preceding_chunk_header();

    std::cout << "preceding_chunk_header: " << preceding_chunk_header.get() << ",type id: " << preceding_chunk_header->type_id_ <<std::endl;
  }
  
  {
    auto chunk_stream =session->get_chunk_stream(1);
    std::cout << "chunk_stream: " << chunk_stream.get() << ",id: " << chunk_stream->id_ << std::endl;
    auto preceding_chunk_header = chunk_stream->preceding_chunk_header();

    std::cout << "preceding_chunk_header: " << preceding_chunk_header.get() ;
    if (preceding_chunk_header.get())
      std::cout << ",id: " << preceding_chunk_header->type_id_ << std::endl;
  }

  {
    auto chunk_stream =session->get_chunk_stream(2);
    std::cout << "chunk_stream: " << chunk_stream.get() << ",id: " << chunk_stream->id_ << std::endl;
    auto header= rtmpheader_ptr(new Header);
    header->type_id_ = 125;
    chunk_stream->set_preceding_chunk_header(header);
    auto preceding_chunk_header = chunk_stream->preceding_chunk_header();

    std::cout << "preceding_chunk_header: " << preceding_chunk_header.get() ;
    if (preceding_chunk_header.get())
      std::cout << ",id: " << preceding_chunk_header->type_id_ << std::endl;
  }

  {
    auto chunk_stream =session->get_chunk_stream(2);
    std::cout << "chunk_stream: " << chunk_stream.get() << ",id: " << chunk_stream->id_ << std::endl;
    auto preceding_chunk_header = chunk_stream->preceding_chunk_header();

    std::cout << "preceding_chunk_header: " << preceding_chunk_header.get() ;
    if (preceding_chunk_header.get())
      std::cout << ",id: " << preceding_chunk_header->type_id_ << std::endl;
  }

  {
    auto chunk_stream =session->get_chunk_stream(1);
    std::cout << "chunk_stream: " << chunk_stream.get() << ",id: " << chunk_stream->id_ << std::endl;
    auto preceding_chunk_header = chunk_stream->preceding_chunk_header();

    std::cout << "preceding_chunk_header: " << preceding_chunk_header.get() ;
    if (preceding_chunk_header.get())
      std::cout << ",id: " << preceding_chunk_header->type_id_ << std::endl;
  }

  return 1;
} 


void flash_test() {
  //std::string fn = "/data/project/git/rtmp-module/build/20181130104010.mp4.h264ac3.dump/audio/audio.dump.2";
  std::string directory = "/data/project/git/rtmp-module/build/20181130104010.mp4.h264ac3.dump/video";
  std::string file_name = "video.dump";
  std::string file_path;

  for (unsigned index=1; index <= 3; ++index )  {
    file_path = directory + "/" + file_name + "." + std::to_string(index);
    parsingflv::parsing_flv(file_path);
  }
}

int main() {
  // std::string file_path = "/data/project/git/rtmp-module/build/20181130104010.mp4.h264ac3.dump/of.h264";
  // parsingflv::parsingh_flv(file_path);

  flash_test();


  return 0;
} 
