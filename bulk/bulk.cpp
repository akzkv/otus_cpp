#include <cassert>
#include <charconv>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void printUsage()
{
    std::cout
      << "Reads commands sequence from stdin and processes them in bulks of <num-cmds>:\n"
      << "  bulk <num-cmds> < cmd_list.txt\n"  
      << std::endl;
}

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
    auto [ptr, ec] {std::from_chars(str.begin(), str.end(), bulkLength)}; 
    if (ptr == str.begin() || bulkLength <= 0)
    {
        printUsage();
        return 1;
    }

    std::cout << bulkLength << std::endl;

    return 0;
}
