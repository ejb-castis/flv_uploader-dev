#include <tuple>

namespace test {
void parsing_hitcount_test();
void current_parsing_vod_hitcount_test(const char* line);

std::tuple<std::string, unsigned int, unsigned int, unsigned int>
alter_parsing_vod_hitcount_test(const char* line);

void get_values_from_vod_hitcount(char* line, std::string& filename, time_t& createtime, int& stackcount, int& risingcount, int& errorcode);


void bin_file_write();


}  // namespace test