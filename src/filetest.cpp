#include "filetest.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <tuple>
#include <stdexcept>
#include "time.h"
#include <boost/lexical_cast.hpp>

namespace test {

using namespace std;
const char tkEq[3] = "=";
const char tkComma[3] = ",";
const char tkBlank[3] = " ";

void parsing_hitcount_test() {
  char* token;
  char* saveptr;

  char s[] = "-abc-=-def= 0 100";
  token = strtok_r(s, "-", &saveptr);  // token = "abc"
  std::cout << "current:" << saveptr << std::endl;
  std::cout << "token:" << token << std::endl;

  token = strtok_r(NULL, "-=", &saveptr);  // token = "def"
  std::cout << "current:" << saveptr << std::endl;
  std::cout << "token:" << token << std::endl;

  token = strtok_r(NULL, tkEq, &saveptr);  // token = NULL
  std::cout << "current:" << saveptr << std::endl;
  std::cout << "token:" << token << std::endl;
}

void current_parsing_vod_hitcount_test(const char* line) {
  char* token=NULL;
  char* saveptr=NULL;

  string str = string(line);
  char* linestr = new char[str.size() + 1];
  strcpy(linestr, str.c_str());

  token = strtok_r(linestr, tkEq, &saveptr);  

  std::cout << "current src :" << line << std::endl;

  if (token == NULL) {
    std::cout << "result front :NULL :" << token << std::endl;
  } else {
    std::cout << "result front :" << token << std::endl;
  }
  if (saveptr == NULL) {
    std::cout << "result back :NULL :" << saveptr << std::endl;
  } else {
    std::cout << "result back :" << saveptr << std::endl;
  }

  char*front = token;
  token = strtok_r(front, tkComma, &saveptr);  

  if (token == NULL) {
    std::cout << "result filename :NULL :" << token << std::endl;
  } else {
    std::cout << "result filename :" << token << std::endl;
  }
  if (saveptr == NULL) {
    std::cout << "result createtime :NULL :" << saveptr << std::endl;
  } else {
    std::cout << "result createtime :" << saveptr << std::endl;
  }

  delete[] linestr;
}

std::tuple<std::string, unsigned int, unsigned int, unsigned int> alter_parsing_vod_hitcount_test(const char* line) {
  string linestr(line);
  std::size_t found = linestr.find_last_of(tkEq);

  std::cout << "alternative src:" << linestr << std::endl;
  std::cout << "result front : " << linestr.substr(0, found) << std::endl;
  std::cout << "result back : " << linestr.substr(found + 1) << std::endl;

  string front = linestr.substr(0, found);
  std::size_t found_file_time = front.find_last_of(tkComma);
  std::cout << "found_file_time : " << found_file_time << std::endl;
  std::cout << "result filename : " << front.substr(0, found_file_time) << std::endl;
  std::cout << "result createtime : " << front.substr(found_file_time + 1 )<< std::endl;

  string counts = linestr.substr(found + 1);
  std::size_t found_counts = counts.find_last_of(tkBlank);
  std::cout << "found_found_counts : " << found_counts << std::endl;
  std::cout << "result stacked fail hit count : " << counts.substr(0, found_counts) << std::endl;
  std::cout << "result rising fail hit count : " << counts.substr(found_counts + 1 )<< std::endl;

  std::string filename = front.substr(0, found_file_time);
  unsigned int create_time=0;
  unsigned int stacked_count=0;
  unsigned int rising_count=0;

  try {
    create_time = (unsigned int) std::stoul(front.substr(found_file_time + 1 ));
    stacked_count = (unsigned int) std::stoul(counts.substr(0, found_counts));
    rising_count = (unsigned int) std::stoul(counts.substr(found_counts + 1 ));
  } catch(std::exception&) {
    std::cout << "convert error:" << std::endl;
  }

  return std::make_tuple(filename, create_time, stacked_count, rising_count);
}

// line format :
// :file_name :delimenter_comma :create_time :delemeter_equal :stack_hitcout :delemeter_blank :rising_hitcount
//
// noexcept
// if success, return error code :0
void get_values_from_vod_hitcount(char* line, std::string& filename, time_t& createtime, int& stackcount, int& risingcount, int& errorcode) {
  errorcode=0;
  string linestr(line);
  std::size_t found_hitcounts = linestr.find_last_of(tkEq);

  std::cout << "alternative src:" << linestr << std::endl;
  std::cout << "result front : " << linestr.substr(0, found_hitcounts) << std::endl;
  std::cout << "result back : " << linestr.substr(found_hitcounts + 1) << std::endl;

  string filename_createtime = linestr.substr(0, found_hitcounts);
  string hitcounts = linestr.substr(found_hitcounts + 1);


  std::size_t found_createtime = filename_createtime.find_last_of(tkComma);
  filename = filename_createtime.substr(0, found_createtime);

  std::cout << "found_createtime : " << found_createtime << std::endl;
  std::cout << "result filename : " << filename << std::endl;
  std::cout << "result createtime : " << filename_createtime.substr(found_createtime + 1 )<< std::endl;
  
  std::size_t found_risingcount = hitcounts.find_last_of(tkBlank);
  std::cout << "found_risingcount : " << found_risingcount << std::endl;
  std::cout << "result stacked fail hit count : " << hitcounts.substr(0, found_risingcount) << std::endl;
  std::cout << "result rising fail hit count : " << hitcounts.substr(found_risingcount + 1 )<< std::endl;
  
  try {
    createtime = boost::lexical_cast<time_t>(filename_createtime.substr(found_createtime + 1 ));
    stackcount = boost::lexical_cast<int>(hitcounts.substr(0, found_risingcount));
    risingcount = boost::lexical_cast<int>(hitcounts.substr(found_risingcount + 1 ));
  } catch(boost::bad_numeric_cast& e) {
    std::cout << "convert error:" << e.what() << std::endl;
    errorcode = 1;
  } catch(boost::bad_lexical_cast& e) {
    std::cout << "convert lexical error:" << e.what() << std::endl;
    errorcode = 2;
  }
}


}  // namespace test