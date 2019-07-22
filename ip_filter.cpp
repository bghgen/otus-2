#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
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

void filter_any(std::vector<ip_address> ip_pool, std::string search_str){
  for (auto ip: ip_pool){
    for (auto octet : ip){
      if (octet == search_str){
      std::cout << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3] << std::endl;
      break;
      }
    }

  }
}


auto filter_octet = [](std::vector<ip_address> &ip_pool, int &octet_number, const auto filter) {
  std::string str = std::to_string(filter);
  std::vector<ip_address> res;
  for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip){
     if ((*ip)[octet_number] == str){
            res.push_back(*ip);
      }
  }
  ++octet_number;
  ip_pool = res;
};

template <typename ... Args>
constexpr void filter(std::vector<ip_address> &ip_pool, Args... args){
  if (sizeof...(Args) > 4)
    return;
  int octet_number = 0;

  (filter_octet(ip_pool, octet_number, args), ...);

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

void filter_one(std::vector<ip_address> ip_pool, std::string search_str){
    for (auto ip: ip_pool){
       if (ip[0] == search_str){
        std::cout << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3] << std::endl;
        }
        //std::cout<<ip[0]<< " " << search_str <<std::endl;
    }
}

void filter_two(std::vector<ip_address> ip_pool, std::string first_str, std::string second_str){
    for (auto ip: ip_pool){
       if ((ip[0] == first_str) &&
           (ip[1] == second_str)) {
        std::cout << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3] << std::endl;
        }
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

        // TODO reverse lexicographically sort
        auto sort_result = ip_pool;

        std::sort(ip_pool.begin(), ip_pool.end(), greater);

        // print_ip_vector(ip_pool);



        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // filter_one(ip_pool, "1");
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
         filter_two(ip_pool, "46", "70");

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)
        // filter_any(ip_pool, "46");
        std::cout<< std::endl;
        //filter(ip_pool, 46,70);
        filter(ip_pool, 346,70);

        print_ip_vector(ip_pool);


        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    UNUSED(argc);
    UNUSED(argv);
    return 0;
}
