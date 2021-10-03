#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
using IpAddress = std::tuple<int, int, int, int>;

IpAddress split(const std::string &str)
{
    std::string::size_type pos = 0;
    auto read_byte_str = [&]
    {
        if (pos >= str.length() || (pos > 0 && str.at(pos - 1) != '.'))
            return 0;
        std::string::size_type dpos = str.find_first_of(".\t ", pos);
        if (dpos != std::string::npos)
            ++dpos;
        std::swap(dpos, pos);
        return atoi(str.substr(dpos, pos - 1 - dpos).c_str());
    };

    return IpAddress{
        read_byte_str(),
        read_byte_str(),
        read_byte_str(),
        read_byte_str()};
}

void coutIpPool(std::vector<IpAddress> pool, bool pred(const IpAddress &) = nullptr)
{
    for (auto &ipa : pool)
    {
        if (pred == nullptr || pred(ipa))
            std::cout << std::get<0>(ipa)
                      << "." << std::get<1>(ipa)
                      << "." << std::get<2>(ipa)
                      << "." << std::get<3>(ipa) << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<IpAddress> ip_pool;
        for (std::string line; std::getline(std::cin, line);)
        {
            ip_pool.push_back(split(line));
        }

        // TODO reverse lexicographically sort
        // 222.173.235.246
        // 222.130.177.64
        std::sort(ip_pool.rbegin(), ip_pool.rend());
        coutIpPool(ip_pool);

        // TODO filter by first byte and output
        // ip = filter(1)
        // 1.231.69.33
        // 1.87.203.225
        coutIpPool(ip_pool,
            [] (const IpAddress& ipa)
                { return std::get<0>(ipa) == 1; }
        );

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        coutIpPool(ip_pool,
            [] (const IpAddress& ipa)
                { return std::get<0>(ipa) == 46 && std::get<1>(ipa) == 70; }
        );

        // TODO filter by any byte and output
        // ip = filter_any(46)
        // 186.204.34.46
        // 186.46.222.194
        coutIpPool(ip_pool,
                   [](const IpAddress &ipa)
                   {
                       const int exp = 46;
                       return std::get<0>(ipa) == exp ||
                              std::get<1>(ipa) == exp ||
                              std::get<2>(ipa) == exp ||
                              std::get<3>(ipa) == exp;
                   });
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
