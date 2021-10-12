#include <cassert>
#include <charconv>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <chrono>
#include <thread>

void printUsage()
{
    std::cout
        << "Reads commands sequence from stdin and processes them in bulks of <num-cmds>:\n"
        << "  bulk <num-cmds> < cmd_list.txt\n"
        << std::endl;
}

class CmdAccum
{
public:
    void append(const std::string &str)
    {
        if (m_cmds.empty())
            m_timestamp = std::time(nullptr);
        m_cmds.emplace_back(str);
    }

    void execute()
    {
        if (m_cmds.empty())
            return;

        auto print = [cmds = this->m_cmds](auto &stream)
        {
            stream << "bulk: ";
            auto last = std::prev(cmds.end());
            for (auto it = cmds.begin(); it != last; ++it)
            {
                stream << *it << ",";
            }
            stream << *last << std::endl;
        };
        print(std::cout);

        std::ofstream ofs(std::string("bulk") + std::to_string(m_timestamp) + ".log");
        print(ofs);

        m_cmds.clear();
    }

    size_t size()
    {
        return m_cmds.size();
    }

protected:
    std::vector<std::string> m_cmds;
    std::time_t m_timestamp{0};
};

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printUsage();
        return 1;
    }
    std::string_view buff(argv[1], 10);
    std::string_view str(buff.begin());

    int bulkLength = 0;
    auto [ptr, ec]{std::from_chars(str.begin(), str.end(), bulkLength)};
    if (ptr == str.begin() || bulkLength <= 0)
    {
        printUsage();
        return 1;
    }

    CmdAccum accum;
    int nesting = 0;
    for (std::string line; std::getline(std::cin, line);)
    {
        if (line == "{")
        {
            if (nesting == 0)
                accum.execute();
            nesting++;
        }
        else if (line == "}")
        {
            nesting--;
            if (nesting == 0)
                accum.execute();
        }
        else
        {
            accum.append(line);
            if (accum.size() >= bulkLength && nesting == 0)
                accum.execute();
        }
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);
    }

    if (nesting == 0)
        accum.execute();

    return 0;
}
