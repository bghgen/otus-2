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

bool greater (ip_address a, ip_address b);

auto filter_octet = [](std::vector<ip_address> &ip_vector, int &octet_number, const auto filter) {
  std::string str = std::to_string(filter);
  std::vector<ip_address> res;
  for (auto ip = ip_vector.cbegin(); ip != ip_vector.cend(); ++ip){
     if ((*ip)[octet_number] == str){
            res.push_back(*ip);
      }
  }
  ++octet_number;
  ip_vector = res;
};

template <typename ... Args>
std::vector<ip_address> filter( std::vector<ip_address> ip_vector, Args... args){
  if (sizeof...(Args) > 4)
    throw std::invalid_argument( "received more than 4 numbers to filter" );
  int octet_number = 0;
  std::vector<ip_address> result = ip_vector;

  (filter_octet(result, octet_number, args), ...);

  return result;
}
