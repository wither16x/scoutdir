#ifndef CLI_H_
#define CLI_H_

#include <string_view>

constexpr char k_arg_help[] = "-h";
constexpr char k_arg_wordlist[] = "-w";
constexpr char k_arg_url[] = "-u";

constexpr bool is_argument(std::string_view str, std::string_view arg)
{
    return str == arg;
}

void help();
void title();
void check_arg_count(int argc);

#endif // CLI_H_