#include "lib.h"
#include <string>

int main(int, char const *[])
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

    return 0;
}
