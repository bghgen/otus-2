#include <algorithm>
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <cstdlib>

using ip_address =  std::vector<std::string>;

ip_address split(const std::string &str, char d);

std::vector<ip_address> filter_any(const std::vector<ip_address> &ip_vector, int filter);

void print_ip_vector(const std::vector<ip_address> &ip_pool);

bool greater (const ip_address &a, const ip_address &b);

template <typename ... Args>
std::vector<ip_address> filter( std::vector<ip_address> ip_vector, Args... args){
  static_assert((sizeof...(Args) <= 4),  "received more than 4 numbers to filter");
  
  int octet_number = 0;
  std::vector<ip_address> result = ip_vector;

  auto filter_octet = [&octet_number, &result](const auto filter){
    std::string str = std::to_string(filter);
    std::vector<ip_address> res;
    for (auto ip = result.cbegin(); ip != result.cend(); ++ip){
       if ((*ip)[octet_number] == str){
              res.push_back(*ip);
        }
    }
    ++octet_number;
    result = res;
  };

  (filter_octet(args), ...);

  return result;
}
