#include "wordlist.h"
#include <fstream>
#include <string>

Wordlist::Wordlist(const std::string &pathname)
    : path_(pathname)
{
    std::ifstream file(pathname);
    std::string line;

    while (file >> line)
        words_.push_back(line);

    file.close();
}