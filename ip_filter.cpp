#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define UNUSED(variable) (void)variable

using ip_address =  std::vector<std::string>;

ip_address split(const std::string &str, char d)
{
    ip_address r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

auto filter_any(const std::vector<ip_address> &ip_vector, int filter){
  std::vector<ip_address> result;
  for (auto ip: ip_vector){
    for (auto octet : ip){
      if (std::atoi(octet.c_str()) == filter){
      result.push_back(ip);
      break;
      }
    }
  }
  return result;
}

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
constexpr auto filter(const std::vector<ip_address> &ip_vector, Args... args){
  if (sizeof...(Args) > 4)
    throw std::invalid_argument( "received more than 4 numbers to filter" );
  int octet_number = 0;
  std::vector<ip_address> result = ip_vector;

  (filter_octet(result, octet_number, args), ...);

  return result;

}

void print_ip_vector(const std::vector<ip_address> &ip_pool){
    for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        {
            if (ip_part != ip->cbegin())
            {
                std::cout << ".";

            }
            std::cout << *ip_part;
        }
        std::cout << std::endl;
    }
}

bool greater (ip_address a, ip_address b){
  for (uint i = 0; i < a.size(); ++i){
    uint8_t an = std::atoi(a[i].c_str());
    uint8_t bn = std::atoi(b[i].c_str());
    if (an > bn)
      return true;
    else if (an < bn)
      return false;
  }
      return true;
}


int main(int argc, char const *argv[])
{

    try
    {
        std::vector<ip_address> ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            ip_address v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), greater);
        print_ip_vector(ip_pool);

        // filter by first byte and output
        auto for_filter1 = filter(ip_pool, 1);
        print_ip_vector(for_filter1);


        // filter by first and second bytes and output
        auto for_filter2 = filter(ip_pool, 46, 70);
        print_ip_vector(for_filter2);

        // filter by any byte and output
        auto for_filter3 = filter_any(ip_pool, 46);
        print_ip_vector(for_filter3);

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    UNUSED(argc);
    UNUSED(argv);
    return 0;
}
