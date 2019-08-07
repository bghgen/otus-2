#include "lib.h"

namespace IP {
  
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

std::vector<ip_address>  filter_any(const std::vector<ip_address> &ip_vector, int filter){
  std::vector<ip_address> result;
  for (const auto &ip: ip_vector){
    for (const auto &octet : ip){
      if (std::atoi(octet.c_str()) == filter){
      result.push_back(ip);
      break;
      }
    }
  }
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

bool greater (const ip_address &a, const ip_address &b){
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

}
