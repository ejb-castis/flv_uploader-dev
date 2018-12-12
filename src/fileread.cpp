#include "fileread.h"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <bitset>



unsigned char to_uchar(const char ch) {
  unsigned int val = ch & 0xFF;
  return static_cast<unsigned char>(val);
}

unsigned get_high_4bit(const char ch) {
  return (to_uchar(ch) & 0xf0) >> 4;
}
unsigned get_lower_4bit(const char ch) {
  return (to_uchar(ch) & 0x0f);
}

std::string get_hex_format(std::string const & value) {
  std::ostringstream oss;
  size_t len = value.length();
  oss << std::hex << std::setfill('0');
  for (size_t i = 0; i < len; i++) {
    oss << std::setw(2) << static_cast<unsigned int>(to_uchar(value.c_str()[i])) << " ";
  }
  return oss.str();
}

bool file_read(std::string const & file_path) {

  // boost::filesystem::path file_path("dump");
  // boost::filesystem::create_directories(file_path);

  unsigned const kLF=4;
  unsigned const kBK=1;
  
  std::cout << "open >" << file_path << std::endl;

  const std::size_t buffer_size= 16;
  char* buffer = new char[buffer_size];
  
  std::ifstream binfile (file_path, std::ios::binary);
  if (not binfile) {
    std::cout << "> open false" << std::endl;
    return false;
  }

  //get length of file:
  binfile.seekg(0, binfile.end);
  std::size_t length = binfile.tellg();
  binfile.seekg(0, binfile.beg);

  std::cout << "> file length[" << length << "]" << std::endl;

  std::size_t reading_size = length < buffer_size ? length : buffer_size;
  binfile.read(buffer, reading_size);
  
  if (not binfile) { std::cout << "> read false" << std::endl; return false; }
  std::cout << "> read length[" << reading_size << "]" << std::endl;

  for (size_t n=0; n < reading_size; ++n) {
    std::cout << std::uppercase << std::hex << std::setfill('0') << std::setw(2) << static_cast<unsigned int>(to_uchar(buffer[n]));
    if ( (n+1) % kBK == 0) { std::cout << " "; }
    if ( (n+1) % kLF == 0) { std::cout << std::endl;}
  }

  std::cout << std::endl;
  for (size_t n=0; n < reading_size; ++n) {
    std::cout << std::bitset<8>(static_cast<unsigned int>(to_uchar(buffer[n]))) <<" ";
    if ( (n+1) % kLF == 0) { std::cout << std::endl;}
  }

  binfile.close();
  delete [] buffer;

  return true;
}
